//
// Created by Mikhail Tsaritsyn on 10.12.2021.
//

#ifndef PHYSICS_OBJECT_H
#define PHYSICS_OBJECT_H

#include <SFML/Graphics.hpp>

#include "common.hpp"
#include "Ray.h"
#include "BBox.h"

struct Point {
    sf::Vector3f pos;
    sf::Color color;
};

class Object {
protected:
    BBox m_bbox;

public:
    [[nodiscard]] virtual float getDistance(const sf::Vector3f& point) const = 0;

    /**
     * @return the closest point and the distance to it
     */
    [[nodiscard]] virtual std::pair<Point, float> getClosestPoint(const sf::Vector3f& point) const = 0;

    [[nodiscard]] virtual bool intersects(const Ray& ray) const = 0;

    /**
     * Checks for the intersection of the object with the given bounding box.
     *
     * @return false, if the intersection surely does not exist and true if it might exist (it will be more precise
     *  for simple convex objects like spheres)
     */
    [[nodiscard]] virtual bool intersects(const BBox& bbox) const = 0;
};


#endif //PHYSICS_OBJECT_H
