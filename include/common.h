//
// Created by Mikhail Tsaritsyn on 10.12.2021.
//

#ifndef PHYSICS_COMMON_H
#define PHYSICS_COMMON_H

#include <iostream>
#include <iomanip>
#include <cmath>

#include <SFML/Graphics.hpp>

std::ostream& operator <<(std::ostream& os, const sf::Color& color);

template <typename T>
T lerp(const T& a, const T& b, float alpha) {
    return (1 - alpha) * a + alpha * b;
}

template <typename T>
std::ostream& operator <<(std::ostream& os, const sf::Vector3<T>& v) {
    return os << '(' << v.x << ", " << v.y << ", " << v.z << ")";
}

template <typename T>
std::ostream& operator <<(std::ostream& os, const sf::Vector2<T>& v) {
    return os << '(' << v.x << ", " << v.y << ")";
}

template <typename T>
T operator *(const sf::Vector3<T>& v1, const sf::Vector3<T>& v2) {
    return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}

template <typename T>
T operator *(const sf::Vector2<T>& v1, const sf::Vector2<T>& v2) {
    return v1.x * v2.x + v1.y * v2.y;
}

template <typename T>
float norm2(const sf::Vector3<T>& v) {
    return v * v;
}

template <typename T>
float norm2(const sf::Vector2<T>& v) {
    return v * v;
}

template <typename T>
float norm(const sf::Vector3<T>& v) {
    return sqrt(norm2(v));
}

template <typename T>
float norm(const sf::Vector2<T>& v) {
    return sqrt(norm2(v));
}

#endif //PHYSICS_COMMON_H
