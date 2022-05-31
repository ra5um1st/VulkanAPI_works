#pragma once

#include "../../Device/Device.hpp"
#include "../../Models/Vertex/Vertex.hpp"

#include <glm/glm.hpp>
#include <vulkan/vulkan.hpp>

#include <vector>

using namespace std;

namespace zxc {

	class VertexBuffer
	{
	public:
		VertexBuffer(Device& device, const vector<Vertex> vertices);
		~VertexBuffer();

		void Bind(VkCommandBuffer commandBuffer);
		void Draw(VkCommandBuffer commandBuffer);

	private:

		Device& device;
		VkBuffer buffer;
		VkDeviceMemory bufferMemory;
		uint32_t vertexCount;

		void CreateVertexBuffer(const vector<Vertex> vertices);
	};
}