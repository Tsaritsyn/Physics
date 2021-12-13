//
// Created by Mikhail Tsaritsyn on 10.12.2021.
//

#ifndef PHYSICS_SPHERE_H
#define PHYSICS_SPHERE_H

#include "Object.h"

class Sphere: public Object {
    sf::Vector3f m_center;
    float m_radius;
    sf::Color m_color;

public:
    Sphere(const sf::Vector3f& center, float radius, const sf::Color& color = sf::Color::Red): m_center(center), m_radius(radius), m_color(color) {};

    float getDistance(const sf::Vector3f& point) override;

    std::pair<sf::Vector3f, sf::Color> getClosestPoint(const sf::Vector3f& point) override;

    [[nodiscard]] bool intersects(const Ray& ray) const override;
};


#endif //PHYSICS_SPHERE_H
