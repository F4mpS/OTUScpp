#pragma once

#include <string>
#include <iostream>
#include <memory>
#include <list>

#include "../shapes/Shape.h"

/**
 * @brief Canvas representation. User can draw different shapes on it.
 * 
 */
class Document : public std::enable_shared_from_this<Document>
{
public:
    Document() = default;
    ~Document() = default;
    
    /** @brief Method that pushes new *shape* to shapeList
     *  @param shape reference to shape
    */
    void PushShape(std::shared_ptr<Shape> shape)
    {
        shapeList.emplace_back(shape);
    }
    
    /** @brief Method that sets *currentShape* as *shape*
     *  @param shape reference to shape
    */
    void SelectCurrentShape(std::shared_ptr<Shape> shape)
    {
        currentShape = shape;
    }


    /** @brief Method that draws *shape*
    */
    void DrawShape()
    {
        currentShape.get()->Draw();
        PushShape(currentShape);
    }

    /** @brief Method that erase all shapes
    */
    void EraseShape()
    {
        std::cout << "--- Erase START ---" << std::endl; 
        for (auto &shape : shapeList)
        {
            shape.get()->Erase();
        }
        
        shapeList.clear();
        std::cout << "--- Erase END ---" << std::endl; 
    }

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
