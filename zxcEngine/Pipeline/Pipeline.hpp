#pragma once

#include "../Device/Device.hpp"

#include <string>
#include <vector>

using namespace std;

namespace zxc {

	struct PipelineConfigInfo {
		VkViewport viewport;
		VkRect2D scissor;
		VkPipelineViewportStateCreateInfo viewportInfo;
		VkPipelineInputAssemblyStateCreateInfo inputAssemblyInfo;
		VkPipelineRasterizationStateCreateInfo rasterizationInfo;
		VkPipelineMultisampleStateCreateInfo multisampleInfo;
		VkPipelineColorBlendAttachmentState colorBlendAttachment;
		VkPipelineColorBlendStateCreateInfo colorBlendInfo;
		VkPipelineDepthStencilStateCreateInfo depthStencilInfo;
		VkPipelineLayout pipelineLayout = nullptr;
		VkRenderPass renderPass = nullptr;
		uint32_t subpass = 0;
	};

	class Pipeline
	{
	public:
		Pipeline(const string& vertFilepath, const string& fragFilepath, Device& device, const PipelineConfigInfo& configInfo);
		~Pipeline();

		Pipeline(const Pipeline&) = delete;
		void operator=(const Pipeline&) = delete;

		static PipelineConfigInfo CreateDefaultConfigInfo(uint32_t width, uint32_t height);

	private:
		Device& device;
		VkPipeline graphicsPipeline;
		VkShaderModule vertShaderModule;
		VkShaderModule fragShaderModule;

		void Initialize(const string& vertFilepath, const string& fragFilepath, const PipelineConfigInfo& configInfo);
		void CreateShaderModule(const vector<char>& data, VkShaderModule* shaderModule);

		static vector<char> ReadFile(const string& filepath);
	};
}