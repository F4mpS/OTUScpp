#pragma once

/**
 * @brief Point struct that represents 2-d point with coordinates x and y
 */
struct Point
{
    Point(double x = 0, double y = 0) : x(x), y(y) {}
    ~Point() = default;

    double x;
    double y;
};