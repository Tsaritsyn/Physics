//
// Created by Mikhail Tsaritsyn on 10.12.2021.
//

#include "common.hpp"

std::ostream& operator <<(std::ostream& os, const sf::Color& color) {
    return os << '(' << std::setw(3) << (unsigned)color.r << ", "
              << std::setw(3) << (unsigned)color.g << ", "
              << std::setw(3) << (unsigned)color.b << ", "
              << std::setw(3) << (unsigned)color.a << ')';
}

sf::Vector3f normalize(const sf::Vector3f& v) {return v / norm(v);}

sf::Vector2f normalize(const sf::Vector2f& v) {return v / norm(v);}