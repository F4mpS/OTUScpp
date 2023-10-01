#include "../lib/mvc/model/model.h"


void model::CloseWindow(std::shared_ptr<view> window) {}

void model::ClearDocument(std::shared_ptr<Document> document) {}

void model::CloseDocument(std::shared_ptr<Document> document) {}

void model::SaveDocument(std::string &documentName, std::shared_ptr<Document> document) {}

void model::ExportDocument(std::shared_ptr<Document> document) {}

void model::CreateDocument(std::string &documentName, std::shared_ptr<Document> document) {}

void model::SelectShape(std::shared_ptr<Shape> shape, std::shared_ptr<Document> document) {}

void model::DrawShape(std::shared_ptr<Document> document) {}

void model::DeleteShape(std::shared_ptr<Shape> shape, std::shared_ptr<Document> document) {}