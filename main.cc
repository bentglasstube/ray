#include <iostream>

#include "camera.h"
#include "color.h"
#include "hittable_list.h"
#include "material.h"
#include "ray.h"
#include "sphere.h"
#include "util.h"
#include "vec3.h"

color ray_color(const ray& r, const hittable& world, int depth) {
  hit_record rec;

  if (depth <= 0) return color(0, 0, 0);

  if (world.hit(r, 0.001, infinity, rec)) {
    ray out;
    color c;

    if (rec.mat->scatter(r, rec, c, out)) {
      return c * ray_color(out, world, depth - 1);
    } else {
      return color(0, 0, 0);
    }
  }

  vec3 unit_dir = unit_vector(r.direction());
  const double t = 0.5 * (unit_dir.y() + 1.0);
  return (1.0 - t) * color(1.0, 1.0, 1.0) + t * color(0.5, 0.7, 1.0);
}

int main() {
  // Image properties
  const double aspect_ratio = 16.0 / 9.0;
  const int image_width = 512;
  const int image_height = static_cast<int>(image_width / aspect_ratio);
  const int samples_per_pixel = 50;
  const int max_depth = 50;

  // Scene
  hittable_list world;

  const auto ground = std::make_shared<lambertian>(color(0.8, 0.8, 0.0));
  const auto center = std::make_shared<lambertian>(color(0.1, 0.2, 0.5));
  const auto left   = std::make_shared<dielectric>(1.5);
  const auto right  = std::make_shared<metal>(color(0.8, 0.6, 0.2), 0.2);

  world.add(std::make_shared<sphere>(point3( 0.0, -100.5, -1.0), 100.0, ground));
  world.add(std::make_shared<sphere>(point3( 0.0,    0.0, -1.0),   0.5, center));
  world.add(std::make_shared<sphere>(point3(-1.0,    0.0, -1.0),   0.5, left));
  world.add(std::make_shared<sphere>(point3( 1.0,    0.0, -1.0),   0.5, right));
  camera cam;

  // Render

  std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

  for (int y = 0; y < image_height; ++y) {
    std::cerr << "\rScanlines remining: " << (image_height - y) << ' ' << std::flush;
    for (int x = 0; x < image_width; ++x) {
      color c(0, 0, 0);
      for (int i = 0; i < samples_per_pixel; ++i) {
        const auto u = double(x + random_double()) / (image_width - 1);
        const auto v = double(y + random_double()) / (image_height - 1);

        ray r = cam.get_ray(u, v);
        c += ray_color(r, world, max_depth);
      }

      write_color(std::cout, c, samples_per_pixel);
    }
  }

  std::cerr << "\nDone.\n";
  return 0;
}
