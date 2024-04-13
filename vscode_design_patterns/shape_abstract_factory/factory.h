#pragma once
#include <iostream>
#include <string>
#include "shape.h"
#include "color.h"
using namespace std;

// [Abstract Factory]
class ShapeFactory {
public:
    virtual Shape* createShape(const string& type) = 0;
    virtual Color* createColor(const string& type) = 0;
};

// [Concrete Factory]
class CircleFactory : public ShapeFactory {
public:
    Shape* createShape(const string& type) override {
        if (type == "circle")
            return new Circle();
        else
            return nullptr;
    }
    Color* createColor(const string& type) override {
        if (type == "red")
            return new Red();
        else if (type == "green")
            return new Green();
        else
            return nullptr;
    }
};

// [Concrete Factory]
class SquareFactory : public ShapeFactory {
public:
    Shape* createShape(const string& type) override {
        if (type == "square")
            return new Square();
        else
            return nullptr;
    }
    Color* createColor(const string& type) {
        return nullptr;
    }
};