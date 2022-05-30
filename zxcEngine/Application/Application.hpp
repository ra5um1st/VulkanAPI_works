#pragma once

#include "../Window/Window.hpp"
#include "../Pipeline/Pipeline.hpp"
#include "../Device/Device.hpp"

namespace zxc {

	class Application {
	public:
		int width = 800;
		int height = 600;
		std::string title = "zxcEngine";

		void Run();

	private:
		Window window{ width, height, title };
		Device device{ window };
		Pipeline pipeline{
			"Shaders/TestShader/test_shader.vert",
			"Shaders/TestShader/test_shader.frag",
			device,
			Pipeline::CreateDefaultConfigInfo(width, height) };
	};
}