#pragma once

#include "Shape.h"

/**
 * @brief Circle implementation.
 * 
 */
class Circle : public Shape, public std::enable_shared_from_this<Circle>
{
public:
    Circle() = default;
    /**
     * @brief Construct a new Circle object
     * 
     * @param x x cord
     * @param y y cord
     * @param radius circle radius
     */
    Circle(double x, double y, size_t radius) : center(x, y), radius(radius) {}

    ~Circle() = default;
    /**
     * @brief Draws circle in *center* with radius *radius*
     * 
     */
    void Draw() override
    {
        std::cout << "Circle drawn" << std::endl;
    }

    /**
     * @brief Erase circle
     * 
     */
    void Erase() override
    {
        std::cout << "Circle erased" << std::endl;
    }


    /**
     * @brief Set radius
     * 
     * @param newRadius new radius
     */
    void SetRadius(size_t newRadius);

    /**
     * @brief Set coords
     * 
     * @param x x cord
     * @param y y cord
     */
    void SetCenter(double x, double y);
private:
    /**
     * @brief Circle cord
     * 
     */
    Point center;

    /**
     * @brief Circle radius
     * 
     */
    size_t radius;    
};
