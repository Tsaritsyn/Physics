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
    Sphere(const sf::Vector3f& center, float radius, const sf::Color& color = sf::Color::Red);

    [[nodiscard]] float getDistance(const sf::Vector3f& point) const override;

    [[nodiscard]] std::pair<Point, float> getClosestPoint(const sf::Vector3f& point) const override;

    [[nodiscard]] bool intersectsWith(const Ray& ray) const override;

    [[nodiscard]] bool intersectsWith(const BBox& bbox) const override;

    [[nodiscard]] std::string str() const override;
};


#endif //PHYSICS_SPHERE_H
