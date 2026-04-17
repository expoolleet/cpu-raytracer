#pragma once

#include <cmath>
#include <fstream>

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

inline vec3 unitVector(const vec3 &v) {
    return v / v.length();
}

using point3 = vec3;
