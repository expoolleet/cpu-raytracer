#pragma once

#include <limits>
#include <random>

namespace utils {

constexpr float pi = 3.14159265359;
constexpr float infinity = std::numeric_limits<float>::infinity();

float degToRad(float deg) {
    return deg * pi / 180.0f;
}

float randomFloat() {
    static std::mt19937 randEngine;
    static std::uniform_real_distribution<float> randDist(0.0f, 1.0f);
    return randDist(randEngine);
}

float randomFloat(float aMin, float bMax) {
    return aMin + (bMax - aMin) * randomFloat();
}
};  // namespace utils
