//
// Created by Mikhail Tsaritsyn on 10.12.2021.
//

#ifndef PHYSICS_PIXELGRID_H
#define PHYSICS_PIXELGRID_H

#include <vector>
#include <optional>

#include <SFML/Graphics.hpp>

#include "common.hpp"

#define NUM_CHANNELS 4
typedef std::array<sf::Uint8, NUM_CHANNELS> PixelValue;


class PixelGrid {
    std::vector<sf::Uint8> m_pixels;
    size_t m_width, m_height;

public:
    PixelGrid(size_t height, size_t width, const std::optional<sf::Color> &value = std::nullopt);

    PixelGrid &setPixel(size_t x, size_t y, const sf::Color &color);

    [[nodiscard]] sf::Color getPixel(size_t x, size_t y) const;

    [[nodiscard]] const sf::Uint8* data() const {return m_pixels.data();};

    [[nodiscard]] size_t getHeight() const {return m_height;};

    [[nodiscard]] size_t getWidth() const {return m_width;};
};

std::ostream& operator <<(std::ostream& os, const PixelGrid& pixels);


#endif //PHYSICS_PIXELGRID_H
