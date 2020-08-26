#pragma once

#include "util.h"
#include "vec3.h"

#include <iostream>

void write_color(std::ostream &out, color c, int samples) {
  const double scale = 256.0 / samples;

  out << static_cast<int>(clamp(scale * c.x(), 0, 255)) << ' '
      << static_cast<int>(clamp(scale * c.y(), 0, 255)) << ' '
      << static_cast<int>(clamp(scale * c.z(), 0, 255)) << '\n';
}
