#include "VertexBuffer.hpp"

#include <cassert>

zxc::VertexBuffer::VertexBuffer(Device& device, const vector<Vertex> vertices) : device{device}, vertexCount{static_cast<uint32_t>(vertices.size())}
{
	CreateVertexBuffer(vertices);
}

zxc::VertexBuffer::~VertexBuffer()
{
	vkDestroyBuffer(device.GetDevice(), buffer, nullptr);
	vkFreeMemory(device.GetDevice(), bufferMemory, nullptr);
}

void zxc::VertexBuffer::Bind(VkCommandBuffer commandBuffer)
{
	VkBuffer buffers[] = { buffer };
	VkDeviceSize offsets[] = {0};

	vkCmdBindVertexBuffers(commandBuffer, 0, 1, buffers, offsets);
}

void zxc::VertexBuffer::Draw(VkCommandBuffer commandBuffer)
{
	vkCmdDraw(commandBuffer, vertexCount, 1, 0, 0);
}

void zxc::VertexBuffer::CreateVertexBuffer(const vector<Vertex> vertices)
{
	assert(vertexCount >= 3 && "Vertex count must be at least 3");

	VkDeviceSize bufferSize = sizeof(vertices[0]) * vertexCount;

	device.CreateBuffer(
		bufferSize,
		VK_BUFFER_USAGE_VERTEX_BUFFER_BIT,
		VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT,
		buffer,
		bufferMemory);

	void* data;
	vkMapMemory(device.GetDevice(), bufferMemory, 0, bufferSize, 0, &data);
	memcpy(data, vertices.data(), static_cast<size_t>(bufferSize));
	vkUnmapMemory(device.GetDevice(), bufferMemory);
}
