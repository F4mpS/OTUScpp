#pragma once

/**
 * @brief Point struct that represents 2-d point with coordinates x and y
 */
struct Point
{
    Point(double x, double y) : x(x), y(y) {}

    double x;
    double y;
};