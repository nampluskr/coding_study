#include "computer.h"
#include "abstract_factory.h"


int main()
{
    if (1) {    // without factory method
        Computer* desktop = new DesktopComputer();
        desktop->operate();

        Computer* laptop = new LaptopComputer();
        laptop->operate();

        delete laptop;
        delete desktop;
    }
    if (1) {    // abstract factory
        ComputerFactory* desktopFactory = new DesktopFactory();
        Computer* desktop = desktopFactory->createComputer();
        desktop->operate();

        ComputerFactory* laptopFactory = new LaptopFactory();
        Computer* laptop = laptopFactory->createComputer();
        laptop->operate();

        delete desktop;
        delete laptop;
    }
    return 0;
}