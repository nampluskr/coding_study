#include "computer.h"
#include "factory.h"


int main()
{
    if (0) {    // without factory method
        Computer* desktop = new DesktopComputer();
        desktop->operate();

        Computer* laptop = new LaptopComputer();
        laptop->operate();

        delete laptop;
        delete desktop;
    }

    if (1) {    // factory method
        ComputerFactory* factory = new ComputerFactory();
        Computer* desktop = factory->createComputer("desktop");
        desktop->operate();

        Computer* laptop = factory->createComputer("laptop");
        laptop->operate();

        delete desktop;
        delete laptop;
        delete factory;
    }
    return 0;
}