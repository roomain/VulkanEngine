#pragma once
/***********************************************
* @headerfile VulkanParameter.generated.h
* @date 20/10/2024
* @author reflecGen.py
************************************************/
#include <variant>
#include "DeserializeManager.h"
#include "Deserializer.h"

/* class deserialization macro */
#define _DESERIALIZE_VulkanParameter \
for(const auto&[name, data] : a_serialized) \
{ \
	if(name == "extensions") \
		std::visit(Deserializer<std::vector<std::string>>{ &a_this.extensions }, data); \
	if(name == "layers") \
		std::visit(Deserializer<std::vector<std::string>>{ &a_this.layers }, data); \
}\

/* class deserialization macro */
#define _DESERIALIZE_VulkanQueueFamilyParameter \
for(const auto&[name, data] : a_serialized) \
{ \
	if(name == "bIsRenderer") \
		std::visit(Deserializer<bool>{ &a_this.bIsRenderer }, data); \
	if(name == "flags") \
		std::visit(Deserializer<VkQueueFlags>{ &a_this.flags }, data); \
	if(name == "count") \
		std::visit(Deserializer<uint32_t>{ &a_this.count }, data); \
}\

/* class deserialization macro */
#define _DESERIALIZE_VulkanDeviceParameter \
for(const auto&[name, data] : a_serialized) \
{ \
	if(name == "extensions") \
		std::visit(Deserializer<std::vector<std::string>>{ &a_this.extensions }, data); \
	if(name == "layers") \
		std::visit(Deserializer<std::vector<std::string>>{ &a_this.layers }, data); \
	if(name == "queues") \
		std::visit(Deserializer<std::vector<VulkanQueueFamilyParameter>>{ &a_this.queues }, data); \
}\

