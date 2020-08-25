#pragma once

#include <memory>
#include <vector>

#include "hittable.h"

class hittable_list : public hittable {
  public:
    hittable_list() {}
    hittable_list(std::shared_ptr<hittable> h) { add(h); }

    void clear() { objects_.clear(); }
    void add(std::shared_ptr<hittable> h) { objects_.push_back(h); }
    virtual bool hit(const ray& r, double tmin, double tmax, hit_record& rec) const override;

  private:
    std::vector<std::shared_ptr<hittable>> objects_;
};

bool hittable_list::hit(const ray& r, double tmin, double tmax, hit_record& rec) const {
  hit_record temp_rec;
  bool hit = false;
  double closest = tmax;

  for (const auto& object : objects_) {
    if (object->hit(r, tmin, closest, temp_rec)) {
      hit = true;
      closest = temp_rec.t;
      rec = temp_rec;
    }
  }

  return hit;
}
