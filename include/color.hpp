#pragma once

#include <interval.hpp>

#include "vec3.hpp"

using color3 = vec3;

constexpr float gamma = 2.2f;

float gammaCorrect(float value) {
    if (value <= 0.0f) {
        return 0.0f;
    }
    return std::pow(value, 1.0f / gamma);
}

void writeColor(std::ostream &out, const color3 &color) {
    interval interval(0.0f, 0.999f);

    int rByte = static_cast<int>(256 * interval.clamp(gammaCorrect(color.r)));
    int gByte = static_cast<int>(256 * interval.clamp(gammaCorrect(color.g)));
    int bByte = static_cast<int>(256 * interval.clamp(gammaCorrect(color.b)));
    out << rByte << ' ' << gByte << ' ' << bByte << '\n';
}
