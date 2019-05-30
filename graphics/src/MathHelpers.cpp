#include "pch.h"
#include "MathHelpers.h"

#include <cmath>

namespace graphics {

    bool AreSame(float a, float b, float epsilon)
    {
        return fabs(a - b) < epsilon;
    }

}
