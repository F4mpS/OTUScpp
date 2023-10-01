#pragma once 

#include <memory>
#include <list>

#include "Button.h"
#include "../Document.h"

/**
 * @brief GUI representation. Window with canvas in the middle and buttons around it for interacting with canvas.
 */
class view
{
private:
    /** @brief Holds current canvas */
    std::shared_ptr<Document> currentDocument;
public:
    view ();
    ~view ();

    /** @brief Method that starts GUI */
    void InitWindow();

    /** @brief Button that calls *CallCloseWindow* in controller */
    Button CloseWindowBtn;

    /** @brief Button that calls *CallClearDocument* in controller */
    Button ClearDocumentBtn;
 
    /** @brief Button that calls *CallCloseDocument* in controller */
    Button CloseDocumentBtn;
    
    /** @brief Button that calls *CallSaveDocument* in controller */
    Button SaveDocumentBtn;
    
    /** @brief Button that calls *CallExportDocument* in controller */
    Button ExportDocumentBtn;
    
    /** @brief Button that calls *CallCreateDocument* in controller */
    Button CreateDocumentBtn;

    /** @brief Button that calls *CallSelectShape* and sets *Rectangle* shape for drawing */
    Button RectangleBtn;

    /** @brief Button that calls *CallSelectShape* and sets *Square* shape for drawing */
    Button SquareBtn;

    /** @brief Button that calls *CallSelectShape* and sets *Line* shape for drawing */
    Button LineBtn;
    
    /** @brief Button that calls *CallSelectShape* and sets *Circle* shape for drawing */
    Button CircleBtn;
    
    /** @brief Button that calls *CallDrawShape* in controller */
    Button DrawShapeBtn;
};
