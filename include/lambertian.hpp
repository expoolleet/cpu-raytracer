#pragma once

#include "material.hpp"
class Lambertian : public Material {
   public:
    Lambertian(color3 albedo) : Material(albedo) {}

    bool scattered(const ray &rayIn, HitInfo &hit, color3 &attenuation, ray &scatteredRay) const override {
        vec3 scatterDirection = hit.normal + randomUnitVector();
        if (nearZero(scatterDirection)) {
            scatterDirection = hit.normal;
        }

        scatteredRay = ray(hit.point, scatterDirection);
        attenuation = m_albedo;
        return true;
    }
};
