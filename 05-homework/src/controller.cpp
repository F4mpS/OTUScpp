#include "../lib/mvc/controller/controller.h"


void controller::CallCloseWindow(std::shared_ptr<view> window) 
{
    (void)window;
}

void controller::CallClearDocument(std::shared_ptr<Document> document) 
{
    (void)document;
}

void controller::CallCloseDocument(std::shared_ptr<Document> document) 
{
    (void)document;
}

void controller::CallSaveDocument(std::string &documentName, std::shared_ptr<Document> document) 
{
    (void)documentName;
    (void)document;
}

void controller::CallExportDocument(std::shared_ptr<Document> document) 
{
    (void)document;
}

void controller::CallCreateDocument(std::string &documentName, std::shared_ptr<Document> document) 
{
    (void)documentName;
    (void)document;
}

void controller::CallSelectShape(std::shared_ptr<Shape> shape, std::shared_ptr<Document> document) 
{
    (void)shape;
    (void)document;
}

void controller::CallDrawShape(std::shared_ptr<Document> document) 
{
    (void)document;
}

void controller::CallDeleteShape(std::shared_ptr<Shape> shape, std::shared_ptr<Document> document) 
{
    (void)shape;
    (void)document;
}