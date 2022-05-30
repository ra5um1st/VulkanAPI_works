#include "Application.hpp"

namespace zxc {

	void Application::Run() {

		while (!window.ShouldClose())
		{
			glfwPollEvents();
		}
	}
}