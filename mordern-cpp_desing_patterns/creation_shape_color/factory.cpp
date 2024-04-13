#include <iostream>
#include <string>
using namespace std;

// [shape.h]
class Shape {
public:
    virtual void draw() const = 0;
};

class Circle : public Shape {
public:
    void draw() const override { cout << "[Circle] draw a circle.\n"; }
};

class Square: public Shape {
public:
    void draw() const override { cout << "[Square] draw a square.\n"; }
};

// [color.h]
class Color {
public:
    virtual void fill() = 0;
};

class Red : public Color {
public:
    void fill() override { cout << "[Red] fill in red.\n"; }
};

class Green: public Color {
public:
    void fill() override { cout << "[Green] fill in green.\n"; }
};

// [factory.h]
class ShapeFactory {
public:
    virtual Shape* createShape(const string& type) = 0;
    virtual Color* createColor(const string& type) = 0;
};



int main()
{
    return 0;
}