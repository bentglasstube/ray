#pragma once

#include "ray.h"
#include "util.h"

class camera {
  public:
    camera() {
      const double aspect_ratio = 16.0 / 9.0;
      const double viewport_height = 2.0;
      const double viewport_width = aspect_ratio * viewport_height;
      const double focal_length = 1.0;

      origin_ = point3(0, 0, 0);
      horz_ = vec3(viewport_width, 0, 0);
      vert_ = vec3(0, -viewport_height, 0);
      corner_ = origin_ - horz_ / 2 - vert_ / 2 - vec3(0, 0, focal_length);
    }

    ray get_ray(double u, double v) const {
      return ray(origin_, corner_ + u * horz_ + v * vert_ - origin_);
    }

  private:
    point3 origin_, corner_;
    vec3 horz_, vert_;
};
