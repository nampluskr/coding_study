#include <iostream>
#include "creator.h"
using namespace std;

void client_code(const Creator& creator) {
    cout << "Client: I'm not aware of the creator's class, but it still works.\n"
        << creator.someOperation() << endl;
}

int main() {
    cout << "App: Launched with the ConcreteCreator1.\n";
    Creator* creator1 = new ConcreteCreator1;
    client_code(*creator1);

    cout << endl;
    cout << "App: Launched with the ConcreteCreator2.\n";
    Creator* creator2 = new ConcreteCreator2;
    client_code(*creator2);

    delete creator1;
    delete creator2;
    return 0;
}