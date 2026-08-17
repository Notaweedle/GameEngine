#pragma once
#include <rapidjson/document.h>   
#include <string>
#include "Vector2.h"
#include "Color.h"

namespace nu::json
{
    bool Load(const std::string& filename, rapidjson::Document& document);

    bool Read(const rapidjson::Value& value, const std::string& name, int& data);

    bool Read(const rapidjson::Value& value, const std::string& name, bool& data);

    bool Read(const rapidjson::Value& value, const std::string& name, float& data);

    bool Read(const rapidjson::Value& value, const std::string& name, std::string& data);

    bool Read(const rapidjson::Value& value, const std::string& name, nu::Vector2& data);

    bool Read(const rapidjson::Value& value, const std::string& name, Color& data);
    

    // TODO (assignment): add overloads following the same pattern as Read(int) for:
    //   float, bool, std::string, and your Vector2 / Color types.
    // e.g.  bool Read(const rapidjson::Value& value, const std::string& name, float& data);
}
