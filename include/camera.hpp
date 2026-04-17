#pragma once

#include <iostream>

#include "color.hpp"
#include "hittable_list.hpp"

class Camera {
   private:
    size_t m_imageHeight;
    float m_focalLength;
    float m_viewportHeight;
    float m_viewportWidth;
    point3 m_center;
    vec3 m_viewportU;
    vec3 m_viewportV;
    point3 m_viewportTopLeftCorner;
    vec3 m_viewport_dU;
    vec3 m_viewport_dV;
    point3 m_topLeftPixel;

    color3 _rayColor(const ray &r, const HittableList &world) {
        HitInfo info;
        if (world.hit(r, Interval(0.0f, infinity), info)) {
            return 0.5 * (info.normal + color3(1.0f));
        }

        vec3 unit = unitVector(r.direction());
        float a = 0.5f * (unit.y + 1.0f);
        return a * color3(0.5f, 0.7f, 1.0f) + (1.0f - a) * color3(1.0f, 1.0f, 1.0f);
    }

   public:
    int imageWidth = 100;
    float aspectRatio = 1.0f;

    Camera() {}

    void render(const HittableList &world) {
        std::cout << "P3\n"
                  << imageWidth << " " << m_imageHeight << "\n255\n";
        for (size_t j = 0; j < m_imageHeight; ++j) {
            std::clog << "\rScanlines remaining: " << (m_imageHeight - j) << ' ' << std::flush;
            for (size_t i = 0; i < imageWidth; ++i) {
                point3 pixelCenter = m_topLeftPixel + (i * m_viewport_dU) + (j * m_viewport_dV);
                vec3 direction = pixelCenter - m_center;
                ray cameraRay{m_center, direction};

                color3 color = _rayColor(cameraRay, world);
                writeColor(std::cout, color);
            }
        }
        std::clog << "\rDone.               \n";
    }

    void initialize() {
        m_imageHeight = static_cast<size_t>(imageWidth / aspectRatio);
        m_imageHeight = m_imageHeight > 1 ? m_imageHeight : 1;
        m_focalLength = 1.0f;
        m_viewportHeight = 2.0f;
        m_viewportWidth = m_viewportHeight * static_cast<float>(imageWidth) / m_imageHeight;
        m_center = point3(0.0f, 0.0f, 0.0f);
        m_viewportU = vec3(m_viewportWidth, 0.0f, 0.0f);
        m_viewportV = vec3(0.0f, -m_viewportHeight, 0.0f);
        m_viewportTopLeftCorner = m_center - vec3(0.0f, 0.0f, m_focalLength) - 0.5f * (m_viewportU + m_viewportV);
        m_viewport_dU = m_viewportU / imageWidth;
        m_viewport_dV = m_viewportV / m_imageHeight;
        m_topLeftPixel = m_viewportTopLeftCorner + 0.5f * (m_viewport_dU + m_viewport_dV);
    }
};
