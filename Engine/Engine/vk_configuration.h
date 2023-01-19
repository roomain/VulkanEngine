#pragma once
#include <vector>
#include <string>
#include <algorithm>

namespace Vulkan
{


	/*@brief vulkan instance configuration*/
	struct InstanceConf
	{
		bool useDebug = true;
		std::string appName;						/*!< application name*/
		uint32_t appVersion;						/*!< application version*/
		std::vector<std::string> instanceExtProps;	/*!< vulkan instance extensions properties*/
		std::vector<std::string> instanceLayers;	/*!< vulkan instance desired layer*/
	};

	/*@brief Queue configuration*/
	struct QueueConfiguration
	{
		VkQueueFlags type;					/*!< queue type*/
		int index = -1;						/*!< queue location index*/
		bool presentationSupport = false;	/*!< indicate if queue supports presentation*/
	};

	//----------------------------------------------------------------------------
	/*@brief Queues configuration corresponding to the needs*/
	struct DeviceQueuesConfiguration
	{
		std::vector<QueueConfiguration> vQueueConf;

		inline void reset()
		{
			for (auto& conf : vQueueConf)
				conf.index = -1;
		}

		inline [[nodiscard]] bool isValid()const noexcept
		{
			return std::all_of(vQueueConf.begin(), vQueueConf.end(), [](const QueueConfiguration& a_conf) {return a_conf.index >= 0; });
		}

		inline [[nodiscard]] int queueVKIndex(const VkQueueFlags a_flag, bool& a_presentationSupport)const noexcept
		{
			auto iter = std::find_if(vQueueConf.begin(), vQueueConf.end(), [&](auto&& conf)
				{
					return (conf.type & a_flag) == a_flag;
				});
			if (iter != vQueueConf.end())
			{
				a_presentationSupport = iter->presentationSupport;
				return iter->index;
			}
			return -1;
		}

		inline [[nodiscard]] int presentationQueueVKIndex()const noexcept
		{
			auto iter = std::find_if(vQueueConf.begin(), vQueueConf.end(), [](auto&& conf)
				{
					return conf.presentationSupport;
				});

			if (iter != vQueueConf.end())
				return iter->index;
			return -1;
		}
	};

	/*@brief engine configuration*/
	struct VulkanConfiguration : public InstanceConf
	{
		bool useDepthBuffer = false;				/*!< use depth buffer*/
		uint64_t frameTimeout = 0;					/*!< timeout for acquiring frame*/
		std::vector<std::string> deviceExt;			/*!< physical device extensions*/
		DeviceQueuesConfiguration queues;			/*!< queues configuration*/
	};
}