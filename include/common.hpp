//
// Created by Mikhail Tsaritsyn on 10.12.2021.
//

#ifndef PHYSICS_COMMON_HPP
#define PHYSICS_COMMON_HPP

#include <iostream>
#include <iomanip>
#include <cmath>

#include <SFML/Graphics.hpp>

#define epsilon 1e-4

std::ostream& operator <<(std::ostream& os, const sf::Color& color);

template <typename T>
T lerp(const T& a, const T& b, float alpha);

template <typename T>
std::ostream& operator <<(std::ostream& os, const sf::Vector3<T>& v);

template <typename T>
std::ostream& operator <<(std::ostream& os, const sf::Vector2<T>& v);

template <typename T>
T operator *(const sf::Vector3<T>& v1, const sf::Vector3<T>& v2);

template <typename T>
T operator *(const sf::Vector2<T>& v1, const sf::Vector2<T>& v2);

template <typename T>
float norm2(const sf::Vector3<T>& v);

template <typename T>
float norm2(const sf::Vector2<T>& v);

template <typename T>
float norm(const sf::Vector3<T>& v);

template <typename T>
float norm(const sf::Vector2<T>& v);

sf::Vector3f normalize(const sf::Vector3f& v);

sf::Vector2f normalize(const sf::Vector2f& v);

template <typename T>
sf::Vector3<T> cross_product(const sf::Vector3<T>& v1, const sf::Vector3<T>& v2);

template <typename T>
T cross_product(const sf::Vector2<T>& v1, const sf::Vector2<T>& v2);

template <typename T>
class Matrix3 {
    std::array<sf::Vector3<T>, 3> m_rows;

public:
    explicit Matrix3(const std::array<sf::Vector3<T>, 3>& rows): m_rows{rows} {};

    Matrix3(const sf::Vector3<T>& row0, const sf::Vector3<T>& row1, const sf::Vector3<T>& row2): m_rows{row0, row1, row2} {};

    Matrix3() = default;

    /**
     * @return the determinant of the matrix
     */
    T det() const;

    /**
     * @return transpose the matrix
     */
    Matrix3<T>& transpose();

    Matrix3<T> transposed() const {return Matrix3<T>(*this).transpose();};

    Matrix3<T>& operator /=(const T& scalar);

    Matrix3<T> operator /(const T& scalar) const {return Matrix3<T>{*this} /= scalar;}

    /**
     * @return the inverse matrix
     */
    Matrix3<T> inverse() const;

    sf::Vector3<T> column(unsigned i) const;

    const sf::Vector3<T>& row(unsigned i) const {return m_rows[i];};

    sf::Vector3<T> operator *(const sf::Vector3<T>& v);
};

template <typename T>
std::ostream& operator <<(std::ostream& os, const Matrix3<T>& M);

/// borders excluded
template <typename T>
inline bool in_interval(T value, T min_value, T max_value) {return (value > min_value) && (value < max_value);}

/// borders included
template <typename T>
inline bool in_range(T value, T min_value, T max_value) {return (value >= min_value) && (value <= max_value);}

/// clips the given value to the given range
template <typename T>
inline T clip(T value, T min_value, T max_value) {return std::max(std::min(value, max_value), min_value);}

#include "../lib/common.inl"

typedef Matrix3<float> Matrix3f;
typedef Matrix3<int> Matrix3i;



#endif //PHYSICS_COMMON_HPP
