#include "pch.h"
#include <filesystem>
#include <ranges>
#include "DeserializeManager.h"
#include "SerializedDataManager.h"
#include "boost/property_tree/json_parser.hpp"

namespace fs = std::filesystem;

DeserializeManager& DeserializeManager::instance()
{
	static DeserializeManager instanceManager;
	return instanceManager;
}

void DeserializeManager::load(const std::string& a_directory, const std::string& a_profile)
{
	fs::path jsonDir = std::filesystem::current_path();
	jsonDir.append(a_directory);

	auto isJsonFile = [](auto& a_entry) { return a_entry.is_regular_file() &&
		(a_entry.path().extension() == ".json" || a_entry.path().extension() == ".JSON"); };

	if (fs::exists(jsonDir) && fs::is_directory(jsonDir))
	{
		for (const auto& entry : fs::recursive_directory_iterator(jsonDir) | std::views::filter(isJsonFile))
			loadFile(entry.path().string(), a_profile);
	}
}



void DeserializeManager::loadFile(const std::string& a_file, const std::string& a_profile)
{
	const std::string INCLUDE = "include";
	const std::string CLASS_ARRAY = "ClassArray";
	const std::string ID = "Id";
	std::vector<std::string> includeFilesList;
	boost::property_tree::ptree propTree;
	boost::property_tree::read_json(a_file, propTree);
	if (auto iter = propTree.find(INCLUDE); iter != propTree.not_found())
		SerializedDataManager::includeFiles(iter->second, includeFilesList);

	if (auto iter = propTree.find(CLASS_ARRAY); iter != propTree.not_found())
	{
		for (const auto& [name, node] : iter->second)
		{			
			if (auto iterId = node.find(ID); iterId != node.not_found())
			{
				if (std::string parentProfile;  SerializedDataManager::getCurrentProfile(iterId->second, a_profile, parentProfile))
				{
					if (parentProfile != "null" && !parentProfile.empty())
					{
						for (const auto& file : includeFilesList)
						{
							fs::path curFile(a_file);
							curFile = curFile.parent_path().append(file);
							try
							{
								loadFile(curFile.string(), parentProfile);
							}
							catch (std::exception& except)
							{
								Logger::error(except.what());
							}
						}
					}

					for (const auto& [classname, classNode] : node)
					{
						if (classname != ID)
							SerializedDataManager::addSerializedData(classname, classNode, m_serialized);
					}
					break;
				}
			}

		}
	}
	
}