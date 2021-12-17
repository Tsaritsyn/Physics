//
// Created by Mikhail Tsaritsyn on 10.12.2021.
//

#include "scenes/Scene.h"

Scene::Scene() {
    m_cameras.emplace_back(new PinholeOrthoCamera(
            {-20., 0., 10.},
            {1., 0., -0.4},
            {0., -1., 0.},
            30.,
            {1920, 1080})
            );
    m_objects.emplace(new Sphere({2., 1., -1.}, 1.1));
    m_objects.emplace(new Sphere({5., 2., 1.}, 1.5, sf::Color::Cyan));
    m_objects.emplace(new Sphere({10., -0.5, -3.}, 0.5, sf::Color::Yellow));
    m_objects.emplace(new Sphere({1., -3., -1.}, 1., sf::Color::Green));
    m_objects.emplace(new Sphere({3., -2., 2.}, 2., sf::Color::Blue));
    m_objects.emplace(new Sphere({7., 3., -1.5}, 0.75, {200, 200, 200}));

//    determine the bounding box for all the objects on the scene
    for (const auto& object: m_objects)
        m_bbox.uniteWith(object->getBbox());

////    build the octree for the scene
    m_octree = std::make_shared<Octree>(m_bbox);
    m_octree->fill_with(m_objects);
    for (const auto& object: m_octree->getAllObjects())
        std::cout << object->str() << '\n';
    printf("Built an octree of depth %lu with %lu leaves\n", m_octree->getDepth(), m_octree->getLeavesNumber());
}

void Scene::updateCameraView(size_t ind) {
    for (unsigned x = 0; x < m_cameras[ind]->getWidth(); x++)
        for (unsigned y = 0; y < m_cameras[ind]->getHeight(); y++) {
            auto ray = m_cameras[ind]->sampleRay(x, y);

            const auto intersecting_objects = getIntersectingObjects(ray);
            if (intersecting_objects.empty()) continue;

            while (true) {
                const auto [dist_to_closest_object, closest_object] =
                        getDistanceToClosestObject(ray.getOrigin(), intersecting_objects);

                if (dist_to_closest_object < epsilon) {
                    const auto[point, _] = closest_object->getClosestPoint(ray.getOrigin());
                    ray.setColor(point.color);
                    break;
                }
                if (dist_to_closest_object == float_inf) break;
                ray.propagate(dist_to_closest_object);
            }

            m_cameras[ind]->updatePixel(x, y, ray.getColor());
        }
}

std::pair<float, std::shared_ptr<Object>>
Scene::getDistanceToClosestObject(const sf::Vector3f &point, const std::unordered_set<std::shared_ptr<Object>> &objects_to_check) {
    float dist_to_closest_object = float_inf;
    std::shared_ptr<Object> closest_object = nullptr;

    for (const auto& object: objects_to_check) {
        auto dist = object->getDistance(point);
        if (dist < dist_to_closest_object) {
            dist_to_closest_object = dist;
            closest_object = object;
        }
    }
    return {dist_to_closest_object, closest_object};
}

std::unordered_set<std::shared_ptr<Object>>
Scene::getIntersectingObjects(const Ray &ray) {
//    we query the scene's octree
    return m_octree->getIntersectingObjects(ray);
}

