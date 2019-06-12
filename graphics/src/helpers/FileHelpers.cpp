#include "pch.h"
#include "FileHelpers.h"

#include "logging/Log.h"

namespace Graphics
{
    std::string ParseFile(const std::string& path)
    {
        const std::ifstream file(path);

        if (file.fail()) {
            LogError([path]()
            {
                std::stringstream ss;
                ss << "Can't open file: " << path << ". Does the file exist?";
                return ss.str();
            }());
        }

        std::stringstream ss;
        ss << file.rdbuf();

        return ss.str();
    }
}
