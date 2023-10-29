#include "../lib/api/controller.h"

void controller::CallClearDocument() 
{
    Model.ClearDocument();
}

void controller::CallCloseDocument() 
{
    Model.CloseDocument();
}

void controller::CallImportDocument(std::string docName) 
{
    Model.ImportDocument(docName);
}

void controller::CallExportDocument(std::string docName) 
{
    Model.ExportDocument(docName);
}

void controller::CallCreateDocument() 
{
    Model.CreateDocument();
}

void controller::CallSelectCircle() 
{
    Model.SelectCircle();
}

void controller::CallSelectLine() 
{
    Model.SelectLine();
}

void controller::CallSelectRectangle() 
{
    Model.SelectRectangle();
}

void controller::CallSelectTriangle() 
{
    Model.SelectTriangle();
}

void controller::CallDrawShape() 
{
    Model.DrawShape();
}