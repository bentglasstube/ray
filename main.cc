#include <iostream>

#include "color.h"
#include "ray.h"
#include "vec3.h"

color background(const ray& r) {
  vec3 unit_dir = unit_vector(r.direction());
  const auto t = 0.5 * (unit_dir.y() + 1.0);
  return (1.0 - t) * color(1.0, 1.0, 1.0) + t * color(0.5, 0.7, 1.0);
}

int main() {
  // Image properties
  const double aspect_ratio = 16.0 / 9.0;
  const int image_width = 400;
  const int image_height = static_cast<int>(image_width / aspect_ratio);

  // Camera properties
  const double viewport_height = 2.0;
  const double viewport_width = aspect_ratio * viewport_height;
  const double focal_length = 1.0;

  const auto origin = point3(0, 0, 0);
  const auto horizontal = vec3(viewport_width, 0, 0);
  const auto vertical = vec3(0, viewport_height, 0);
  const auto lower_left = origin - horizontal / 2 - vertical / 2 - vec3(0, 0, focal_length);

  // Render

  std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

  for (int y = 0; y < image_height; ++y) {
    std::cerr << "\rScanlines remining: " << (image_height - y) << ' ' << std::flush;
    for (int x = 0; x < image_width; ++x) {
      const auto u = double(x) / (image_width - 1);
      const auto v = double(y) / (image_height - 1);

      ray r(origin, lower_left + u * horizontal + v * vertical - origin);
      color c = background(r);
      write_color(std::cout, c);
    }
  }

  std::cerr << "\nDone.\n";
  return 0;
}
