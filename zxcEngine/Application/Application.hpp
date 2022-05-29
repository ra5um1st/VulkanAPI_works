#pragma once

#include "../Window/Window.hpp"
#include "../Pipeline/Pipeline.hpp"

namespace zxc {

	class Application {
	public:
		int width = 800;
		int height = 600;
		std::string title = "zxcEngine";

		Application();

		void Run();

	private:
		Window window;
		Pipeline pipeline;
	};
}