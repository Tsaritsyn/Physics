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
    BBox() : m_min(float_inf, float_inf, float_inf), m_max(float_neg_inf, float_neg_inf, float_neg_inf) {};

    BBox(const sf::Vector3f &min, const sf::Vector3f &max) : m_min(min), m_max(max) {};

    [[nodiscard]] bool contains(const sf::Vector3f &point) const;

    [[nodiscard]] bool contains(const BBox &other) const;

    [[nodiscard]] bool intersectsWith(const Ray &ray) const;

    [[nodiscard]] bool intersectsWith(const BBox &other) const;

    /**
     * @return the closest point on the BBox surface if the given point is outside the BBox;
     *  a copy of the given point if it is inside the BBox
     */
    [[nodiscard]] sf::Vector3f getClosestPoint(const sf::Vector3f &p) const;

    BBox& uniteWith(const BBox &other);

    [[nodiscard]] std::vector<BBox> subdivide() const;

    [[nodiscard]] float getMinDimension() const;

    [[nodiscard]] float getMaxDimension() const;

    friend std::ostream &operator<<(std::ostream &os, const BBox &bbox);
};


#endif //PHYSICS_BBOX_H
