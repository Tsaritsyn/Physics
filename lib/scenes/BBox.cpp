//
// Created by Mikhail Tsaritsyn on 12.12.2021.
//

#include "scenes/BBox.h"

static inline bool intersection_in_range(float x0, float t, float d, float x_min, float x_max) {
    return in_range(x0 + d * t, x_min, x_max);
}

bool BBox::contains(const sf::Vector3f &point) const {
    return (in_range(point.x, m_min.x, m_max.x)
            && in_range(point.y, m_min.y, m_max.y)
            && in_range(point.z, m_min.z, m_max.z));
}

bool BBox::intersectsWith(const Ray &ray) const {
    const auto o = ray.getOrigin();
    const auto d = ray.getDirection();

//    if the origin of the ray in inside the bbox, then it surely intersectsWith with it
    if (contains(o)) return true;

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

bool BBox::intersectsWith(const BBox &other) const {
    if (other.contains(*this) || contains(other)) return true;

//    they intersect if any vertex of the other lies inside this one or vice versa
    return contains(other.m_min)
        || contains(other.m_max)
        || contains({other.m_min.x, other.m_max.y, other.m_max.z})
        || contains({other.m_max.x, other.m_min.y, other.m_max.z})
        || contains({other.m_min.x, other.m_min.y, other.m_max.z})
        || contains({other.m_max.x, other.m_max.y, other.m_min.z})
        || contains({other.m_min.x, other.m_max.y, other.m_min.z})
        || contains({other.m_max.x, other.m_min.y, other.m_min.z})
        ||
           other.contains(m_min)
        || other.contains(m_max)
        || other.contains({m_min.x, m_max.y, m_max.z})
        || other.contains({m_max.x, m_min.y, m_max.z})
        || other.contains({m_min.x, m_min.y, m_max.z})
        || other.contains({m_max.x, m_max.y, m_min.z})
        || other.contains({m_min.x, m_max.y, m_min.z})
        || other.contains({m_max.x, m_min.y, m_min.z});
}

sf::Vector3f BBox::getClosestPoint(const sf::Vector3f &p) const {
    return {
            clip(p.x, m_min.x, m_max.x),
            clip(p.y, m_min.y, m_max.y),
            clip(p.z, m_min.z, m_max.z)
            };
}

BBox &BBox::uniteWith(const BBox &other) {
    m_min.x = std::min(m_min.x, other.m_min.x);
    m_min.y = std::min(m_min.y, other.m_min.y);
    m_min.z = std::min(m_min.z, other.m_min.z);

    m_max.x = std::max(m_max.x, other.m_max.x);
    m_max.y = std::max(m_max.y, other.m_max.y);
    m_max.z = std::max(m_max.z, other.m_max.z);

    return *this;
}

std::vector<BBox> BBox::subdivide() const {
    auto hd = (m_max - m_min) / 2.f;    // half diagonal
    const std::vector<sf::Vector3f> minimums{
        m_min,
        m_min + sf::Vector3f{hd.x, 0., 0.},
        m_min + sf::Vector3f{0., hd.y, 0.},
        m_min + sf::Vector3f{0., 0., hd.z},
        m_min + sf::Vector3f{hd.x, hd.y, 0.},
        m_min + sf::Vector3f{hd.x, 0., hd.z},
        m_min + sf::Vector3f{0., hd.y, hd.z},
        m_min + hd
    };
    std::vector<BBox> result;
    result.reserve(minimums.size());
    for (const auto& sub_min: minimums)
        result.emplace_back(sub_min, sub_min + hd);
    return result;
}

std::ostream &operator<<(std::ostream &os, const BBox &bbox) {
    return os << "BBox(" << bbox.m_min << ": " << bbox.m_max << ')';
}

float BBox::getMinDimension() const {
    auto diagonal = m_max - m_min;
    return std::min(diagonal.x, std::min(diagonal.y, diagonal.z));
}

float BBox::getMaxDimension() const {
    auto diagonal = m_max - m_min;
    return norm(diagonal);
}

