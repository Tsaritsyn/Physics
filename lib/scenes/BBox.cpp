//
// Created by Mikhail Tsaritsyn on 12.12.2021.
//

#include "scenes/BBox.h"

static inline bool intersection_in_range(float x0, float t, float d, float x_min, float x_max) {
    return in_range(x0 + d * t, x_min, x_max);
}

bool BBox::contains(const sf::Vector3f &point) const {
    return (in_interval(point.x, m_min.x, m_max.x)
            && in_interval(point.y, m_min.y, m_max.y)
            && in_interval(point.z, m_min.z, m_max.z));
}

bool BBox::intersects(const Ray &ray) const {
    const auto o = ray.getOrigin();
    const auto d = ray.getDirection();

//    auto x_inside = in_interval(o.x, m_min.x, m_max.x);
//    auto y_inside = in_interval(o.y, m_min.y, m_max.y);
//    auto z_inside = in_interval(o.z, m_min.z, m_max.z);
//    if the origin of the ray in inside the bbox, then it surely intersects with it
    if (contains(o)) return true;
//    if (x_inside && y_inside && z_inside) return true;

    if (!in_interval(o.x, m_min.x, m_max.x)) {
        float t = -1;
        if (o.x <= m_min.x) t = (m_min.x - o.x) / d.x;
        else if (o.x >= m_max.x) t = (m_max.x - o.x) / d.x;
        if (t >= 0
            && intersection_in_range(o.y, t, d.y, m_min.y, m_max.y)
            && intersection_in_range(o.z, t, d.z, m_min.z, m_max.z)
            )
            return true;
    }

    if (!in_interval(o.y, m_min.y, m_max.y)) {
        float t = -1;
        if (o.y <= m_min.y) t = (m_min.y - o.y) / d.y;
        else if (o.y >= m_max.y) t = (m_max.y - o.y) / d.y;
        if (t >= 0
            && intersection_in_range(o.x, t, d.x, m_min.x, m_max.x)
            && intersection_in_range(o.z, t, d.z, m_min.z, m_max.z)
            )
            return true;
    }

    if (!in_interval(o.z, m_min.z, m_max.z)) {
        float t = -1;
        if (o.z <= m_min.z) t = (m_min.z - o.z) / d.z;
        else if (o.z >= m_max.z) t = (m_max.z - o.z) / d.z;
        if (t >= 0
            && intersection_in_range(o.y, t, d.y, m_min.y, m_max.y)
            && intersection_in_range(o.x, t, d.x, m_min.x, m_max.x)
            )
            return true;
    }

    return false;
}

bool BBox::contains(const BBox &other) const {
    return (contains(other.m_min) && contains(other.m_max));
}

bool BBox::intersects(const BBox &other) const {
    if (other.contains(*this) || contains(other)) return true;

//    they intersect if any vertex of the other lies inside this one
    return contains(other.m_min)
        || contains(other.m_max)
        || contains({other.m_min.x, other.m_max.y, other.m_max.z})
        || contains({other.m_max.x, other.m_min.y, other.m_max.z})
        || contains({other.m_min.x, other.m_min.y, other.m_max.z})
        || contains({other.m_max.x, other.m_max.y, other.m_min.z})
        || contains({other.m_min.x, other.m_max.y, other.m_min.z})
        || contains({other.m_max.x, other.m_min.y, other.m_min.z});
}

sf::Vector3f BBox::getClosestPoint(const sf::Vector3f &p) const {
    return {
            clip(p.x, m_min.x, m_max.x),
            clip(p.y, m_min.y, m_max.y),
            clip(p.z, m_min.z, m_max.z)
            };
}

