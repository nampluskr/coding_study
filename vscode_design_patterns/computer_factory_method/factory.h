#pragma once

#include <string>
#include "computer.h"
using namespace std;

class ComputerFactory {
public:
    Computer* createComputer(const string& type) {
        if (type == "desktop")
            return new DesktopComputer();
        else if (type == "laptop")
            return new LaptopComputer();
        else
            return nullptr;
    }
};
