//
// Created by Mikhail Tsaritsyn on 10.12.2021.
//

#ifndef PHYSICS_RAY_H
#define PHYSICS_RAY_H

#include <SFML/Graphics.hpp>

class Ray {
    sf::Vector3f m_origin, m_direction;
    sf::Color m_color;

public:
    Ray(const sf::Vector3f& origin, const sf::Vector3f& direction, const sf::Color& color)
    : m_origin(origin), m_direction(direction), m_color(color)
    {};

    [[nodiscard]] const sf::Vector3f& getOrigin() const {return m_origin;};

    [[nodiscard]] const sf::Vector3f& getDirection() const {return m_direction;};

    [[nodiscard]] const sf::Color& getColor() const {return m_color;};

    void propagate(float distance) { m_origin += m_direction * distance;};

    void changeDirection(const sf::Vector3f& new_direction) {m_direction = new_direction;};

    void setColor(const sf::Color& color) {m_color = color;};

};


#endif //PHYSICS_RAY_H
