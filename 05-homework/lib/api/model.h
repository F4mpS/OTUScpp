#pragma once

#include <memory>
#include <string>
#include <unordered_map>
#include <iostream>

#include "Document.h"
#include "../shapes/Shape.h"
#include "../shapes/Circle.h"
#include "../shapes/Line.h"
#include "../shapes/Rectangle.h"
#include "../shapes/Triangle.h"

/**
 * @brief Class that implements logic of program.
 * @brief Final point in MVC pattern that makes changes to document and shows it to user.
 */
class model
{
public:
    /** @brief Method that removes all shapes from *document*
     *  @param document refence to document
    */
    void ClearDocument();

    /** @brief Method that closes *document*
     *  @param document refence to document
    */
    void CloseDocument();

    /** @brief Method that saves *document* as *documentName*
     *  @param documentName name of document
     *  @param document refence to document
    */
    void ImportDocument(std::string);

    /** @brief Method that opens *document*
     *  @param document refence to document
    */
    void ExportDocument(std::string);

    /** @brief Method that creates new document in *document* with name *documentName*
     *  @param documentName name of new document
     *  @param document refence to place where to create new document
    */
    void CreateDocument();

    /** @brief Method that sets *currentShape* in *document* as *circle*
    */
    void SelectCircle();

    /** @brief Method that sets *currentShape* in *document* as *rectangle*
    */
    void SelectRectangle();

    /** @brief Method that sets *currentShape* in *document* as *line*
    */
    void SelectLine();

    /** @brief Method that sets *currentShape* in *document* as *triangle*
    */
    void SelectTriangle();

    /** @brief Method that draws *currentShape* in *document*
     *  @param document refence to document
    */
    void DrawShape();
private:
    std::shared_ptr<Document> currentDocument;
    std::unordered_map<std::string, std::shared_ptr<Document>> docList;
};

