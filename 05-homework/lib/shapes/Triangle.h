#pragma once

#include "Shape.h"

class Triangle : public Shape, public std::enable_shared_from_this<Triangle>
{
public:
    Triangle() = default;
    /**
     * @brief Construct a new Triangle object
     * 
     * @param x1 first vertex x cord
     * @param y1 first vertex y cord
     * @param x2 second vertex x cord
     * @param y2 second vertex y cord
     * @param x3 third vertex x cord
     * @param y3 third vertex y cord
     */
    Triangle (double x1, double y1, double x2, double y2, double x3, double y3) : firstVertex(x1, y1), secondVertex(x2, y2), thirdVertex(x3, y3) {}

    ~Triangle() = default;

    void Draw() override
    {
        std::cout << "Triangle drawn" << std::endl;
    }

    /**
     * @brief Erase triangle
     * 
     */
    void Erase() override
    {
        std::cout << "Triangle erased" << std::endl;
    }

    /**
     * @brief Set *firstVertex*
     * 
     * @param x new x cord
     * @param y new y cord
     */
    void SetFirstVertex(double x, double y);

    /**
     * @brief Set *secondVertex*
     * 
     * @param x new x cord
     * @param y new y cord
     */
    void SetSecondVertex(double x, double y);
    
    /**
     * @brief Set *thirdVertex*
     * 
     * @param x new x cord
     * @param y new y cord
     */
    void SetThirdVertex(double x, double y);
private:
    /**
     * @brief First vertex point
     * 
     */
    Point firstVertex;
    
    /**
     * @brief Second vertex point
     * 
     */
    Point secondVertex;
    
    /**
     * @brief Third vertex point
     * 
     */
    Point thirdVertex;
};