#pragma once

#include "product.h"

class Creator {
public:
    virtual ~Creator() {};
    virtual Product* factoryMethod() const = 0;

    string someOperation() const {
        Product* product = this->factoryMethod();
        string result = "Creator: The same creator's code has just worked with ";
        result += product->operation();
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