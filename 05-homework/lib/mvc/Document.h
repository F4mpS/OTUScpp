#pragma once

#include <string>
#include <memory>
#include <list>

#include "../shapes/Shape.h"
#include "../shapes/Circle.h"
#include "../shapes/Rectangle.h"
#include "../shapes/Triangle.h"
#include "../shapes/Line.h"

/**
 * @brief Canvas representation. User can draw different shapes on it.
 * 
 */
class Document
{
public:
    Document() {}
    ~Document() {}

    /** @brief Method that deletes *shape* from shapeList
     *  @param shape reference to shape
    */
    void DeleteShape(std::shared_ptr<Shape> shape);
    
    /** @brief Method that pushes new *shape* to shapeList
     *  @param shape reference to shape
    */
    void PushShape(std::shared_ptr<Shape> shape);
    
    /** @brief Method that sets *currentShape* as *shape*
     *  @param shape reference to shape
    */
    void SelectCurrentShape(std::shared_ptr<Shape> shape);


    /** @brief Method that draws *shape*
     *  @param shape reference to shape
     * 
     *  @brief It uses polymorphism to print different shape by calling single method
    */
    void DrawShape(const Line& shape);
    void DrawShape(const Triangle& shape);
    void DrawShape(const Circle& shape);
    void DrawShape(const Rectangle& shape);

private:
    /**
     * @brief shapeList contains references to all shapes in document
     */
    std::list<std::shared_ptr<Shape>> shapeList;
    
    /**
     * @brief currentShape contains shape to be drawn
     */
    std::shared_ptr<Shape> currentShape;

    /**
     * @brief documentName contains its name
     */
    std::string documentName;
};
