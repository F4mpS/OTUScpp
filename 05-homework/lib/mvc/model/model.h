#pragma once

#include <memory>
#include <string>

#include "../view/view.h"
#include "../Document.h"

/**
 * @brief Class that implements logic of program.
 * @brief Final point in MVC pattern that makes changes to document and shows it to user.
 */
class model
{
public:
    /** @brief Method that closes *window*
     *  @param window reference to GUI
    */
    void CloseWindow(std::shared_ptr<view> window);

    /** @brief Method that removes all shapes from *document*
     *  @param document refence to document
    */
    void ClearDocument(std::shared_ptr<Document> document);

    /** @brief Method that closes *document*
     *  @param document refence to document
    */
    void CloseDocument(std::shared_ptr<Document> document);

    /** @brief Method that saves *document* as *documentName*
     *  @param documentName name of document
     *  @param document refence to document
    */
    void SaveDocument(std::string& documentName, std::shared_ptr<Document> document);

    /** @brief Method that opens *document*
     *  @param document refence to document
    */
    void ExportDocument(std::shared_ptr<Document> document);

    /** @brief Method that creates new document in *document* with name *documentName*
     *  @param documentName name of new document
     *  @param document refence to place where to create new document
    */
    void CreateDocument(std::string& documentName, std::shared_ptr<Document> document);

    /** @brief Method that sets *currentShape* in *document* as *shape*
     *  @param shape refence to one of shapes
     *  @param document refence to document
    */
    void SelectShape(std::shared_ptr<Shape> shape, std::shared_ptr<Document> document);

    /** @brief Method that draws *currentShape* in *document*
     *  @param document refence to document
    */
    void DrawShape(std::shared_ptr<Document> document);

    /** @brief Method that deletes *shape* from *document*
     *  @param shape refence to shape
     *  @param document refence to document
    */
    void DeleteShape(std::shared_ptr<Shape> shape, std::shared_ptr<Document> document);
private:
    /** 
     * @param documentList list of reference to all documents
    */
    std::list<std::shared_ptr<Document>> documentList;
};

