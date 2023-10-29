#pragma once 

#include <memory>
#include <list>

// #include "Buttons.h"
#include "controller.h"

/**
 * @brief GUI representation. Window with canvas in the middle and buttons around it for interacting with canvas.
 */
class view
{
public:
    view ();
    ~view ();

    /** @brief Method that calls *CallClearDocument* in controller */
    void ClearDocumentBtn();
 
    /** @brief Method that calls *CallCloseDocument* in controller */
    void CloseDocumentBtn();
     
    /** @brief Method that calls *CallSaveDocument* in controller */
    void ImportDocumentBtn(std::string);
     
    /** @brief Method that calls *CallExportDocument* in controller */
    void ExportDocumentBtn(std::string);
    
    /** @brief Method that calls *CallCreateDocument* in controller */
    void CreateDocumentBtn();

    /** @brief Method that calls *CallSelectShape* and sets *Rectangle* shape for drawing */
    void RectangleBtn();

    /** @brief Method that calls *CallSelectShape* and sets *Line* shape for drawing */
    void LineBtn();
    
    /** @brief Method that calls *CallSelectShape* and sets *Circle* shape for drawing */
    void CircleBtn();
    
    /** @brief Method that calls *CallSelectShape* and sets *Triangle* shape for drawing */
    void TriangleBtn();

    /** @brief Method that calls *CallDrawShape* in controller */
    void DrawShapeBtn();
private:
    controller* Controller;
};
