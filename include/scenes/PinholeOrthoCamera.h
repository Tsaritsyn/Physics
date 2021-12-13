//
// Created by Mikhail Tsaritsyn on 13.12.2021.
//

#ifndef PHYSICS_PINHOLEORTHOCAMERA_H
#define PHYSICS_PINHOLEORTHOCAMERA_H

#include "Camera.h"
#include "common.hpp"

class PinholeOrthoCamera: public Camera {
    Matrix3f m_trans_matrix;    // matrix that transforms intrinsic camera coordinates to world coordinates (backward matrix)
    sf::Vector2f m_fov;         // field of view in degrees (horizontal, vertical)
    sf::Vector2f m_px2m;        // scaling from pixel coordinates on the grid to metres

public:
    /**
     * @param origin origin of the camera that will be the origin of all samped rays
     * @param view_direction direction of the camera's gaze
     * @param grid_horizontal_axis horizontal axis of the grid (must be orthogonal to the view direction)
     * @param fov horizontal Field of View for the camera in degrees
     * @param grid_size size of the camera grid in pixels (horizontal, vertical)
     */
    PinholeOrthoCamera(
            const sf::Vector3f& origin,
            const sf::Vector3f& view_direction,
            const sf::Vector3f& grid_horizontal_axis,
            float fov,
            const sf::Vector2u& grid_size
            );

    [[nodiscard]] Ray sampleRay(unsigned x, unsigned y) override;

    void updatePixel(unsigned x, unsigned y, const sf::Color& color) override {Camera::m_grid.setPixel(x, y, color);};
};


#endif //PHYSICS_PINHOLEORTHOCAMERA_H
