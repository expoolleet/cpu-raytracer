#include <windows.h>

#include "camera.hpp"
#include "hittable_list.hpp"
#include "lambertian.hpp"
#include "metal.hpp"
#include "sphere.hpp"
#include "vec3.hpp"

using std::make_shared;

int main(int argc, char *argv[]) {
    HittableList world;

    auto material_ground = make_shared<Lambertian>(color3(0.8, 0.8, 0.0));
    auto material_center = make_shared<Lambertian>(color3(0.1, 0.2, 0.5));
    auto material_left = make_shared<Metal>(color3(0.8, 0.8, 0.8), 0.0f);
    auto material_right = make_shared<Metal>(color3(0.8, 0.6, 0.2), 0.3f);

    world.add(make_shared<Sphere>(point3(0.0, 0.0, -1.2), 0.5, material_center));
    world.add(make_shared<Sphere>(point3(-1.0, 0.0, -1.0), 0.5, material_left));
    world.add(make_shared<Sphere>(point3(1.0, 0.0, -1.0), 0.5, material_right));
    world.add(make_shared<Sphere>(point3(0.0, -100.5, -1.0), 100.0, material_ground));

    Camera camera;
    camera.position = point3(0.0f, 0.0f, 0.0f);
    camera.aspectRatio = 16.0 / 9.0;
    camera.imageWidth = atoi(argv[1]);
    camera.sampleCount = atoi(argv[2]);
    camera.raysMaxDepth = atoi(argv[3]);
    camera.initialize();
    camera.render(world);

    return 0;
}
