#pragma once

#include <bit>
#include <cmath>
#include <fstream>

#include "utils.hpp"

class vec3 {
   public:
    union {
        float c[3];
        struct {
            float x, y, z;
        };
        struct {
            float r, g, b;
        };
    };

    vec3(float x, float y, float z) : c{x, y, z} {}
    vec3(float x) : c{x, x, x} {}
    vec3() : c{0.0f, 0.0f, 0.0f} {}

    vec3 operator-() const {
        return vec3(-x, -y, -z);
    }

    float operator[](int i) {
        return c[i];
    }

    float operator[](int i) const {
        return c[i];
    }

    float length_squared() const {
        return x * x + y * y + z * z;
    }

    float length() const {
        return std::sqrt(length_squared());
    }

    inline static vec3 random() {
        return vec3(utils::random(), utils::random(), utils::random());
    }

    inline static vec3 random(float aMin, float bMax) {
        return vec3(utils::random(aMin, bMax), utils::random(aMin, bMax), utils::random(aMin, bMax));
    }
};

inline std::ostream &operator<<(std::ostream &out, const vec3 &v) {
    return out << v.x << ' ' << v.y << ' ' << v.z;
}

inline vec3
operator+(const vec3 &v1, const vec3 &v2) {
    return vec3(v1.x + v2.x, v1.y + v2.y, v1.z + v2.z);
}

inline vec3 operator-(const vec3 &v1, const vec3 &v2) {
    return vec3(v1.x - v2.x, v1.y - v2.y, v1.z - v2.z);
}

inline vec3 operator*(const vec3 &v1, const vec3 &v2) {
    return vec3(v1.x * v2.x, v1.y * v2.y, v1.z * v2.z);
}

inline vec3 operator*(float a, const vec3 &v) {
    return vec3(a * v.x, a * v.y, a * v.z);
}

inline vec3 operator/(const vec3 &v, float a) {
    return vec3(v.x / a, v.y / a, v.z / a);
}

inline float dot(const vec3 &v1, const vec3 &v2) {
    return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}

inline vec3 cross(const vec3 &v1, const vec3 &v2) {
    return vec3(v1.y * v2.z - v1.z * v2.y, v1.z * v2.x - v1.x * v2.z, v1.x * v2.y - v1.y * v2.x);
}

inline vec3 normalize(const vec3 &v) {
    return v / v.length();
}

inline vec3 randomUnitVector() {
    while (true) {
        vec3 vec = vec3::random(-1.0f, 1.0f);
        float len = vec.length_squared();
        if (1e-38 < len && len <= 1.0f) {
            return vec / std::sqrt(len);
        }
    }
}

inline vec3 randomOnHemisphere(const vec3 &normal) {
    vec3 vecOnUnitHemishpere = randomUnitVector();
    if (dot(vecOnUnitHemishpere, normal) > 0.0f) {
        return vecOnUnitHemishpere;
    }
    return -vecOnUnitHemishpere;
}

inline vec3 reflect(const vec3 &v, const vec3 &n) {
    return v - 2 * dot(v, n) * n;
}

inline vec3 refract(const vec3 &v, const vec3 &n, float refractionIndex) {
    float cosTheta = std::fmin(dot(-v, n), 1.0f);
    vec3 vPerpendicular = refractionIndex * (v + cosTheta * n);
    vec3 vParallel = -std::sqrtf(std::fabs(1.0f - vPerpendicular.length_squared())) * n;
    return vPerpendicular + vParallel;
}

inline bool nearZero(const vec3 &v, float epsilon = 1e-8) {
    return std::fabs(v.x) < epsilon && std::fabs(v.y) < epsilon && std::fabs(v.z) < epsilon;
}

inline bool isZero(const vec3 &v) {
    int32_t xBits, yBits, zBits;
    xBits = std::bit_cast<int32_t>(std::fabs(v.x));
    yBits = std::bit_cast<int32_t>(std::fabs(v.y));
    zBits = std::bit_cast<int32_t>(std::fabs(v.z));
    int maxUlp = 4;  // maximum steps going from 0.0 to 1.0
    return xBits <= maxUlp && yBits <= maxUlp && zBits <= maxUlp;
}

using point3 = vec3;
