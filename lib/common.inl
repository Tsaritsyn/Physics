//
// Created by Mikhail Tsaritsyn on 13.12.2021.
//

//#include "common.h"

#include "common.hpp"

template <typename T>
T lerp(const T& a, const T& b, float alpha) {return (1 - alpha) * a + alpha * b;}

template <typename T>
std::ostream& operator <<(std::ostream& os, const sf::Vector3<T>& v) {return os << '(' << v.x << ", " << v.y << ", " << v.z << ")";}

template <typename T>
std::ostream& operator <<(std::ostream& os, const sf::Vector2<T>& v) {return os << '(' << v.x << ", " << v.y << ")";}

template <typename T>
T operator *(const sf::Vector3<T>& v1, const sf::Vector3<T>& v2) {return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;}

template <typename T>
T operator *(const sf::Vector2<T>& v1, const sf::Vector2<T>& v2) {return v1.x * v2.x + v1.y * v2.y;}

template <typename T>
float norm2(const sf::Vector3<T>& v) {return v * v;}

template <typename T>
float norm2(const sf::Vector2<T>& v) {return v * v;}

template <typename T>
float norm(const sf::Vector3<T>& v) {return sqrt(norm2(v));}

template <typename T>
float norm(const sf::Vector2<T>& v) {return sqrt(norm2(v));}

template <typename T>
sf::Vector3<T> cross_product(const sf::Vector3<T>& v1, const sf::Vector3<T>& v2) {
    return {v1.y * v2.z - v1.z * v2.y, v1.z * v2.x - v1.x * v2.z, v1.x * v2.y - v1.y * v2.x};
}

template <typename T>
T cross_product(const sf::Vector2<T>& v1, const sf::Vector2<T>& v2) {return v1.x * v2.y - v1.y * v2.x;}

template<typename T>
T Matrix3<T>::det() const {
    return m_rows[0].x * m_rows[1].y * m_rows[2].z +
            m_rows[1].x * m_rows[2].y * m_rows[0].z +
            m_rows[0].y * m_rows[1].z * m_rows[2].x -
            m_rows[2].x * m_rows[1].y * m_rows[0].z -
            m_rows[0].x * m_rows[2].y * m_rows[1].z -
            m_rows[1].x * m_rows[0].y * m_rows[2].z;
}

template<typename T>
Matrix3<T>& Matrix3<T>::transpose() {
    std::swap(m_rows[0].y, m_rows[1].x);
    std::swap(m_rows[0].z, m_rows[2].x);
    std::swap(m_rows[2].y, m_rows[1].z);
    return *this;
}

template<typename T>
Matrix3<T> &Matrix3<T>::operator/=(const T &scalar) {
    for (unsigned i = 0; i < 3; i++)
        m_rows[i] /= scalar;
    return *this;
}

template<typename T>
Matrix3<T> Matrix3<T>::inverse() const {
    return Matrix3<T>(
      {m_rows[1].y * m_rows[2].z - m_rows[1].z * m_rows[2].y, m_rows[0].z * m_rows[2].y - m_rows[0].y * m_rows[2].z, m_rows[0].y * m_rows[1].z - m_rows[0].z * m_rows[1].y},
      {m_rows[1].z * m_rows[2].x - m_rows[1].x * m_rows[2].z, m_rows[0].x * m_rows[2].z - m_rows[0].z * m_rows[2].x, m_rows[1].x * m_rows[0].z - m_rows[0].x * m_rows[1].z},
      {m_rows[1].x * m_rows[2].y - m_rows[1].y * m_rows[2].x, m_rows[0].y * m_rows[2].x - m_rows[0].x * m_rows[2].y, m_rows[0].x * m_rows[1].y - m_rows[0].y * m_rows[1].x}
    ) /= det();
}

template<typename T>
sf::Vector3<T> Matrix3<T>::column(unsigned int i) const {
    return sf::Vector3<T>{m_rows[0][i], m_rows[1][i], m_rows[2][i]};
}

template<typename T>
sf::Vector3<T> Matrix3<T>::operator*(const sf::Vector3<T> &v) {
    return sf::Vector3<T>(m_rows[0] * v, m_rows[1] * v, m_rows[2] * v);
}

template<typename T>
std::ostream& operator <<(std::ostream& os, const Matrix3<T>& M) {
    return os << '(' << M.row(0) << "\n " << M.row(1) << "\n " << M.row(2) << ')';
}

