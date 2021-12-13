//
// Created by Mikhail Tsaritsyn on 10.12.2021.
//

#ifndef PHYSICS_CAMERA_H
#define PHYSICS_CAMERA_H

#include <SFML/Graphics.hpp>

#include "PixelGrid.h"
#include "Ray.h"

class Camera {
protected:
    PixelGrid m_grid;
    sf::Vector3f m_origin;

public:
    /**
     * @param origin origin of the camera
     * @param grid_size size of its grid in pixels (horizontal, vertical)
     */
    Camera(const sf::Vector3f& origin, const sf::Vector2u& grid_size): m_origin(origin), m_grid(grid_size.y, grid_size.x) {};

    /**
     * Samples ray for a specified pixel
     *
     * @param x horizontal coordinate of the pixel
     * @param y vertical coordinate of the pixel
     * @return a ray with direction of that of the camera and going through the given pixel determining its color
     */
    [[nodiscard]] virtual Ray sampleRay(unsigned x, unsigned y) = 0;

    /**
     * Changes the color of the given pixel wrt the given value.
     */
    virtual void updatePixel(unsigned x, unsigned y, const sf::Color& color) = 0;

    /**
     * @return height of the camera grid in pixels
     */
    unsigned getHeight() {return m_grid.getHeight();};

    /**
     * @return width of the camera grid in pixels
     */
    unsigned getWidth() {return m_grid.getWidth();};

    /**
     * @return the pixel grid of the camera
     */
    [[nodiscard]] const PixelGrid& getView() const {return m_grid;};
};


#endif //PHYSICS_CAMERA_H
