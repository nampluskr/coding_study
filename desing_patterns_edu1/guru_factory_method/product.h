#pragma once
#include <string>
using namespace std;

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