#pragma once

#include <vulkan/vulkan.hpp>

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm/glm.hpp>

#include <vector>

using namespace std;
using namespace glm;

class Vertex
{
public:
	vec2 position;
	vec3 color;

	static vector<VkVertexInputAttributeDescription> GetInputAttributeDescriptions();
	static vector<VkVertexInputBindingDescription> GetInputBindingDescriptions();
};