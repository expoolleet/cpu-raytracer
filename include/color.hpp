#pragma once

#include "vec3.hpp"

using color3 = vec3;

void writeColor(std::ostream &out, const color3 &c) {
    int rByte = static_cast<int>(255.999 * c.r);
    int gByte = static_cast<int>(255.999 * c.g);
    int bByte = static_cast<int>(255.999 * c.b);
    out << rByte << ' ' << gByte << ' ' << bByte << '\n';
}
