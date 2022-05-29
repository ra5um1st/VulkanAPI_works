#pragma once

#include <string>
#include <vector>

using namespace std;

class Pipeline
{
public:
	Pipeline(const string& vertFilepath, const string& fragFilepath);

private:
	void Initialize(const string& vertFilepath, const string& fragFilepath);

	static vector<char> ReadFile(const string& filepath);
};