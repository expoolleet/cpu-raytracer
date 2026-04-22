#pragma once

#include <iostream>

#include "color.hpp"
#include "hittable_list.hpp"
#include "material.hpp"
#include "utils.hpp"

class Camera {
   private:
    size_t m_imageHeight;
    float m_focalLength;
    float m_viewportHeight;
    float m_viewportWidth;
    vec3 m_viewportU;
    vec3 m_viewportV;
    point3 m_viewportTopLeftCorner;
    vec3 m_viewport_dU;
    vec3 m_viewport_dV;
    point3 m_topLeftPixel;
    float m_pixelSampleScale;

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

    vec3 _getSampleSquare() {
        return {utils::random() - 0.5f, utils::random() - 0.5f, 0.0f};
    }

    ray _getRay(int i, int j) {
        vec3 offset = _getSampleSquare();
        point3 pixelCenter = m_topLeftPixel + ((i + offset.x) * m_viewport_dU) + ((j + offset.y) * m_viewport_dV);
        vec3 direction = pixelCenter - position;
        ray cameraRay{position, direction};
        return cameraRay;
    }

   public:
    int imageWidth = 100;
    float aspectRatio = 1.0f;
    int sampleCount = 8;
    int raysMaxDepth = 10;
    point3 position = point3(0.0f);

    Camera() {}

    void initialize() {
        m_imageHeight = static_cast<size_t>(imageWidth / aspectRatio);
        m_imageHeight = m_imageHeight > 1 ? m_imageHeight : 1;
        m_focalLength = 1.0f;
        m_viewportHeight = 2.0f;
        m_viewportWidth = m_viewportHeight * static_cast<float>(imageWidth) / m_imageHeight;
        m_viewportU = vec3(m_viewportWidth, 0.0f, 0.0f);
        m_viewportV = vec3(0.0f, -m_viewportHeight, 0.0f);
        m_viewportTopLeftCorner = position - vec3(0.0f, 0.0f, m_focalLength) - 0.5f * (m_viewportU + m_viewportV);
        m_viewport_dU = m_viewportU / imageWidth;
        m_viewport_dV = m_viewportV / m_imageHeight;
        m_topLeftPixel = m_viewportTopLeftCorner + 0.5f * (m_viewport_dU + m_viewport_dV);
        m_pixelSampleScale = 1.0f / sampleCount;
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
