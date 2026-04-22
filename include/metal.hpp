#pragma once

#include "material.hpp"
class Metal : public Material {
   private:
    float m_roughness;

   public:
    Metal(color3 albedo, float roughness) : Material(albedo), m_roughness(roughness) {}

    bool scattered(const ray &rayIn, HitInfo &hit, color3 &attenuation, ray &rayOut) const override {
        vec3 reflectedVec = reflect(rayIn.direction(), hit.normal);
        reflectedVec = normalize(reflectedVec) + (m_roughness * randomUnitVector());
        rayOut = ray(hit.point, reflectedVec);
        attenuation = m_albedo;
        return dot(reflectedVec, hit.normal) > 0.0f;
    }
};
