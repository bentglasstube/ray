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
    metal(const color& a) : albedo_(a) {}

    virtual bool scatter(const ray& r, const hit_record& rec, color& c, ray& out) const override {
      vec3 reflected = reflect(unit_vector(r.direction()), rec.normal);
      out = ray(rec.p, reflected);
      c = albedo_;
      return dot(out.direction(), rec.normal) > 0;
    }

  private:
    color albedo_;
};
