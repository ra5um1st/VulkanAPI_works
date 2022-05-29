#include "Application.hpp"

namespace zxc {
	Application::Application() : 
		window(Window(width, height, title)), 
		pipeline(Pipeline("Shaders/TestShader/test_shader.vert", "Shaders/TestShader/test_shader.frag")) {}

	void Application::Run() {

		while (!window.ShouldClose())
		{
			glfwPollEvents();
		}
	}
}