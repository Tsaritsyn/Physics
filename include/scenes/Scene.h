//
// Created by Mikhail Tsaritsyn on 10.12.2021.
//

#ifndef PHYSICS_SCENE_H
#define PHYSICS_SCENE_H

#include <vector>
#include <memory>
#include <unordered_set>

#include "PinholeOrthoCamera.h"
#include "Sphere.h"
#include "Octree.h"


class Scene {
    std::vector<std::unique_ptr<Camera>> m_cameras;
    std::unordered_set<std::shared_ptr<Object>> m_objects;
    std::shared_ptr<Octree> m_octree;
    BBox m_bbox;

    /**
     * @param objects_to_check set of scene objects among which to search for closest one
     * @return distance to the closest object and its index in object array
     */
    [[nodiscard]] static std::pair<float, std::shared_ptr<Object>>
    getDistanceToClosestObject(const sf::Vector3f& point, const std::unordered_set<std::shared_ptr<Object>> &objects_to_check) ;

    std::unordered_set<std::shared_ptr<Object>> getIntersectingObjects(const Ray& ray);

public:
    Scene();

    void updateCameraView(size_t ind = 0);

    [[nodiscard]] const PixelGrid& getCameraView(size_t ind = 0) const {return m_cameras[ind]->getView();};

};


#endif //PHYSICS_SCENE_H
