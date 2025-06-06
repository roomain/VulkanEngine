#pragma once
/***********************************************
* @headerfile VulkanVertex.h
* @date 09 / 05 / 2025
* @author Roomain
************************************************/
#include <vector>
#include <type_traits>
#include <glm/glm.hpp>
#include <vulkan/vulkan.hpp>
#include "VulkanDefines.h"



/*@brief vertex with normal*/
struct BasicVertex
{
	glm::vec3 m_position;
	glm::vec3 m_normal;
};


struct TexturedVertex : BasicVertex
{
	glm::vec2 m_uv;
};

struct ColoredVertex : BasicVertex
{
	glm::vec2 m_color;
};


struct SplineVertex : BasicVertex
{
	glm::vec4 m_tangent;
};


struct AnimationVertex : TexturedVertex
{
	glm::vec4 tangent;
	glm::vec2 m_color;
	glm::vec4 joint0;
	glm::vec4 weight0;
};

template<typename Vertex>
constexpr VkVertexInputBindingDescription bindingDescription(const uint32_t a_binding)
{
	return VkVertexInputBindingDescription({ a_binding, sizeof(Vertex), VK_VERTEX_INPUT_RATE_VERTEX });
}


inline VertexInputAttribDescVector inputDescription(const uint32_t a_binding, const uint32_t a_location, const BasicVertex& a_vertex)
{
	VertexInputAttribDescVector description;
	description.emplace_back(
		VkVertexInputAttributeDescription{
			.location = a_location,
			.binding = a_binding,
			.format = VK_FORMAT_R32G32B32_SFLOAT,
			.offset = static_cast<uint32_t>(offsetof(a_vertex, m_position))
		});
	description.emplace_back(
		VkVertexInputAttributeDescription{
			.location = a_location,
			.binding = a_binding,
			.format = VK_FORMAT_R32G32B32_SFLOAT,
			.offset = static_cast<uint32_t>(offsetof(a_vertex, m_normal))
		});
	return description;
}

inline VertexInputAttribDescVector inputDescription(const uint32_t a_binding, const uint32_t a_location, const TexturedVertex& a_vertex)
{
	VertexInputAttribDescVector description;
	description.emplace_back(
		VkVertexInputAttributeDescription{
			.location = a_location,
			.binding = a_binding,
			.format = VK_FORMAT_R32G32B32_SFLOAT,
			.offset = static_cast<uint32_t>(offsetof(a_vertex, m_position))
		});
	description.emplace_back(
		VkVertexInputAttributeDescription{
			.location = a_location,
			.binding = a_binding,
			.format = VK_FORMAT_R32G32B32_SFLOAT,
			.offset = static_cast<uint32_t>(offsetof(a_vertex, m_normal))
		});
	description.emplace_back(
		VkVertexInputAttributeDescription{
			.location = a_location,
			.binding = a_binding,
			.format = VK_FORMAT_R32G32_SFLOAT,
			.offset = static_cast<uint32_t>(offsetof(a_vertex, m_uv))
		});
	return description;
}

inline VertexInputAttribDescVector inputDescription(const uint32_t a_binding, const uint32_t a_location, const ColoredVertex& a_vertex)
{
	VertexInputAttribDescVector description;
	description.emplace_back(
		VkVertexInputAttributeDescription{
			.location = a_location,
			.binding = a_binding,
			.format = VK_FORMAT_R32G32B32_SFLOAT,
			.offset = static_cast<uint32_t>(offsetof(a_vertex, m_position))
		});
	description.emplace_back(
		VkVertexInputAttributeDescription{
			.location = a_location,
			.binding = a_binding,
			.format = VK_FORMAT_R32G32B32_SFLOAT,
			.offset = static_cast<uint32_t>(offsetof(a_vertex, m_normal))
		});
	description.emplace_back(
		VkVertexInputAttributeDescription{
			.location = a_location,
			.binding = a_binding,
			.format = VK_FORMAT_R32G32B32_SFLOAT,
			.offset = static_cast<uint32_t>(offsetof(a_vertex, m_color))
		});
	return description;
}

inline VertexInputAttribDescVector inputDescription(const uint32_t a_binding, const uint32_t a_location, const SplineVertex& a_vertex)
{
	VertexInputAttribDescVector description;
	description.emplace_back(
		VkVertexInputAttributeDescription{
			.location = a_location,
			.binding = a_binding,
			.format = VK_FORMAT_R32G32B32_SFLOAT,
			.offset = static_cast<uint32_t>(offsetof(a_vertex, m_position))
		});
	description.emplace_back(
		VkVertexInputAttributeDescription{
			.location = a_location,
			.binding = a_binding,
			.format = VK_FORMAT_R32G32B32_SFLOAT,
			.offset = static_cast<uint32_t>(offsetof(a_vertex, m_normal))
		});
	description.emplace_back(
		VkVertexInputAttributeDescription{
			.location = a_location,
			.binding = a_binding,
			.format = VK_FORMAT_R32G32B32_SFLOAT,
			.offset = static_cast<uint32_t>(offsetof(a_vertex, m_tangent))
		});
	return description;
}

inline VertexInputAttribDescVector inputDescription(const uint32_t a_binding, const uint32_t a_location, const AnimationVertex& a_vertex)
{
	VertexInputAttribDescVector description;
	description.emplace_back(
		VkVertexInputAttributeDescription{
			.location = a_location,
			.binding = a_binding,
			.format = VK_FORMAT_R32G32B32_SFLOAT,
			.offset = static_cast<uint32_t>(offsetof(a_vertex, m_position))
		});
	description.emplace_back(
		VkVertexInputAttributeDescription{
			.location = a_location,
			.binding = a_binding,
			.format = VK_FORMAT_R32G32B32_SFLOAT,
			.offset = static_cast<uint32_t>(offsetof(a_vertex, m_normal))
		});
	description.emplace_back(
		VkVertexInputAttributeDescription{
			.location = a_location,
			.binding = a_binding,
			.format = VK_FORMAT_R32G32_SFLOAT,
			.offset = static_cast<uint32_t>(offsetof(a_vertex, m_uv))
		});
	description.emplace_back(
		VkVertexInputAttributeDescription{
			.location = a_location,
			.binding = a_binding,
			.format = VK_FORMAT_R32G32B32A32_SFLOAT,
			.offset = static_cast<uint32_t>(offsetof(a_vertex, m_tangent))
		});
	description.emplace_back(
		VkVertexInputAttributeDescription{
			.location = a_location,
			.binding = a_binding,
			.format = VK_FORMAT_R32G32B32_SFLOAT,
			.offset = static_cast<uint32_t>(offsetof(a_vertex, m_color))
		});
	description.emplace_back(
		VkVertexInputAttributeDescription{
			.location = a_location,
			.binding = a_binding,
			.format = VK_FORMAT_R32G32B32A32_SFLOAT,
			.offset = static_cast<uint32_t>(offsetof(a_vertex, joint0))
		});
	description.emplace_back(
		VkVertexInputAttributeDescription{
			.location = a_location,
			.binding = a_binding,
			.format = VK_FORMAT_R32G32B32A32_SFLOAT,
			.offset = static_cast<uint32_t>(offsetof(a_vertex, weight0))
		});
	return description;
}