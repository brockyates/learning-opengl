#include "pch.h"
#include "FileHelpers.h"

#include "logging/Log.h"

namespace Graphics
{
    std::string ParseFile(const std::string& filepath)
    {
        const std::ifstream file(filepath);

        if (file.fail()) {
            LogError([filepath]()
            {
                std::stringstream ss;
                ss << "Can't open file: " << filepath << ". Does the file exist?";
                return ss.str();
            }());
        }

        std::stringstream ss;
        ss << file.rdbuf();

        return ss.str();
    }

    void WriteToFile(const std::string& filepath, const std::string& content)
    {
        std::ofstream file(filepath, std::ios::binary);
        file << content;
    }
}
