#pragma once

#include <memory>

#include "hittable.h"
#include "material.h"
#include "vec3.h"

class sphere : public hittable {
  public:
    sphere() {}
    sphere(point3 center, double r, std::shared_ptr<material> m) : center_(center), radius_(r), material_(m) {};

    virtual bool hit(const ray& r, double tmin, double tmax, hit_record& rec) const override;

  private:
    point3 center_;
    double radius_;
    std::shared_ptr<material> material_;
};

bool sphere::hit(const ray& r, double tmin, double tmax, hit_record& rec) const {
  const vec3 oc = r.origin() - center_;
  const auto a = r.direction().length_squared();
  const auto half_b = dot(oc, r.direction());
  const auto c = oc.length_squared() - radius_ * radius_;
  const auto discriminant = half_b * half_b - a * c;

  if (discriminant > 0) {
    const auto root = std::sqrt(discriminant);
    auto temp = (-half_b - root) / a;
    if (temp < tmax && temp > tmin) {
      rec.t = temp;
      rec.p = r.at(rec.t);
      const vec3 outward_normal = (rec.p - center_) / radius_;
      rec.set_face_normal(r, outward_normal);
      rec.mat = material_;
      return true;
    }

    temp = (-half_b + root) / a;
    if (temp < tmax && temp > tmin) {
      rec.t = temp;
      rec.p = r.at(rec.t);
      const vec3 outward_normal = (rec.p - center_) / radius_;
      rec.set_face_normal(r, outward_normal);
      rec.mat = material_;
      return true;
    }
  }

  return false;
}
