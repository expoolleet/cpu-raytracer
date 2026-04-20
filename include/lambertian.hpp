#pragma once

#include "material.hpp"
class Lambertian : public Material {
   public:
    Lambertian(color3 albedo) : Material(albedo) {}

    bool scattered(const ray &rayIn, HitInfo &info, color3 &attenuation, ray &scatteredRay) const override {
        vec3 scatterDirection = info.normal + randomUnitVector();
        if (nearZero(scatterDirection)) {
            scatterDirection = info.normal;
        }

        scatteredRay = ray(info.point, scatterDirection);
        attenuation = m_albedo;
        return true;
    }
};
