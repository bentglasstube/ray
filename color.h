#pragma once

#include "util.h"
#include "vec3.h"

#include <iostream>

void write_color(std::ostream &out, color c, int samples) {
  const double scale = 1.0 / samples;
  const double r = std::sqrt(scale * c.x());
  const double g = std::sqrt(scale * c.y());
  const double b = std::sqrt(scale * c.z());

  out << static_cast<int>(clamp(256 * r, 0, 255)) << ' '
      << static_cast<int>(clamp(256 * g, 0, 255)) << ' '
      << static_cast<int>(clamp(256 * b, 0, 255)) << '\n';
}
