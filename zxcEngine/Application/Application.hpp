#pragma once

#include "../Window/Window.hpp"
#include "../Pipeline/Pipeline.hpp"
#include "../Device/Device.hpp"
#include "../SwapChain/SwapChain.hpp"

#include <memory>
#include <vector>

using namespace std;

namespace zxc {

	class Application {
	public:
		int width = 800;
		int height = 600;
		string title = "zxcEngine";

		Application();
		~Application();

		Application(const Application&) = delete;
		Application& operator=(const Application&) = delete;

		void Run();

	private:
		Window window{ width, height, title };
		Device device{ window };
		SwapChain swapChain{ device, window.GetExtent() };
		unique_ptr<Pipeline> pipeline;
		VkPipelineLayout pipelineLayout;
		vector<VkCommandBuffer> commandBuffers;

		void CreatePipeline();
		void CreatePipelineLayout();
		void CreateCommandBuffers();
		void DrawFrame();

	};
}