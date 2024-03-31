//#include "template_class.h"
#include "template_struct.h"

int main()
{
    cout << ">> Concrete class 1:\n";
    auto* cc1 = new ConcreteClass1;
    cc1->templateMethod();

    cout << endl;
    cout << ">> Concrete class 2:\n";
    auto* cc2 = new ConcreteClass2;
    cc2->templateMethod();

    delete cc1;
    delete cc2;
    return 0;
}