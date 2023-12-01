#pragma once

#include <string>

class Message
{
public:
    enum class Code
    {
        OK,
        ERROR,
    };

    Message(Code, std::string);
    Message() = delete;

    Code GetCode() const;
    const std::string& GetCodeStr() const;

private:
    Code code;
    std::string codeStr;
};
