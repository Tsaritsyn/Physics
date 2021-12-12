//
// Created by Mikhail Tsaritsyn on 10.12.2021.
//

#include "common.h"

std::ostream& operator <<(std::ostream& os, const sf::Color& color) {
    return os << '(' << std::setw(3) << (unsigned)color.r << ", "
       << std::setw(3) << (unsigned)color.g << ", "
       << std::setw(3) << (unsigned)color.b << ", "
       << std::setw(3) << (unsigned)color.a << ')';
}
