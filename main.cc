#include <iostream>

int main() {
  const int image_width = 256;
  const int image_height = 256;

  std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

  for (int y = 0; y < image_height; ++y) {
    std::cerr << "\rScanlines remining: " << (image_height - y) << ' ' << std::flush;
    for (int x = 0; x < image_width; ++x) {
      const double r = double(x) / (image_width - 1);
      const double g = double(y) / (image_height - 1);
      const double b = 0.25;

      const int rr = static_cast<int>(255.999 * r);
      const int gg = static_cast<int>(255.999 * g);
      const int bb = static_cast<int>(255.999 * b);

      std::cout << rr << ' ' << gg << ' ' << bb << '\n';
    }
  }

  std::cerr << "\nDone.\n";
  return 0;
}
