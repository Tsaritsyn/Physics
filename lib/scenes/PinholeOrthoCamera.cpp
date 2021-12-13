//
// Created by Mikhail Tsaritsyn on 13.12.2021.
//

#include "scenes/PinholeOrthoCamera.h"

PinholeOrthoCamera::PinholeOrthoCamera(const sf::Vector3f &origin, const sf::Vector3f &view_direction,
                                       const sf::Vector3f &grid_horizontal_axis, float fov,
                                       const sf::Vector2u &grid_size):
        Camera{origin, grid_size} {
    if (std::abs(view_direction * grid_horizontal_axis) > epsilon) throw std::invalid_argument("Grid axis must be orthogonal to the direction of view");

    auto x_prime = normalize(grid_horizontal_axis);
    auto z_prime = normalize(view_direction);
    auto y_prime = cross_product(z_prime, x_prime);
    auto forward_matrix = Matrix3f(x_prime, y_prime, z_prime);
    m_trans_matrix = forward_matrix.inverse();

    m_fov.x = fov / 180.f * M_PIf32;
    m_fov.y = m_fov.x / getWidth() * getHeight();

    m_px2m = 2.f * sf::Vector2f{(float)tan(m_fov.x / 2) / getWidth(), (float)tan(m_fov.y / 2) / getHeight()};
}

Ray PinholeOrthoCamera::sampleRay(unsigned int x, unsigned int y) {
    sf::Vector3f intrinsic_ray{
            ((float)getWidth() / 2 - x) * m_px2m.x,
            ((float)getHeight() / 2 - y) * m_px2m.y,
            1.f
    };
    return {m_origin, m_trans_matrix * normalize(intrinsic_ray), sf::Color::Black};
}
