#pragma once

#include <string>

#include "model.h"

/**
 * @brief Class that takes button calls from GUI and passes them to the model.
 * @brief Gasket in MVC pattern that separates program logic from UI.
 */
class controller
{
public:
    controller() = default;
    ~controller() = default;

    /** @brief Fires after *ClearDocumentBtn* is called from GUI and calls *ClearDocument* in model 
     *  @param document refence to document
    */
    void CallClearDocument();

    /** @brief Fires after *CloseDocumentBtn* is called from GUI and calls *CloseDocument* in model 
     *  @param document refence to document
    */
    void CallCloseDocument();
    
    /** @brief Fires after *SaveDocumentBtn* is called from GUI and calls *SaveDocument* in model 
     *  @param documentName name of document
     *  @param document refence to document
    */
    void CallImportDocument(std::string);
    
    /** @brief Fires after *ExportDocumentBtn* is called from GUI and calls *ExportDocument* in model 
     *  @param document refence to document
    */
    void CallExportDocument(std::string);
    
    /** @brief Fires after *CreateDocumentBtn* is called from GUI and calls *CreateDocument* in model 
     *  @param documentName name of document
     *  @param document refence to document
    */
    void CallCreateDocument();

    /** @brief Fires after *CircleBtn* is called from GUI and calls *SelectCircle* in model 
    */
    void CallSelectCircle();

    /** @brief Fires after *RectangleBtn* is called from GUI and calls *SelectRectangle* in model 
    */
    void CallSelectRectangle();

    /** @brief Fires after *LineBtn* is called from GUI and calls *SelectLine* in model 
    */
    void CallSelectLine();

    /** @brief Fires after *TriangleBtn* is called from GUI and calls *SelectTriangle* in model 
    */
    void CallSelectTriangle();
    
    /** @brief Fires after *DrawShapeBtn* is called from GUI and calls *DrawShape* in model 
     *  @param document refence to document
    */
    void CallDrawShape();
private:
    model Model; 
};
