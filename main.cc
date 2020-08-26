#include <iostream>
#include <memory>

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

hittable_list random_scene() {
  hittable_list world;

  auto ground = std::make_shared<lambertian>(color(0.5, 0.5, 0.5));
  world.add(std::make_shared<sphere>(point3(0, -1000, 0), 1000, ground));

  for (int a = -11; a < 11; ++a) {
    for (int b = -11; b < 11; ++b) {
      const point3 center(a + 0.9 * random_double(), 0.2, b + 0.9 * random_double());

      if ((center - point3(4, 0.2, 0)).length() > 0.9) {
        const double rmat = random_double();
        std::shared_ptr<material> mat;

        if (rmat < 0.8) {
          const color albedo = color::random() * color::random();
          mat = std::make_shared<lambertian>(albedo);
        } else if (rmat < 0.95) {
          const color albedo = color::random(0.5, 1);
          const double fuzz = random_double(0, 0.5);
          mat = std::make_shared<metal>(albedo, fuzz);
        } else {
          mat = std::make_shared<dielectric>(1.5);
        }

        world.add(std::make_shared<sphere>(center, 0.2, mat));
      }
    }
  }

  world.add(std::make_shared<sphere>(point3(0, 1, 0), 1.0, std::make_shared<dielectric>(1.5)));
  world.add(std::make_shared<sphere>(point3(-4, 1, 0), 1.0, std::make_shared<lambertian>(color(0.4, 0.2, 0.1))));
  world.add(std::make_shared<sphere>(point3(4, 1, 0), 1.0, std::make_shared<metal>(color(0.7, 0.6, 0.5), 0.5)));

  return world;
}

int main() {
  // Image properties
  const double aspect_ratio = 16.0 / 9.0;
  const int image_width = 1280;
  const int image_height = static_cast<int>(image_width / aspect_ratio);
  const int samples_per_pixel = 500;
  const int max_depth = 50;

  // Scene
  hittable_list world = random_scene();

  // Camera
  const point3 lookfrom(13, 2, 3);
  const point3 lookat(0, 0, 0);
  const vec3 up(0, 1, 0);
  const double dist_to_focus = 10.0;
  const double aperture = 0.1;

  camera cam(lookfrom, lookat, up, 20, aspect_ratio, aperture, dist_to_focus);

  // Render

  std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

  for (int y = image_height - 1; y >= 0; --y) {
    std::cerr << "\rScanlines remaining: " << y << ' ' << std::flush;
    for (int x = 0; x < image_width; ++x) {
      color c(0, 0, 0);
      for (int i = 0; i < samples_per_pixel; ++i) {
        const auto u = (x + random_double()) / (image_width - 1);
        const auto v = (y + random_double()) / (image_height - 1);
        ray r = cam.get_ray(u, v);
        c += ray_color(r, world, max_depth);
      }

      write_color(std::cout, c, samples_per_pixel);
    }
  }

  std::cerr << "\nDone.\n";
  return 0;
}
