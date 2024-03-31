#if 0
#include <iostream>
#include <string>
using namespace std;

// product.h
// <abstract>
class Product {
public:
    virtual ~Product() {}
    virtual string operation() const = 0;
};

class ConcreteProduct1 : public Product {
public:
    string operation() const override {
        return "{Result of the ConcreteProduct1}";
    }
};

class ConcreteProduct2 : public Product {
public:
    string operation() const override {
        return "{Result of the ConcreteProduct2}";
    }
};

// creator.h
class Creator {
public:
    virtual ~Creator() {};
    virtual Product* factoryMethod() const = 0;

    string someOperation() const {
        Product* product = this->factoryMethod();
        string result = "Creator: The same creator's code has just worked with " + product->operation();
        delete product;
        return result;
    }
};

class ConcreteCreator1 : public Creator {
public:
    Product* factoryMethod() const override {
        return new ConcreteProduct1;
    }
};

class ConcreteCreator2 : public Creator {
public:
    Product* factoryMethod() const override {
        return new ConcreteProduct2;
    }
};

void clientcode(const Creator& creator) {
    cout << "Client: I'm not aware of the creator's class, but it still works.\n"
        << creator.someOperation() << endl;
}


int main() {
    cout << "App: Launched with the ConcreteCreator1.\n";
    Creator* creator1 = new ConcreteCreator1;
    clientcode(*creator1);

    cout << endl;
    cout << "App: Launched with the ConcreteCreator2.\n";
    Creator* creator2 = new ConcreteCreator2;
    clientcode(*creator2);

    delete creator1;
    delete creator2;
    return 0;
}
#endif