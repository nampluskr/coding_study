#pragma once
#include <iostream>
#include <string>
#include "computer.h"
using namespace std;

// abstract factory
class ComputerFactory {
public:
    virtual Computer* createComputer() = 0;
};

// concrete factory
class DesktopFactory: public ComputerFactory {
    Computer* createComputer() override {
        return new DesktopComputer();
    }
};

// conctrete factory
class LaptopFactory: public ComputerFactory {
    Computer* createComputer() override {
        return new LaptopComputer();
    }
};

