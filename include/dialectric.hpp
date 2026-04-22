#pragma once

#include "color.hpp"
#include "material.hpp"
#include "vec3.hpp"

class Dialectric : public Material {
   private:
    float m_refractionIndex;

    // Shlick's approximation for reflectance
    static float _reflectance(float cosTheta, float refractionIndex) {
        float r0 = (1.0f - refractionIndex) / (1.0f + refractionIndex);
        r0 = r0 * r0;
        return r0 + (1.0f - r0) * std::pow(1.0f - cosTheta, 5);
    }

   public:
    Dialectric(color3 albedo, float refractionIndex) : Material(albedo), m_refractionIndex(refractionIndex) {}

    bool scattered(const ray &rayIn, HitInfo &hit, color3 &attenuation, ray &scatteredRay) const override {
        float refractionIndex = hit.frontFace ? (1.0f / m_refractionIndex) : m_refractionIndex;
        vec3 normalizedRayDir = normalize(rayIn.direction());

        float cosTheta = std::fmin(dot(-normalizedRayDir, hit.normal), 1.0f);
        float sinTheta = std::sqrt(1.0f - cosTheta * cosTheta);

        bool cannotRefract = refractionIndex * sinTheta > 1.0f;

        vec3 scatteredDir;
        if (cannotRefract || _reflectance(cosTheta, refractionIndex) > utils::random()) {
            scatteredDir = reflect(normalizedRayDir, hit.normal);
        } else {
            scatteredDir = refract(normalizedRayDir, hit.normal, refractionIndex);
        }
        scatteredRay = ray(hit.point, scatteredDir);
        attenuation = m_albedo;
        return true;
    }
};
