#include "../lib/api/view.h"

view::view()
{
    Controller = new controller;
}

view::~view()
{
    Controller = nullptr;
}

/** @brief Method that calls *CallClearDocument* in controller */
void view::ClearDocumentBtn()
{
    Controller->CallClearDocument();
}

/** @brief Method that calls *CallCloseDocument* in controller */
void view::CloseDocumentBtn()
{
    Controller->CallCloseDocument();
}

/** @brief Method that calls *CallSaveDocument* in controller */
void view::ImportDocumentBtn(std::string docName)
{
    Controller->CallImportDocument(docName);
}

/** @brief Method that calls *CallExportDocument* in controller */
void view::ExportDocumentBtn(std::string docName)
{
    Controller->CallExportDocument(docName);
}

/** @brief Method that calls *CallCreateDocument* in controller */
void view::CreateDocumentBtn()
{
    Controller->CallCreateDocument();
}

/** @brief Method that calls *CallSelectShape* and sets *Rectangle* shape for drawing */
void view::RectangleBtn()
{
    Controller->CallSelectRectangle();
}

/** @brief Method that calls *CallSelectShape* and sets *Line* shape for drawing */
void view::LineBtn()
{
    Controller->CallSelectLine();
}

/** @brief Method that calls *CallSelectShape* and sets *Circle* shape for drawing */
void view::CircleBtn()
{
    Controller->CallSelectCircle();
}

/** @brief Method that calls *CallSelectShape* and sets *Triangle* shape for drawing */
void view::TriangleBtn()
{
    Controller->CallSelectTriangle();
}

/** @brief Method that calls *CallDrawShape* in controller */
void view::DrawShapeBtn()
{
    Controller->CallDrawShape();
}