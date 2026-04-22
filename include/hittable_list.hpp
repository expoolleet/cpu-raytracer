#pragma once

#include <memory>
#include <vector>

#include "hittable.hpp"

using std::make_shared;
using std::shared_ptr;

class HittableList : public Hittable {
   private:
    std::vector<shared_ptr<Hittable>> m_objects;

   public:
    HittableList() {}
    HittableList(shared_ptr<Hittable> object) {
        add(object);
    }

    void add(shared_ptr<Hittable> object) {
        m_objects.push_back(object);
    }

    void clear() {
        m_objects.clear();
    }

    const std::vector<shared_ptr<Hittable>> &getList() {
        return m_objects;
    }

    bool hit(const ray &r, interval rayInterval, HitInfo &hit) const override {
        bool hitAnything = false;
        HitInfo tempHit;
        float closest = rayInterval.getMax();
        for (const auto &object : m_objects) {
            if (object->hit(r, interval(rayInterval.getMin(), closest), tempHit)) {
                hitAnything = true;
                closest = tempHit.t;
                hit = tempHit;
            }
        }

        return hitAnything;
    }
};
