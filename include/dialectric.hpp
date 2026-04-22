#pragma once

#include "color.hpp"
#include "material.hpp"
#include "vec3.hpp"

class Dialectric : public Material {
   private:
    float m_refractionIndex;

   public:
    Dialectric(color3 albedo, float refractionIndex) : Material(albedo), m_refractionIndex(refractionIndex) {}

    bool scattered(const ray &rayIn, HitInfo &info, color3 &attenuation, ray &scatteredRay) const override {
        attenuation = m_albedo;
        float refractedIndexOut = info.frontFace ? 1.0f : m_refractionIndex;
        float refractedIndexIn = info.frontFace ? m_refractionIndex : 1.0f;
        vec3 unitDirection = normalize(rayIn.direction());
        scatteredRay = ray(info.point, refract(unitDirection, info.normal, refractedIndexOut, refractedIndexIn));
        return true;
    }
};
