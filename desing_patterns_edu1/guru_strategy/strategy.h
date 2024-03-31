#pragma once
#include <iostream>
#include <string>
using namespace std;

// <interface>
class Strategy {
public:
    virtual ~Strategy() {}
    virtual void excute(const string& data) const = 0;
};


class ConcreteStrategyA : public Strategy {
public:
    void excute(const string& data) const override { 
        cout << ">> [Strategy B] execute using " << data << "\n";
    }
};


class ConcreteStrategyB : public Strategy {
public:
    void excute(const string& data) const override {
        cout << ">> [Strategy B] execute using " << data << "\n";
    }
};