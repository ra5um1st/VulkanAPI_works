#include "Application/Application.hpp"
#include <iostream>

int main() {

	zxc::Application app;

	try {
		app.Run();
	}
	catch (std::exception& exception) {
		std::cerr << exception.what() << '\n';
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}