#pragma once

#include <memory>

#include "ray.h"
#include "util.h"

class material;

struct hit_record {
  point3 p;
  vec3 normal;
  std::shared_ptr<material> mat;
  double t;
  bool front_face;

  inline void set_face_normal(const ray& r, const vec3& outward_normal) {
    front_face = dot(r.direction(), outward_normal) < 0;
    normal = front_face ? outward_normal : -outward_normal;
  }
};

class hittable {
  public:
    virtual bool hit(const ray& r, double tmin, double tmax, hit_record& rec) const = 0;
};
