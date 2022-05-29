#include <GLFW/glfw3.h>
#include <string>

namespace zxc {

	class Window {
	public:
		Window(int height, int width, std::string title);
		~Window();

		bool ShouldClose();

	private:
		GLFWwindow* window;

		int width;
		int height;
		std::string title;

		void Initialize();
	};
}