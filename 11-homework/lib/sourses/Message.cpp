#include "../headers/Message.h"

#include <utility>

Message::Message(Code code, std::string text) : code(code), codeStr(text) {}

Message::Code Message::GetCode() const
{
    return code;
}

const std::string& Message::GetCodeStr() const
{
    return codeStr;
}
