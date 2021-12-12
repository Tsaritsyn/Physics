//
// Created by Mikhail Tsaritsyn on 12.12.2021.
//

#ifndef PHYSICS_OCTREE_H
#define PHYSICS_OCTREE_H

//#include <SFML/Graphics.hpp>
#include "BBox.h"
#include "Object.h"
#include "common.h"
#include <memory>

class Octree {
    BBox m_bbox;
    std::optional<std::shared_ptr<Object>> m_object{std::nullopt};
};


#endif //PHYSICS_OCTREE_H
