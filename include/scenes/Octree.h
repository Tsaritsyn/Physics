//
// Created by Mikhail Tsaritsyn on 12.12.2021.
//

#ifndef PHYSICS_OCTREE_H
#define PHYSICS_OCTREE_H

#include <memory>
#include <unordered_set>
#include <utility>

//#include <SFML/Graphics.hpp>
#include "BBox.h"
#include "Object.h"
#include "common.hpp"

class Octree {
    BBox m_bbox;
    std::unordered_set<std::shared_ptr<Object>> m_objects{};
    std::vector<std::shared_ptr<Octree>> m_children{};
//    std::shared_ptr<Octree> m_parent{};

public:
    Octree() = default;

    explicit Octree(const BBox& bbox): m_bbox(bbox) {};

    /**
     * Stores the given set of objects in the tree. The bounding box of the current node will be divided and children
     * will be created until no objects or a single object remain or the minimum size is reached, that means that some
     * objects intersect and cannot be separated.
     *
     * @param objects set of objects that need to be filled in
     * @param min_size minimum size that a bounding box of a tree node may have
     */
    void fill_with(const std::unordered_set<std::shared_ptr<Object>>& objects, float min_size = 1.f);

    [[nodiscard]] std::unordered_set<std::shared_ptr<Object>> getIntersectingObjects(const Ray& ray) const;

    [[nodiscard]] size_t getLeavesNumber() const;

    [[nodiscard]] size_t getDepth() const;

    std::unordered_set<std::shared_ptr<Object>> getAllObjects() const;

//    ~Octree()
};


#endif //PHYSICS_OCTREE_H
