#pragma once

#include <memory>

#include "interval.hpp"
#include "ray.hpp"

class Material;

struct HitInfo {
    point3 point;
    vec3 normal;
    float t;
    bool frontFace;
    std::shared_ptr<Material> material;

    void setFaceNormal(const ray &r, const vec3 &outwardNormal) {
        frontFace = dot(r.direction(), outwardNormal) < 0.0f;
        normal = frontFace ? outwardNormal : -outwardNormal;
    }
};

class Hittable {
   public:
    ~Hittable() = default;

    virtual bool hit(const ray &r, interval rayInterval, HitInfo &info) const = 0;
};
