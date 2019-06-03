#include "pch.h"
#include "MathHelpers.h"

#include <cmath>

namespace Graphics {

    bool AreSame(const float a, const float b, const float epsilon)
    {
        return fabs(a - b) < epsilon;
    }

}
