//
// Created by Mikhail Tsaritsyn on 10.12.2021.
//

#include "scenes/Sphere.h"

Sphere::Sphere(const sf::Vector3f &center, float radius, const sf::Color &color):
        m_center(center), m_radius(radius), m_color(color) {
    const sf::Vector3f radius_3d{radius, radius, radius};
    Object::m_bbox = BBox(m_center - radius_3d, m_center + radius_3d);
}

std::pair<Point, float> Sphere::getClosestPoint(const sf::Vector3f &point) const {
    float distance = norm(point - m_center);
    float alpha = m_radius / distance;
    return {{lerp(m_center, point, alpha), m_color}, distance};
}

float Sphere::getDistance(const sf::Vector3f &point) const {
    return norm(m_center - point) - m_radius;
}

bool Sphere::intersectsWith(const Ray &ray) const {
    if (!Object::m_bbox.intersectsWith(ray)) return false;

    auto center_dir = m_center - ray.getOrigin();
    auto dot_criterion = center_dir * ray.getDirection();
    if (dot_criterion < 0) return false;
    return norm2(center_dir) - dot_criterion * dot_criterion <= m_radius * m_radius;
}

bool Sphere::intersectsWith(const BBox &bbox) const {
    if (!m_bbox.intersectsWith(bbox)) return false;
    if (bbox.contains(m_bbox)) return true;

    const auto closest_point = bbox.getClosestPoint(m_center);
    return getDistance(closest_point) <= 0;
}

std::string Sphere::str() const {
    std::stringstream ss;
    ss << "Sphere with center at " << m_center << " and radius " << m_radius;
    return ss.str();
}
