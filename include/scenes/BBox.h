//
// Created by Mikhail Tsaritsyn on 12.12.2021.
//

#ifndef PHYSICS_BBOX_H
#define PHYSICS_BBOX_H

#include <SFML/Graphics.hpp>

class BBox {
    sf::Vector3f m_top,     // top left far corner
                 m_bottom;  // bottom right close corner
};


#endif //PHYSICS_BBOX_H
