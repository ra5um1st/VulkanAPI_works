#pragma once

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <string>

using namespace std;

namespace zxc {

	class Window {
	public:
		Window(int width, int height, string title);
		~Window();

		bool ShouldClose();
		void CreateWindowSurface(VkInstance vkInstance, VkSurfaceKHR* surface);

		VkExtent2D GetExtent() { return { static_cast<uint32_t>(width), static_cast<uint32_t>(height) }; };

	private:
		GLFWwindow* window;

		int width;
		int height;
		string title;

		void Initialize();
	};
}