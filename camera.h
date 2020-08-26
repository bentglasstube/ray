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
        double aspect_ratio,
        double aperture,
        double focus_dist
    ) {
      const double theta = degrees_to_radians(fov);
      const double h = std::tan(theta / 2.0);
      const double viewport_height = 2.0 * h;
      const double viewport_width = aspect_ratio * viewport_height;

      w_ = unit_vector(lookfrom - lookat);
      u_ = unit_vector(cross(up, w_));
      v_ = cross(w_, u_);

      origin_ = lookfrom;
      horz_ = focus_dist * viewport_width * u_;
      vert_ = focus_dist * viewport_height * v_;
      corner_ = origin_ - horz_ / 2 - vert_ / 2 - focus_dist * w_;

      lens_radius_ = aperture / 2;
    }

    ray get_ray(double s, double t) const {
      const vec3 rd = lens_radius_ * random_in_unit_disk();
      const vec3 offset = u_ * rd.x() + v_ * rd.y();

      return ray(origin_ + offset, corner_ + s * horz_ + t * vert_ - origin_ - offset);
    }

  private:
    point3 origin_, corner_;
    vec3 horz_, vert_;
    vec3 u_, v_, w_;
    double lens_radius_;
};
