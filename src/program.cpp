#include <windows.h>

#include "camera.hpp"
#include "dialectric.hpp"
#include "hittable_list.hpp"
#include "lambertian.hpp"
#include "metal.hpp"
#include "sphere.hpp"
#include "vec3.hpp"

using std::make_shared;

int main(int argc, char *argv[]) {
    HittableList world;

    auto materialLambertian1 = make_shared<Lambertian>(color3(0.8f, 0.8f, 0.0f));
    auto materialLambertian2 = make_shared<Lambertian>(color3(0.1f, 0.2f, 0.5f));
    auto materialDialectric1 = make_shared<Dialectric>(color3(1.0f, 1.0f, 1.0f), 1.5f);
    auto materialDialectric2 = make_shared<Dialectric>(color3(1.0f, 1.0f, 1.0f), 1.0f / 1.5f);
    auto materialMetal1 = make_shared<Metal>(color3(0.8f, 0.6f, 0.2f), 0.3f);

    world.add(make_shared<Sphere>(point3(0.0f, -100.5f, -1.0f), 100.0f, materialLambertian1));
    world.add(make_shared<Sphere>(point3(0.0f, 0.0f, -1.2f), 0.5f, materialLambertian2));
    world.add(make_shared<Sphere>(point3(1.0f, 0.0f, -1.0f), 0.5f, materialMetal1));
    world.add(make_shared<Sphere>(point3(-1.0f, 0.0f, -1.0f), 0.4f, materialDialectric2));
    world.add(make_shared<Sphere>(point3(-1.0f, 0.0f, -1.0f), 0.5f, materialDialectric1));

    Camera camera;
    camera.position = point3(0.0f, 0.0f, 0.0f);
    camera.aspectRatio = 16.0f / 9.0f;

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
