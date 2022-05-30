#include "Window.hpp"
#include <stdexcept>

namespace zxc {
	Window::Window(int width, int height, std::string title)
	{
		this->width = width;
		this->height = height;
		this->title = title;

		Initialize();
	}

	Window::~Window()
	{
		glfwDestroyWindow(window);
		glfwTerminate();
	}

	void Window::Initialize()
	{
		glfwInit();
		glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
		glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

		window = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
	}
	
	bool Window::ShouldClose() {
		return glfwWindowShouldClose(window);
	}

	void Window::CreateWindowSurface(VkInstance vkInstance, VkSurfaceKHR* surface) {
		if (glfwCreateWindowSurface(vkInstance, window, nullptr, surface) != VK_SUCCESS) {
			throw runtime_error("Failed to create window surface");
		}
	}
}