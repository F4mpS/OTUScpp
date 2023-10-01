#pragma once

#include "Shape.h"

/**
 * @brief Circle implementation.
 * 
 */
class Circle : Shape
{
public:
    /**
     * @brief Construct a new Circle object
     * 
     * @param x x cord
     * @param y y cord
     * @param radius circle radius
     */
    Circle (double x, double y, size_t radius) : center(x, y), radius(radius) {}

    /**
     * @brief Draws circle in *center* with radius *radius*
     * 
     */
    void Draw() override {}

    /**
     * @brief Set radius
     * 
     * @param newRadius new radius
     */
    void SetRadius(size_t newRadius) {}

    /**
     * @brief Set coords
     * 
     * @param x x cord
     * @param y y cord
     */
    void SetCenter(double x, double y) {}
private:
    /**
     * @brief Circle radius
     * 
     */
    size_t radius;

    /**
     * @brief Circle cord
     * 
     */
    Point center;
};