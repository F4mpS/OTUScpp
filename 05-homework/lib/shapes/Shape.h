#pragma once

#include "Color.h"
#include "Point.h"

#include <memory>

class Shape : public std::enable_shared_from_this<Shape>
{
public:
    /**
     * @brief Construct new Shape
     * 
     */
    Shape() : lineColor(Color(0, 0, 0, 0)), lineSize(1) {}

    /**
     * @brief Construct new Shape
     * 
     * @param color *lineColor*
     */
    Shape(Color color) : lineColor(color), lineSize(1) {}

    /**
     * @brief Construct new Shape
     * 
     * @param size *lineSize*
     */
    Shape(size_t size) : lineColor(Color(0, 0, 0, 0)), lineSize(size) {}
    
    /**
     * @brief Construct new Shape
     * 
     * @param color *lineColor*
     * @param size *lineSize*
     */
    Shape(Color color, size_t size) : lineColor(color), lineSize(size) {}

    /**
     * @brief Shape virtual destructor
     * 
     */
    virtual ~Shape() = default;

    // Shape(const Shape& shape) {}

    /**
     * @brief Set *lineColor*
     * 
     * @param newColor *lineColor*
     */
    void SetColor(Color newColor);
    
    /**
     * @brief Set *lineSize*
     * 
     * @param newSize *lineSize*
     */
    void SetLineSize(size_t newSize);

    /**
     * @brief Shape draw virtual method
     * 
     */
    virtual void Draw() {}

    /**
     * @brief Shape erase virtual method
     * 
     */
    virtual void Erase() {}
protected:
    /**
     * @brief Shape line color
     * 
     */
    Color lineColor;

    /**
     * @brief Shape line size
     * 
     */
    size_t lineSize;
};
