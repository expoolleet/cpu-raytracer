#include <windows.h>

#include "camera.hpp"
#include "hittable_list.hpp"
#include "sphere.hpp"
#include "vec3.hpp"

int main() {
    HittableList world;
    world.add(make_shared<Sphere>(point3(0, 0, -1), 0.5));
    world.add(make_shared<Sphere>(point3(0, -100.5, -1), 100));

    Camera camera;
    camera.aspectRatio = 16.0 / 9.0;
    camera.imageWidth = 400;
    camera.initialize();
    camera.render(world);

    return 0;
}
