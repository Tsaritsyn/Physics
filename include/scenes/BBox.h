//
// Created by Mikhail Tsaritsyn on 12.12.2021.
//

#ifndef PHYSICS_BBOX_H
#define PHYSICS_BBOX_H

#include <memory>

#include <SFML/Graphics.hpp>

#include "Ray.h"
#include "common.hpp"

class BBox {
    sf::Vector3f m_min, m_max;

public:
    BBox() = default;

    BBox(const sf::Vector3f& min, const sf::Vector3f& max): m_min(min), m_max(max) {};

    [[nodiscard]] bool contains(const sf::Vector3f& point) const;

    [[nodiscard]] bool contains(const BBox& other) const;

    [[nodiscard]] bool intersects(const Ray& ray) const;

    [[nodiscard]] bool intersects(const BBox& other) const;

    [[nodiscard]] sf::Vector3f getCenter() const {return (m_min + m_max) / 2.f;};

//    [[nodiscard]] const sf::Vector3f& getMin() const {return m_min;};

//    [[nodiscard]] const sf::Vector3f& getMax() const {return m_max;};

    /**
     * @return the closest point on the BBox surface if the given point is outside the BBox;
     *  a copy of the given point if it is inside the BBox
     */
    [[nodiscard]] sf::Vector3f getClosestPoint(const sf::Vector3f& p) const;
};


#endif //PHYSICS_BBOX_H
