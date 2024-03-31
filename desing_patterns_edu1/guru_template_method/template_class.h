#pragma once
#include <iostream>
using namespace std;

// <abstract>
class AbstractClass {
protected:
    virtual ~AbstractClass() {}

    void baseOperation1() const { cout << "Abstract Class:  base operation 1\n"; }
    void baseOperation2() const { cout << "Abstract Class:  base operation 2\n"; }
    void baseOperation3() const { cout << "Abstract Class:  base operation 3\n"; }

    virtual void requiredOperation1() const = 0;
    virtual void requiredOperation2() const = 0;
    virtual void hook1() const {}
    virtual void hook2() const {}

public:
    // define a skeleton of alrorithms
    void templateMethod() {
        baseOperation1();
        requiredOperation1();
        hook1();
        baseOperation2();
        requiredOperation1();
        hook2();
        baseOperation3();
    }
};

// <implementaion>
class ConcreteClass1 : public AbstractClass {
protected:
    void requiredOperation1() const override {
        cout << "Concrete Class1: implemented opreation 1\n";
    }
    void requiredOperation2() const override { 
        cout << "Concrete Class1: implemented opreation 2\n";
    }
};

// <implementation>
class ConcreteClass2 : public AbstractClass {
protected:
    void requiredOperation1() const override { 
        cout << "Concrete Class2: implemented opreation 1\n";
    }
    void requiredOperation2() const override {
        cout << "Concrete Class2: implemented opreation 2\n";
    }
    void hook1() const override { cout << "Concrete Class2: overriden hook 1\n"; }
    void hook2() const override { cout << "Concrete Class2: overriden hook 2\n"; }
};