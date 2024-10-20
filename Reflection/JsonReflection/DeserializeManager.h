#pragma once
#include <format>
#include <variant>
#include "SerializedObject.h"
#include "Deserializer.h"
#include "common/notCopiable.h"
#include "LoggingSystem/logger.h"


class DeserializeManager
{
private:
    SerializedMap m_serialized; /*!<data per typename*/

    DeserializeManager() = default;
    void loadFile(const std::string& a_file, const std::string& a_profile);

    

public:
    NOT_COPIABLE(DeserializeManager)
    NOT_MOVABLE(DeserializeManager)

    static DeserializeManager& instance();
    void load(const std::string& a_directory, const std::string& a_profile);

    template<typename Type>
    void deserialize(const Type* a_value, const std::string& a_typename)const
    {
        if (auto iterSerialized = m_serialized.find(a_typename); iterSerialized != m_serialized.cend())
        {
            std::visit(Deserializer<Type> { a_value }, iterSerialized->second);
        }
        else
        {
            const auto& typeInfo = typeid(Type);
            Logger::error(std::format("Unsupported type deserializer: {}", typeInfo.name()));
        }
    }
};