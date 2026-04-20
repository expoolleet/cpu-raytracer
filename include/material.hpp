#pragma once

#include "color.hpp"
#include "hittable.hpp"
#include "ray.hpp"

class Material {
   protected:
    color3 m_albedo;

   public:
    Material(color3 albedo) : m_albedo(albedo) {}

    virtual ~Material() = default;

    virtual bool scattered(const ray &rayIn, HitInfo &info, color3 &attenuation, ray &scatteredRay) const = 0;
};
