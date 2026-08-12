#pragma once
#include <rapidjson/document.h>   // defines rapidjson::Document / rapidjson::Value
#include <string>

namespace nu::json
{
    bool Load(const std::string& filename, rapidjson::Document& document);

    bool Read(const rapidjson::Value& value, const std::string& name, int& data);

    // TODO (assignment): add overloads following the same pattern as Read(int) for:
    //   float, bool, std::string, and your Vector2 / Color types.
    // e.g.  bool Read(const rapidjson::Value& value, const std::string& name, float& data);
}
