#pragma once

#include "utils.hpp"

using utils::infinity;

class Interval {
   private:
    float m_min, m_max;

   public:
    Interval() : m_min(+infinity), m_max(-infinity) {}
    Interval(float min, float max) : m_min(min), m_max(max) {}

    float size() {
        return m_max - m_min;
    }

    bool contains(float x) {
        return m_min <= x && x <= m_max;
    }

    bool surrounds(float x) {
        return m_min < x && x < m_max;
    }

    inline float getMin() const {
        return m_min;
    }

    inline float getMax() const {
        return m_max;
    }

    inline static Interval empty() {
        return Interval(+infinity, -infinity);
    }

    inline static Interval universe() {
        return Interval(-infinity, +infinity);
    }
};
