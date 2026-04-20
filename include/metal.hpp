#pragma once

#include "material.hpp"
class Metal : public Material {
   private:
    float m_roughness;

   public:
    Metal(color3 albedo, float roughness) : Material(albedo), m_roughness(roughness) {}

    bool scattered(const ray &rayIn, HitInfo &info, color3 &attenuation, ray &rayOut) const override {
        vec3 reflectedVec = reflect(rayIn.direction(), info.normal);
        reflectedVec = normalize(reflectedVec) + (m_roughness * randomUnitVector());
        rayOut = ray(info.point, reflectedVec);
        attenuation = m_albedo;
        return dot(reflectedVec, info.normal) > 0.0f;
    }
};
