#pragma once

#include <string>

namespace Graphics
{
    std::string ParseFile(const std::string& filepath);
    void WriteToFile(const std::string& filepath, const std::string& content);
}
