#pragma once

#include "Shape.h"

/**
 * @brief Line implementation.
 * 
 */
class Line : public Shape, public std::enable_shared_from_this<Line>
{
public:
    Line() = default;
    /**
     * @brief Construct a new Line object
     * 
     * @param x1 start x cord
     * @param y1 start y cord
     * @param x2 end x cord
     * @param y2 end y cord
     */
    Line(double x1, double y1, double x2, double y2) : start(x1, y1), end(x2, y2) {}
    
    ~Line() = default;
    /**
     * @brief Draws line from *start* to *end*
     * 
     */
    void Draw() override
    {
        std::cout << "Line drawn" << std::endl;
    }

    /**
     * @brief Erase line
     * 
     */
    void Erase() override
    {
        std::cout << "Line erased" << std::endl;
    }

    /**
     * @brief Set *start* point
     * 
     * @param x new x cord
     * @param y new y cord
     */
    void SetStart(double x, double y);

    /**
     * @brief Set *end* point
     * 
     * @param x new x cord
     * @param y new y cord
     */
    void SetEnd(double x, double y);
private:
    /**
     * @brief Start point
     */
    Point start;
    
    /**
     * @brief End point
     */
    Point end;
};