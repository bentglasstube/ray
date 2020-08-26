#pragma once

#include <cmath>
#include <iostream>

#include "util.h"

class vec3 {
  public:
    vec3() : e_{0, 0, 0} {}
    vec3(double x, double y, double z) : e_{x, y, z} {}

    double x() const { return e_[0]; }
    double y() const { return e_[1]; }
    double z() const { return e_[2]; }

    vec3 operator-() const { return vec3(-e_[0], -e_[1], -e_[2]); }
    double operator[](int i) const { return e_[i]; }
    double& operator[](int i) { return e_[i]; }

    vec3& operator+=(const vec3 &v) {
      e_[0] += v.e_[0];
      e_[1] += v.e_[1];
      e_[2] += v.e_[2];
      return *this;
    }

    vec3& operator*=(const double t) {
      e_[0] *= t;
      e_[1] *= t;
      e_[2] *= t;
      return *this;
    }

    vec3& operator/=(const double t) {
      return *this *= 1/t;
    }

    double length() const {
      return std::sqrt(length_squared());
    }

    double length_squared() const {
      return e_[0] * e_[0] + e_[1] * e_[1] + e_[2] * e_[2];
    }

    inline static vec3 random() {
      return vec3(random_double(), random_double(), random_double());
    }

    inline static vec3 random(double min, double max) {
      return vec3(random_double(min, max),
                  random_double(min, max),
                  random_double(min, max));
    }

  private:
    double e_[3];
};

using point3 = vec3;
using color = vec3;

inline std::ostream& operator<<(std::ostream &out, const vec3 &v) {
  return out << v.x() << ' ' << v.y() << ' ' << v.z();
}

inline vec3 operator+(const vec3 &u, const vec3 &v) {
  return vec3(u.x() + v.x(), u.y() + v.y(), u.z() + v.z());
}

inline vec3 operator-(const vec3 &u, const vec3 &v) {
  return vec3(u.x() - v.x(), u.y() - v.y(), u.z() - v.z());
}

inline vec3 operator*(const vec3 &u, const vec3 &v) {
  return vec3(u.x() * v.x(), u.y() * v.y(), u.z() * v.z());
}

inline vec3 operator*(const vec3 &v, double t) {
  return vec3(v.x() * t, v.y() * t, v.z() * t);
}

inline vec3 operator*(double t, const vec3 &v) {
  return v * t;
}

inline vec3 operator/(const vec3 &v, double t) {
  return v * (1 / t);
}

inline double dot(const vec3 &u, const vec3 &v) {
  return u.x() * v.x() + u.y() * v.y() + u.z() * v.z();
}

inline vec3 cross(const vec3 &u, const vec3 &v) {
  return vec3(u.y() * v.z() - u.z() * v.y(),
              u.z() * v.x() - u.x() * v.z(),
              u.x() * v.y() - u.y() * v.x());
}

inline vec3 unit_vector(vec3 v) {
  return v / v.length();
}

vec3 random_in_unit_sphere() {
  while (true) {
    const auto p = vec3::random(-1, 1);
    if (p.length_squared() < 1) return p;
  }
}
