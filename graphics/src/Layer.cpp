#include "pch.h"
#include "Layer.h"

namespace Graphics {

    Layer::Layer(const std::string& debugName)
        : m_DebugName(debugName)
    {
        LOG_TRACE([&]() {
            std::stringstream ss;
            ss << "Layer::Layer(const std::string& debugName): " << m_DebugName;
            return ss.str();
        }());
    }

    Layer::~Layer()
    {
        LOG_TRACE([&]() {
            std::stringstream ss;
            ss << "Layer::~Layer(const std::string& debugName): " << m_DebugName;
            return ss.str();
        }());
    }

}
