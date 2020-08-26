#pragma once

#include "util.h"
#include "vec3.h"

struct hit_record;

class material {
  public:
    virtual bool scatter(const ray& r, const hit_record& rec, color& c, ray& out) const = 0;
};

class lambertian : public material {
  public:
    lambertian(const color& c) : albedo_(c) {}

    virtual bool scatter(const ray& r, const hit_record& rec, color& c, ray& out) const override {
      const vec3 dir = rec.normal + random_unit_vector();
      out = ray(rec.p, dir);
      c = albedo_;
      return true;
    }

  private:
    color albedo_;
};

class metal : public material {
  public:
    metal(const color& a, double fuzz) : albedo_(a), fuzz_(fuzz < 1 ? fuzz : 1) {}

    virtual bool scatter(const ray& r, const hit_record& rec, color& c, ray& out) const override {
      vec3 reflected = reflect(unit_vector(r.direction()), rec.normal);
      out = ray(rec.p, reflected + fuzz_ * random_in_unit_sphere());
      c = albedo_;
      return dot(out.direction(), rec.normal) > 0;
    }

  private:
    color albedo_;
    double fuzz_;
};

double shlick(double cosine, double index) {
  double r0 = (1 - index) / (1 + index);
  r0 = r0 * r0;
  return r0 + (1 - r0) * std::pow(1 - cosine, 5);
}

class dielectric : public material {
  public:
    dielectric(double index) : index_(index) {}

    virtual bool scatter(const ray& r, const hit_record& rec, color& c, ray& out) const override {
      c = color(1.0, 1.0, 1.0);
      const double ratio = rec.front_face ? (1.0 / index_) : index_;
      const vec3 dir = unit_vector(r.direction());

      const double cos_theta = std::min(dot(-dir, rec.normal), 1.0);
      const double sin_theta = std::sqrt(1.0 - cos_theta * cos_theta);

      if (ratio * sin_theta > 1.0 || random_double() < shlick(cos_theta, ratio)) {
        out = ray(rec.p, reflect(dir, rec.normal));
      } else {
        out = ray(rec.p, refract(dir, rec.normal, ratio));
      }

      return true;
    }

  private:
    double index_;
};
