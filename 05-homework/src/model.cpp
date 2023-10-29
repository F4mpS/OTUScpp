#include "../lib/api/model.h"

/** @brief Method that removes all shapes from *document*
 *  @param document refence to document
 */
void model::ClearDocument()
{
    currentDocument.get()->EraseShape();
    std::cout << "Document cleared" << std::endl;
}

/** @brief Method that closes *document*
 *  @param document refence to document
 */
void model::CloseDocument()
{
    currentDocument = nullptr;
    std::cout << "Document closed" << std::endl;
}

/** @brief Method that import document from file *docName*
 *  @param docName name of document
 */
void model::ImportDocument(std::string docName)
{
    currentDocument = docList.find(docName)->second;
    std::cout << "\"" << docName << "\" imported" << std::endl;
}

/** @brief Method that export document to file *docName*
 *  @param document refence to document
 */
void model::ExportDocument(std::string docName)
{    
    docList.emplace(docName, currentDocument);
    std::cout << "Document exported as \"" << docName << "\"" << std::endl;
}

/** @brief Method that creates new document in *document* with name *documentName*
 *  @param documentName name of new document
 *  @param document refence to place where to create new document
 */
void model::CreateDocument()
{
    currentDocument = std::make_shared<Document>();
    std::cout << "Document created" << std::endl;
}

// /** @brief Method that sets *currentShape* in *document* as *shape*
//  *  @param shape refence to one of shapes
//  *  @param document refence to document
//  */
// void model::SelectShape(Shape* shape)
// {
//     currentDocument.get()->SelectCurrentShape(std::make_shared<Shape>(shape));
// }

void model::SelectCircle()
{
    currentDocument.get()->SelectCurrentShape(std::make_shared<Circle>());
    std::cout << "Circle selected" << std::endl;
}
    
void model::SelectRectangle()
{
    currentDocument.get()->SelectCurrentShape(std::make_shared<Rectangle>());
    std::cout << "Rectangle selected" << std::endl;
}

void model::SelectLine()
{
    currentDocument.get()->SelectCurrentShape(std::make_shared<Line>());
    std::cout << "Line selected" << std::endl;
}

void model::SelectTriangle()
{
    currentDocument.get()->SelectCurrentShape(std::make_shared<Triangle>());
    std::cout << "Triangle selected" << std::endl;
}

/** @brief Method that draws in *document*
 *  @param document refence to document
 */
void model::DrawShape()
{
    currentDocument.get()->DrawShape();
}