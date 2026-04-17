#pragma once

#include <limits>

namespace utils {

constexpr float pi = 3.14159265359;
constexpr float infinity = std::numeric_limits<float>::infinity();

float degToRad(float deg) {
    return deg * pi / 180.0f;
}
};  // namespace utils
