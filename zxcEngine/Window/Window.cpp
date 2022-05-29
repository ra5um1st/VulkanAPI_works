#include "Window.hpp"

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
		glfwInitHint(GLFW_CLIENT_API, GLFW_NO_API);
		glfwInitHint(GLFW_RESIZABLE, GLFW_FALSE);

		window = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
	}
	
	bool Window::ShouldClose() {
		return glfwWindowShouldClose(window);
	}
}