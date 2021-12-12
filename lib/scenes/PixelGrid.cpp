//
// Created by Mikhail Tsaritsyn on 10.12.2021.
//

#include "scenes/PixelGrid.h"

PixelGrid::PixelGrid(size_t height, size_t width, const std::optional<sf::Color> &value)
        : m_width(width), m_height(height), m_pixels(height * width * NUM_CHANNELS) {
    if (value.has_value()) {
        for (size_t i = 0; i < height; i++)
            for (size_t j = 0; j < width; j++) {
                m_pixels[(i * width + j) * NUM_CHANNELS + 0] = value.value().r;
                m_pixels[(i * width + j) * NUM_CHANNELS + 1] = value.value().g;
                m_pixels[(i * width + j) * NUM_CHANNELS + 2] = value.value().b;
                m_pixels[(i * width + j) * NUM_CHANNELS + 3] = value.value().a;
            }
    }
}

PixelGrid &PixelGrid::setPixel(size_t x, size_t y, const sf::Color &color) {
    m_pixels[(y * m_width + x) * NUM_CHANNELS + 0] = color.r;
    m_pixels[(y * m_width + x) * NUM_CHANNELS + 1] = color.g;
    m_pixels[(y * m_width + x) * NUM_CHANNELS + 2] = color.b;
    m_pixels[(y * m_width + x) * NUM_CHANNELS + 3] = color.a;
    return *this;
}

sf::Color PixelGrid::getPixel(size_t x, size_t y) const {
    sf::Color result{};
    result.r = m_pixels[(y * m_width + x) * NUM_CHANNELS + 0];
    result.g = m_pixels[(y * m_width + x) * NUM_CHANNELS + 1];
    result.b = m_pixels[(y * m_width + x) * NUM_CHANNELS + 2];
    result.a = m_pixels[(y * m_width + x) * NUM_CHANNELS + 3];
    return result;
}

std::ostream &operator<<(std::ostream& os, const PixelGrid &pixels) {
    os << '[';
    for (size_t i = 0; i < pixels.getHeight(); i++) {
        os << ((i == 0) ? "[" : " [");
        for (size_t j = 0; j < pixels.getWidth(); j++) {
            auto value = pixels.getPixel(j, i);
            os << value;
            if (j != pixels.getWidth() - 1) os << ", ";
        }
        os << "]\n";
    }
    os << ']';
    return os;
}
