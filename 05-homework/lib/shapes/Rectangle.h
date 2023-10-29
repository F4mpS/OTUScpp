#pragma once

#include "Shape.h"

/**
 * @brief Rectangle implementation.
 * 
 */
class Rectangle : public Shape, public std::enable_shared_from_this<Rectangle>
{
public:
    Rectangle() = default;
    /**
     * @brief Construct a new Line object
     * 
     * @param x1 left top vertex x cord
     * @param y1 left top vertex y cord
     * @param x2 right bottom vertex x cord
     * @param y2 right bottom vertex y cord
     */
    Rectangle (double x1, double y1, double x2, double y2) : LeftTopVertex(x1, y1), RightBottomVertex(x2, y2) {}

    /**
     * @brief Draws rectagle with vertexes in *LeftTopVertex* and *RightBottomVertex*
     * 
     */
    void Draw () override
    {
        std::cout << "Rectangle drawn" << std::endl;
    }

    /**
     * @brief Erase rectangle
     * 
     */
    void Erase() override
    {
        std::cout << "Rectangle erased" << std::endl;
    }

    /**
     * @brief Set left top vertex
     * 
     * @param x new x cord
     * @param y new y cord
     */
    void SetLeftTopVertex(double x, double y);
    
    /**
     * @brief Set right bottom vertex
     * 
     * @param x new x cord
     * @param y new y cord
     */
    void SetRightBottomVertex(double x, double y);
private:
    /**
     * @brief Left top vertex point
     * 
     */
    Point LeftTopVertex;
    
    /**
     * @brief Right bottom vertex point
     * 
     */
    Point RightBottomVertex;
};
