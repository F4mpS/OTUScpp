#pragma once 

#include <iostream>

#include "../../interfaces/IPrinter.h"

class OstreamPrinter : public IPrinter
{
public:
    OstreamPrinter() = delete;
    OstreamPrinter(std::ostream&);
    ~OstreamPrinter() = default;

    void Print(const std::vector<std::string>&) const override;
private:
    std::ostream& output;
};
