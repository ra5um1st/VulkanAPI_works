#include "Application.hpp"

#include <stdexcept>
#include <array>
#include <vector>

namespace zxc {

	Application::Application() {
		CreateVertexBuffer();
		CreatePipelineLayout();
		CreatePipeline();
		CreateCommandBuffers();
	};

	Application::~Application() {
		vkDestroyPipelineLayout(device.GetDevice(), pipelineLayout, nullptr);
	};

	void Application::Run() {

		while (!window.ShouldClose())
		{
			glfwPollEvents();
			DrawFrame();
		}

		vkDeviceWaitIdle(device.GetDevice());
	}

	void Application::CreatePipeline() {
		PipelineConfigInfo pipelineConfig = Pipeline::CreateDefaultConfigInfo(swapChain.Width(), swapChain.Height());

		pipelineConfig.renderPass = swapChain.GetRenderPass();
		pipelineConfig.pipelineLayout = pipelineLayout;
		pipeline = make_unique<Pipeline>("Shaders/TestShader/test_shader.vert.spv", "Shaders/TestShader/test_shader.frag.spv", device, pipelineConfig);
	}

	void Application::CreateVertexBuffer()
	{
		vector<Vertex> vertices = {
			{{0.0f, -0.5f}, {1.0f, 0.0f, 0.0f}},
			{{0.5f, 0.5f}, {0.0f, 1.0f, 0.0f}},
			{{-0.5f, 0.5f}, {0.0f, 0.0f, 1.0f}}
		};

		vertexBuffer = make_unique<VertexBuffer>(device, vertices);
	}

	void Application::CreatePipelineLayout() {

		VkPipelineLayoutCreateInfo pipelineLayoutInfo{};

		pipelineLayoutInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
		pipelineLayoutInfo.setLayoutCount = 0;
		pipelineLayoutInfo.pSetLayouts = nullptr;
		pipelineLayoutInfo.pushConstantRangeCount = 0;
		pipelineLayoutInfo.pPushConstantRanges = nullptr;
		if (vkCreatePipelineLayout(device.GetDevice(), &pipelineLayoutInfo, nullptr, &pipelineLayout) != VK_SUCCESS) {
			throw runtime_error("Failed to create pipeline layout");
		}
	};
	void Application::CreateCommandBuffers() {

		commandBuffers.resize(swapChain.GetImageCount());

		VkCommandBufferAllocateInfo commandBufferAllocateInfo{};
		commandBufferAllocateInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
		commandBufferAllocateInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
		commandBufferAllocateInfo.commandPool = device.GetCommandPool();
		commandBufferAllocateInfo.commandBufferCount = static_cast<uint32_t>(commandBuffers.size());

		if (vkAllocateCommandBuffers(device.GetDevice(), &commandBufferAllocateInfo, commandBuffers.data()) != VK_SUCCESS) {
			throw runtime_error("Failed to allocate command buffers");
		}

		for (size_t i = 0; i < commandBuffers.size(); i++)
		{
			VkCommandBufferBeginInfo commandBufferBeginInfo{};
			commandBufferBeginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;

			if (vkBeginCommandBuffer(commandBuffers[i], &commandBufferBeginInfo) != VK_SUCCESS) {
				throw runtime_error("Failed to begin recording command buffer");
			}

			VkRenderPassBeginInfo renderPassBeginInfo{};
			renderPassBeginInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
			renderPassBeginInfo.renderPass = swapChain.GetRenderPass();
			renderPassBeginInfo.framebuffer = swapChain.GetFrameBuffer(i);
			renderPassBeginInfo.renderArea.offset = { 0,0 };
			renderPassBeginInfo.renderArea.extent = swapChain.GetSwapChainExtent();

			array<VkClearValue, 2> clearValues{};
			clearValues[0].color = { 0.0f, 0.0f, 0.0f, 1.0f };
			clearValues[1].depthStencil = { 1.0f, 0 };

			renderPassBeginInfo.clearValueCount = static_cast<uint32_t>(clearValues.size());
			renderPassBeginInfo.pClearValues = clearValues.data();

			vkCmdBeginRenderPass(commandBuffers[i], &renderPassBeginInfo, VK_SUBPASS_CONTENTS_INLINE);

			pipeline->Bind(commandBuffers[i]);
			vertexBuffer->Bind(commandBuffers[i]);
			vertexBuffer->Draw(commandBuffers[i]);

			vkCmdEndRenderPass(commandBuffers[i]);

			if (vkEndCommandBuffer(commandBuffers[i]) != VK_SUCCESS) {
				throw runtime_error("Failed to end recording command buffer");
			}
		}
	};
	void Application::DrawFrame() {

		uint32_t imageIndex = 0;
		if (swapChain.AcquireNextImage(&imageIndex) != VK_SUCCESS) {
			throw runtime_error("Failed to acquire next image");
		}

		if (swapChain.SubmitCommandBuffers(&commandBuffers[imageIndex], &imageIndex) != VK_SUCCESS) {
			throw runtime_error("Failed to submit command buffers");
		}
	};
}