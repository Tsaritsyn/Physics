//
// Created by Mikhail Tsaritsyn on 10.12.2021.
//

#include "scenes/Sphere.h"

std::pair<sf::Vector3f, sf::Color> Sphere::getClosestPoint(const sf::Vector3f &point) {
    float alpha = m_radius / norm(point - m_center);
    return {lerp(m_center, point, alpha), m_color};
}

float Sphere::getDistance(const sf::Vector3f &point) {
    return norm(m_center - point) - m_radius;
}

bool Sphere::ifIntersects(const Ray &ray) const {
    auto center_dir = m_center - ray.getOrigin();
    auto dot_criterion = center_dir * ray.getDirection();
    if (dot_criterion < 0) return false;
    return norm2(center_dir) - dot_criterion * dot_criterion <= m_radius * m_radius;
}
