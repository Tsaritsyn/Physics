//
// Created by Mikhail Tsaritsyn on 10.12.2021.
//

#include "scenes/Camera.h"

Ray Camera::sampleRay(unsigned int x, unsigned int y) const {
    return {sf::Vector3(pixelPos(x, y)), sf::Vector3(m_direction), sf::Color()};
}

sf::Vector3f Camera::pixelPos(unsigned int x, unsigned int y) const {
    sf::Vector2i shift((int)x - (int)m_grid.getWidth() / 2, (int)y - (int)m_grid.getHeight() / 2);
    return {m_origin.x, shift.x * m_mpp.x, shift.y * m_mpp.y};
}
