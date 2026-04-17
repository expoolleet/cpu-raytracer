#pragma once

#include "hittable.hpp"
#include "ray.hpp"
#include "vec3.hpp"

class Sphere : public Hittable {
   private:
    point3 m_center;
    float m_radius;

   public:
    Sphere(point3 center, float radius) : m_center(center), m_radius(radius) {}
    Sphere() {}

    bool hit(const ray &r, Interval rayInterval, HitInfo &hitInfo) const override {
        point3 oc = m_center - r.origin();
        float a = r.direction().length_squared();
        float h = dot(r.direction(), oc);
        float c = oc.length_squared() - m_radius * m_radius;
        float discriminant = h * h - a * c;
        if (discriminant < 0) {
            return false;
        }

        float sqrtD = std::sqrt(discriminant);
        float root = (h - sqrtD) / a;
        if (!rayInterval.surrounds(root)) {
            root = (h + sqrtD) / a;
            if (!rayInterval.surrounds(root)) {
                return false;
            }
        }

        hitInfo.t = root;
        hitInfo.point = r.at(root);
        vec3 outwardNormal = (hitInfo.point - m_center) / m_radius;
        hitInfo.setFaceNormal(r, outwardNormal);
        return true;
    }

    float getRadius() const {
        return m_radius;
    }

    point3 getPosition() const {
        return m_center;
    }
};
