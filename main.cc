#include <iostream>

#include "color.h"
#include "vec3.h"

int main() {
  const int image_width = 256;
  const int image_height = 256;

  std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

  for (int y = 0; y < image_height; ++y) {
    std::cerr << "\rScanlines remining: " << (image_height - y) << ' ' << std::flush;
    for (int x = 0; x < image_width; ++x) {
      color pixel_color(double(x) / (image_width - 1), double(y) / (image_height - 1), 0.25);
      write_color(std::cout, pixel_color);
    }
  }

  std::cerr << "\nDone.\n";
  return 0;
}
