#include "Vertex.hpp"

vector<VkVertexInputAttributeDescription> Vertex::GetInputAttributeDescriptions() {

	vector<VkVertexInputAttributeDescription> inputAttributeDescriptions(2);

	inputAttributeDescriptions[0].binding = 0;
	inputAttributeDescriptions[0].format = VK_FORMAT_R32G32_SFLOAT;
	inputAttributeDescriptions[0].location = 0;
	inputAttributeDescriptions[0].offset = offsetof(Vertex, position);

	inputAttributeDescriptions[1].binding = 0;
	inputAttributeDescriptions[1].format = VK_FORMAT_R32G32B32_SFLOAT;
	inputAttributeDescriptions[1].location = 1;
	inputAttributeDescriptions[1].offset = offsetof(Vertex, color);

	return inputAttributeDescriptions;
}
vector<VkVertexInputBindingDescription> Vertex::GetInputBindingDescriptions() {

	vector<VkVertexInputBindingDescription> inputBindingDescriptions(1);

	inputBindingDescriptions[0].binding = 0;
	inputBindingDescriptions[0].inputRate = VK_VERTEX_INPUT_RATE_VERTEX;
	inputBindingDescriptions[0].stride = sizeof(Vertex);

	return inputBindingDescriptions;
}