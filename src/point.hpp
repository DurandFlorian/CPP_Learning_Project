#pragma once

#include <algorithm>
#include <array>
#include <cassert>
#include <math.h>
#include <numeric>
#include <string>

template <unsigned char dimension, typename T, std::enable_if_t<std::is_arithmetic_v<T>,bool > = true> class Point
{
public:
    float& x()
    {
        static_assert(dimension >= 1);
        return values[0];
    }
    float x() const
    {
        static_assert(dimension >= 1);
        return values[0];
    }

    float& y()
    {
        static_assert(dimension >= 2);
        return values[1];
    }
    float y() const
    {
        static_assert(dimension >= 2);
        return values[1];
    }

    float& z()
    {
        static_assert(dimension >= 3);
        return values[2];
    }
    float z() const
    {
        static_assert(dimension >= 3);
        return values[2];
    }

    Point() {};

    template <typename... Arg>
    Point(T v, Arg&&... init) : values { v,static_cast<T>(std::forward<Arg>(init))... }
    {
        static_assert(sizeof...(init) <= dimension);
    }

    Point& operator+=(const Point& other)
    {
        std::transform(values.begin(), values.end(), other.values.begin(), values.begin(),
                       [](const float& a, const float& b) { return a + b; });
        return *this;
    }

    Point& operator-=(const Point& other)
    {
        std::transform(values.begin(), values.end(), other.values.begin(), values.begin(),
                       [](const float& a, const float& b) { return a - b; });
        return *this;
    }

    Point& operator*=(const Point& other)
    {
        std::transform(values.begin(), values.end(), other.values.begin(), values.begin(),
                       [](const float& a, const float& b) { return a * b; });
        return *this;
    }

    Point& operator*=(const T scalar)
    {
        std::transform(values.begin(), values.end(), values.begin(),
                       [scalar](const T& v) { return v * scalar; });
        return *this;
    }

    Point operator+(const Point& other) const
    {
        Point result = *this;
        result += other;
        return result;
    }

    Point operator-(const Point& other) const
    {
        Point result = *this;
        result -= other;
        return result;
    }

    Point operator*(const T scalar) const
    {
        Point result = *this;
        result *= scalar;
        return result;
    }

    Point operator*(const Point& other) const
    {
        Point result = *this;
        result *= other;
        return result;
    }

    Point operator-() const
    {
        Point result = *this;
        std::transform(result.values.begin(), result.values.end(), result.values.begin(),
                       [](const T& v) { return -v; });
        return result;
    }

    float length() const
    {
        return std::sqrt(
            std::reduce(values.begin(), values.end(), 0., [](T f1, T f2) { return f1 + f2 * f2; }));
    }

    float distance_to(const Point& other) const { return (*this - other).length(); }

    Point& normalize(const float target_len = 1.0f)
    {
        const float current_len = length();
        if (current_len == 0)
        {
            throw std::logic_error("cannot normalize vector of length 0");
        }

        *this *= (target_len / current_len);
        return *this;
    }

    Point& cap_length(const float max_len)
    {
        // assert(max_len > 0);
        const float current_len = length();
        if (current_len > max_len)
        {
            *this *= (max_len / current_len);
        }

        return *this;
    }

    std::string print_coordinates() const
    {
        std::string coordinates = "coordinates{";
        return std::transform_reduce(
            values.begin(), values.end(), coordinates,
            [](std::string s1, std::string s2) { return s1 + ", " + s2; },
            [](T v) { return std::to_string(v); });
    }

    static void test_generic_points()
    {
        Point<dimension, T> p1 { 1, 2, 3 };
        Point<dimension, T> p2 { 3, 4, 5 };
        auto p3 = p1 + p2;
        p3 -= p1;
        p1 += p2;
        p1 *= 3;
    }

    std::array<T, dimension> values;
};
