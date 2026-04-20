#pragma once

#include "utils.hpp"

using utils::infinity;

class interval {
   private:
    float m_min, m_max;

   public:
    interval() : m_min(+infinity), m_max(-infinity) {}
    interval(float min, float max) : m_min(min), m_max(max) {}

    float size() {
        return m_max - m_min;
    }

    bool contains(float x) {
        return m_min <= x && x <= m_max;
    }

    bool surrounds(float x) {
        return m_min < x && x < m_max;
    }

    float getMin() const {
        return m_min;
    }

    float getMax() const {
        return m_max;
    }

    float clamp(float x) const {
        if (x < m_min) return m_min;
        if (x > m_max) return m_max;
        return x;
    }

    inline static interval empty() {
        return interval(+infinity, -infinity);
    }

    inline static interval universe() {
        return interval(-infinity, +infinity);
    }
};
