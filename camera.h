#pragma once

#include "ray.h"
#include "util.h"
#include "vec3.h"

class camera {
  public:
    camera(
        point3 lookfrom,
        point3 lookat,
        vec3 up,
        double fov,
        double aspect_ratio
    ) {
      const double theta = degrees_to_radians(fov);
      const double h = std::tan(theta / 2.0);
      const double viewport_height = 2.0 * h;
      const double viewport_width = aspect_ratio * viewport_height;

      const vec3 w = unit_vector(lookfrom - lookat);
      const vec3 u = unit_vector(cross(up, w));
      const vec3 v = cross(w, u);

      origin_ = lookfrom;
      horz_ = viewport_width * u;
      vert_ = viewport_height * v;
      corner_ = origin_ - horz_ / 2 - vert_ / 2 - w;
    }

    ray get_ray(double u, double v) const {
      return ray(origin_, corner_ + u * horz_ + v * vert_ - origin_);
    }

  private:
    point3 origin_, corner_;
    vec3 horz_, vert_;
};
