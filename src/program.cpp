#include <windows.h>

#include <bitset>

#include "camera.hpp"
#include "dialectric.hpp"
#include "hittable_list.hpp"
#include "lambertian.hpp"
#include "metal.hpp"
#include "sphere.hpp"
#include "utils.hpp"
#include "vec3.hpp"

using std::make_shared;

std::pair<float, float> hammersleySequence2D(uint32_t x, int n) {
    // radical inverse vdc
    uint32_t bits = x;
    bits = (bits >> 16u) | (x << 16u);
    bits = ((bits & 0xAAAAAAAA) >> 1u) | ((bits & 0x55555555) << 1u);
    bits = ((bits & 0xCCCCCCCC) >> 2u) | ((bits & 0x33333333) << 2u);
    bits = ((bits & 0xF0F0F0F0) >> 4u) | ((bits & 0x0F0F0F0F) << 4u);
    bits = ((bits & 0xFF00FF00) >> 8u) | ((bits & 0x00FF00FF) << 8u);
    return {static_cast<float>(x) / n, bits * 2.3283064365386963e-10f};  // / 0x1000000000
}

int main(int argc, char *argv[]) {
    HittableList world;

    float earthRadius = 100.0f;
    int n = 60;
    float scale = 5.5f;
    float centerOffset = 2.0f;
    float radiusOfCenteredMetalSpehere = 1.8f;
    for (unsigned int i = 0; i < n; ++i) {
        float rand = utils::random();

        float radius = utils::random(0.3f, 0.6f);
        color3 color = color3(utils::random(), utils::random(), utils::random());
        auto randPos = hammersleySequence2D(i, n);
        float x = randPos.first * (2 * scale) - scale;
        float z = randPos.second * (2 * scale) - scale;
        float y = std::sqrtf(earthRadius * earthRadius - x * x - z * z) - earthRadius;
        if ((x >= 0.0f && x <= centerOffset && z >= 0.0f && z <= centerOffset) || (x <= 0.0f && x >= -centerOffset && z <= 0.0f && z >= -centerOffset) ||
            (x >= 0.0f && x <= centerOffset && z <= 0.0f && z >= -centerOffset) || (x <= 0.0f && x >= -centerOffset && z >= 0.0f && z <= centerOffset)) {
            continue;
        }
        point3 position = point3(x, y + radius, z);
        if (rand < 0.7f) {
            world.add(make_shared<Sphere>(position, radius, make_shared<Lambertian>(color)));
        } else if (rand < 0.95f) {
            world.add(make_shared<Sphere>(position, radius, make_shared<Metal>(color, utils::random())));
        } else {
            world.add(make_shared<Sphere>(position, radius, make_shared<Dialectric>(color, utils::random(1.0f, 1.5f))));
        }
    }

    auto materialLambertian1 = make_shared<Lambertian>(color3(0.8f, 0.8f, 0.8f));
    auto materialMetal1 = make_shared<Metal>(color3(0.7f, 0.6f, 0.5f), 0.0f);

    world.add(make_shared<Sphere>(point3(0.0f, -earthRadius, 0.0f), earthRadius, materialLambertian1));
    world.add(make_shared<Sphere>(point3(0.0f, radiusOfCenteredMetalSpehere, 0.0f), radiusOfCenteredMetalSpehere, materialMetal1));

    Camera camera;
    camera.position = point3(-5.0f, 3.0f, 7.0f);
    camera.lookAt = point3(0.0f, 0.0f, 0.0f);
    camera.vUp = vec3(0.0f, 1.0f, 0.0f);
    camera.aspectRatio = 16.0f / 9.0f;
    camera.vFov = 50.0f;
    camera.defocusAngle = 2.5f;
    camera.focusDistance = 7.0f;

    if (argc > 3) {
        camera.imageWidth = atoi(argv[1]);
        camera.sampleCount = atoi(argv[2]);
        camera.raysMaxDepth = atoi(argv[3]);
    } else {
        camera.imageWidth = 400;
        camera.sampleCount = 50;
        camera.raysMaxDepth = 10;
    }

    camera.initialize();
    camera.render(world);

    return 0;
}
