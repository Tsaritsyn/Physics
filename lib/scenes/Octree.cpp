//
// Created by Mikhail Tsaritsyn on 12.12.2021.
//

#include "scenes/Octree.h"

std::unordered_set<std::shared_ptr<Object>> Octree::getIntersectingObjects(const Ray &ray) const {
    if (!m_bbox.intersectsWith(ray)) return {};
    std::unordered_set<std::shared_ptr<Object>> result;

    for (const auto& child: m_children) {
        if (child->m_bbox.intersectsWith(ray)) {
            const auto &child_intersections = child->getIntersectingObjects(ray);
            std::set_union(result.begin(), result.end(),
                           child_intersections.begin(), child_intersections.end(),
                           std::inserter(result, result.begin())
                           );
        }
    }
    for (const auto& object: m_objects)
        if (object->intersectsWith(ray)) result.insert(object);
    return result;
}

size_t Octree::getLeavesNumber() const {
    if (m_children.empty()) return 1;
    size_t result = 0;
    for (const auto& child: m_children)
        result += child->getLeavesNumber();
    return result;
}

size_t Octree::getDepth() const {
    size_t result = 0;
    for (const auto& child: m_children)
        result = std::max(result, child->getDepth());
    return result + 1;
}

void Octree::fill_with(const std::unordered_set<std::shared_ptr<Object>> &objects, float min_size) {
    for (const auto& object: objects)
        if (object->intersectsWith(m_bbox)) m_objects.insert(object);

    if (m_objects.size() <= 1) return;

    const auto sub_boxes = m_bbox.subdivide();
    if (sub_boxes[0].getMinDimension() < min_size) return;

    for (const auto& sub_box: sub_boxes) {
        auto child = std::make_shared<Octree>(sub_box);
        child->fill_with(m_objects, min_size);
        m_children.push_back(child);
    }
    m_objects.clear();
}

std::unordered_set<std::shared_ptr<Object>> Octree::getAllObjects() const {
    std::unordered_set<std::shared_ptr<Object>> result;

    std::set_union(result.begin(), result.end(),
                   m_objects.begin(), m_objects.end(),
                   std::inserter(result, result.begin()));
    for (const auto& child: m_children) {
        const auto &child_objects = child->getAllObjects();
        std::set_union(result.begin(), result.end(),
                       child_objects.begin(), child_objects.end(),
                       std::inserter(result, result.begin()));
    }
    return result;
}
