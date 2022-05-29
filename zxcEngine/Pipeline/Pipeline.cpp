#include "Pipeline.hpp"

#include <fstream>
using namespace std;

Pipeline::Pipeline(const string& vertFilepath, const string& fragFilepath)
{
	Initialize(vertFilepath, fragFilepath);
}

void Pipeline::Initialize(const string& vertFilepath, const string& fragFilepath)
{
	auto vertData = ReadFile(vertFilepath);
	auto fragData = ReadFile(fragFilepath);

	printf("Vertex shader size: %zu \n", vertData.size());
	printf("Fragment shader size: %zu \n", fragData.size());
}

vector<char> Pipeline::ReadFile(const string& filepath)
{
	ifstream file = ifstream(filepath, ios::ate | ios::binary);

	if (!file.is_open()) {
		throw runtime_error("Failed to open file: " + filepath);
	}

	vector<char> buffer = vector<char>(file.tellg());

	file.seekg(0);
	file.read(buffer.data(), buffer.size());
	file.close();

	return buffer;
}
