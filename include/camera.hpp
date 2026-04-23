#pragma once

#include <iostream>

#include "color.hpp"
#include "hittable_list.hpp"
#include "material.hpp"
#include "utils.hpp"

class Camera {
   private:
    size_t m_imageHeight;

    float m_viewportHeight;
    float m_viewportWidth;
    float m_pixelSampleScale;

    vec3 m_viewportU;
    vec3 m_viewportV;
    vec3 m_viewport_dU;
    vec3 m_viewport_dV;
    vec3 m_defocusDiskU;
    vec3 m_defocusDiskV;

    point3 m_topLeftPixel;
    point3 m_viewportTopLeftCorner;

    color3 _getRayColor(const ray &r, int depth, const HittableList &world) {
        if (depth <= 0) {
            return vec3(0.0f);
        }

        HitInfo info;
        if (world.hit(r, interval(0.001f, infinity), info)) {
            ray scattered;
            color3 attenuation;
            if (info.material->scattered(r, info, attenuation, scattered)) {
                return attenuation * _getRayColor(scattered, depth - 1, world);
            }
            return vec3(0.0f);
        }

        vec3 unit = normalize(r.direction());
        float a = 0.5f * (unit.y + 1.0f);
        return a * color3(0.5f, 0.7f, 1.0f) + (1.0f - a) * color3(1.0f, 1.0f, 1.0f);
    }

    vec3 _sampleSquare() {
        return {utils::random() - 0.5f, utils::random() - 0.5f, 0.0f};
    }

    vec3 _sampleDisk() {
        vec3 v = randomUnitVecOnDisk();
        return position + v.x * m_defocusDiskU + v.y * m_defocusDiskV;
    }

    ray _getRay(int i, int j) {
        vec3 offset = _sampleSquare();
        point3 pixelCenter = m_topLeftPixel + ((i + offset.x) * m_viewport_dU) + ((j + offset.y) * m_viewport_dV);
        vec3 rayOrigin = defocusAngle <= 0.0f ? position : _sampleDisk();
        vec3 rayDirection = pixelCenter - rayOrigin;
        return {rayOrigin, rayDirection};
    }

   public:
    int imageWidth = 100;
    int sampleCount = 8;
    int raysMaxDepth = 10;

    float vFov = 60.0f;
    float aspectRatio = 1.0f;
    float focusDistance = 10.0f;
    float defocusAngle = 0.0f;

    vec3 vUp = vec3(0.0f, 1.0f, 0.0f);

    point3 lookAt = point3(0.0f, 0.0f, -1.0f);
    point3 position = point3(0.0f);

    Camera() {}

    void initialize() {
        m_pixelSampleScale = 1.0f / sampleCount;

        m_imageHeight = static_cast<size_t>(imageWidth / aspectRatio);
        m_imageHeight = m_imageHeight > 1 ? m_imageHeight : 1;

        float theta = utils::degToRad(vFov);
        float h = std::tanf(theta / 2.0f);
        vec3 w = normalize(position - lookAt);
        vec3 u = normalize(cross(vUp, w));
        vec3 v = cross(w, u);

        m_viewportHeight = 2.0f * h * focusDistance;
        m_viewportWidth = m_viewportHeight * static_cast<float>(imageWidth) / m_imageHeight;

        m_viewportU = m_viewportWidth * u;
        m_viewportV = m_viewportHeight * (-v);

        m_viewportTopLeftCorner = position - focusDistance * w - 0.5f * (m_viewportU + m_viewportV);

        m_viewport_dU = m_viewportU / imageWidth;
        m_viewport_dV = m_viewportV / m_imageHeight;

        m_topLeftPixel = m_viewportTopLeftCorner + 0.5f * (m_viewport_dU + m_viewport_dV);

        float defocusRadius = focusDistance * std::tanf(utils::degToRad(defocusAngle / 2.0f));
        m_defocusDiskU = defocusRadius * u;
        m_defocusDiskV = defocusRadius * v;
    }

    void render(const HittableList &world) {
        std::cout << "P3\n"
                  << imageWidth << " " << m_imageHeight << "\n255\n";
        for (size_t j = 0; j < m_imageHeight; ++j) {
            std::clog << "\rScanlines remaining: " << (m_imageHeight - j) << ' ' << std::flush;
            for (size_t i = 0; i < imageWidth; ++i) {
                vec3 color;
                for (int s = 0; s < sampleCount; ++s) {
                    ray cameraRay = _getRay(i, j);
                    color = color + _getRayColor(cameraRay, raysMaxDepth, world);
                }
                writeColor(std::cout, m_pixelSampleScale * color);
            }
        }
        std::clog << "\rDone.                   \n";
    }
};
