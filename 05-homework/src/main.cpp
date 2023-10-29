#include <iostream>

#include "../lib/api/view.h"

int main()
{
    view ui;

    std::cout << "FIRST DOC" << std::endl;
    ui.CreateDocumentBtn();
    ui.CircleBtn();
    ui.DrawShapeBtn();
    ui.LineBtn();
    ui.DrawShapeBtn();
    ui.ExportDocumentBtn("My first document");
    std::cout << std::endl;

    std::cout << "SECOND DOC" << std::endl;
    ui.CreateDocumentBtn();
    ui.RectangleBtn();
    ui.DrawShapeBtn();
    ui.ExportDocumentBtn("My second document");
    std::cout << std::endl;

    std::cout << "FIRST DOC" << std::endl;
    ui.ImportDocumentBtn("My first document");
    ui.ClearDocumentBtn();
    ui.CloseDocumentBtn();
    std::cout << std::endl;

    std::cout << "SECOND DOC" << std::endl;
    ui.ImportDocumentBtn("My second document");
    ui.ClearDocumentBtn();
    ui.CloseDocumentBtn();
    std::cout << std::endl;
}