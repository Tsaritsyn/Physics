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
            {1080, 720})
            );
    m_objects.emplace_back(new Sphere({2., 0., 0.}, 1));
    m_objects.emplace_back(new Sphere({5., 2., 1.}, 1.5, sf::Color::Cyan));
    m_objects.emplace_back(new Sphere({10., -1., -2.}, 0.5, sf::Color::Yellow));
    m_objects.emplace_back(new Sphere({1., -3., -1.}, 1., sf::Color::Green));
    m_objects.emplace_back(new Sphere({3., -2., 2.}, 2., sf::Color::Blue));
    m_objects.emplace_back(new Sphere({7., 3., -1.5}, 0.75, {200, 200, 200}));
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
                ray.propagate(dist_to_closest_object);

                if (dist_to_closest_object < epsilon) {
                    const auto[point, _] = closest_object->getClosestPoint(ray.getOrigin());
                    ray.setColor(point.color);
                    break;
                }
            }

            m_cameras[ind]->updatePixel(x, y, ray.getColor());
        }
}

std::pair<float, std::shared_ptr<Object>>
Scene::getDistanceToClosestObject(const sf::Vector3f &point, const std::unordered_set<std::shared_ptr<Object>> &objects_to_check) {
    float dist_to_closest_object = std::numeric_limits<float>::infinity();
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
    std::unordered_set<std::shared_ptr<Object>> result;
    for (const auto& object: m_objects)
        if (object->intersects(ray)) result.insert(object);
    return result;
}

