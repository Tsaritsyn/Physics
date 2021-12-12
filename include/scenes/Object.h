//
// Created by Mikhail Tsaritsyn on 10.12.2021.
//

#ifndef PHYSICS_OBJECT_H
#define PHYSICS_OBJECT_H

#include <SFML/Graphics.hpp>

#include "common.h"
#include "Ray.h"

class Object {
public:
    virtual float getDistance(const sf::Vector3f& point) = 0;

    virtual std::pair<sf::Vector3f, sf::Color> getClosestPoint(const sf::Vector3f& point) = 0;

    [[nodiscard]] virtual bool ifIntersects(const Ray& ray) const = 0;
};


#endif //PHYSICS_OBJECT_H
