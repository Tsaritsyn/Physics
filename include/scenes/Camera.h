//
// Created by Mikhail Tsaritsyn on 10.12.2021.
//

#ifndef PHYSICS_CAMERA_H
#define PHYSICS_CAMERA_H

#include <SFML/Graphics.hpp>

#include "PixelGrid.h"
#include "Ray.h"

class Camera {
    sf::Vector3f m_origin, m_direction;
    sf::Vector2f m_size;        // size of the grid in meters
    PixelGrid m_grid;
    sf::Vector2f m_mpp; // metres per pixel

    sf::Vector3f pixelPos(unsigned x, unsigned y) const;

public:
    Camera(const sf::Vector3f& origin, const sf::Vector3f& direction, const sf::Vector2f& size, const sf::Vector2u& grid_size)
    : m_origin(origin), m_direction(direction), m_size(size), m_grid(grid_size.y, grid_size.x),
      m_mpp(size.x / grid_size.x, size.y / grid_size.y)
    {};

    [[nodiscard]] Ray sampleRay(unsigned x, unsigned y) const;

    void updatePixel(unsigned x, unsigned y, const sf::Color& color) { m_grid.setPixel(x, y, color);};

    [[nodiscard]] unsigned getHeight() const {return m_grid.getHeight();};

    [[nodiscard]] unsigned getWidth() const {return m_grid.getWidth();};

    [[nodiscard]] const PixelGrid& getView() const {return m_grid;};
};


#endif //PHYSICS_CAMERA_H
