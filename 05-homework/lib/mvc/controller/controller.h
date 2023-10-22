#pragma once

#include <memory>
#include <string>

#include "../../shapes/Shape.h"
#include "../view/view.h"
#include "../Document.h"

/**
 * @brief Class that takes button calls from GUI and passes them to the model.
 * @brief Gasket in MVC pattern that separates program logic from UI.
 */
class controller
{
private:
    /*
    * controller data
    */
public:
    /** @brief Fires after *CloseWindowBtn* is called from GUI and calls *CloseWindow* in model
     *  @param window reference to GUI
    */
    void CallCloseWindow(std::shared_ptr<view> window);

    /** @brief Fires after *ClearDocumentBtn* is called from GUI and calls *ClearDocument* in model 
     *  @param document refence to document
    */
    void CallClearDocument(std::shared_ptr<Document> document);

    /** @brief Fires after *CloseDocumentBtn* is called from GUI and calls *CloseDocument* in model 
     *  @param document refence to document
    */
    void CallCloseDocument(std::shared_ptr<Document> document);
    
    /** @brief Fires after *SaveDocumentBtn* is called from GUI and calls *SaveDocument* in model 
     *  @param documentName name of document
     *  @param document refence to document
    */
    void CallSaveDocument(std::string& documentName, std::shared_ptr<Document> document);
    
    /** @brief Fires after *ExportDocumentBtn* is called from GUI and calls *ExportDocument* in model 
     *  @param document refence to document
    */
    void CallExportDocument(std::shared_ptr<Document> document);
    
    /** @brief Fires after *CreateDocumentBtn* is called from GUI and calls *CreateDocument* in model 
     *  @param documentName name of document
     *  @param document refence to document
    */
    void CallCreateDocument(std::string& documentName, std::shared_ptr<Document> document);

    /** @brief Fires after *SelectShapeBtn* is called from GUI and calls *SelectShape* in model 
     *  @param shape refence to shape
     *  @param document refence to document
    */
    void CallSelectShape(std::shared_ptr<Shape> shape, std::shared_ptr<Document> document);
    
    /** @brief Fires after *DrawShapeBtn* is called from GUI and calls *DrawShape* in model 
     *  @param document refence to document
    */
    void CallDrawShape(std::shared_ptr<Document> document);
    
    /** @brief Fires after shape delete method (method in shape) is called from GUI and calls *DeleteShape* in model 
     *  @param shape refence to shape
     *  @param document refence to document
    */
    void CallDeleteShape(std::shared_ptr<Shape> shape, std::shared_ptr<Document> document);
};
