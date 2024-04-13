#include "factory.h"

int main()
{
    ShapeFactory* circleFactory = new CircleFactory();
    Shape* circle = circleFactory->createShape("circle");
    Color* red = circleFactory->createColor("red");

    circle->draw();
    red->fill();

    delete red;
    delete circle;
    delete circleFactory;

    ShapeFactory* squareFactory = new SquareFactory();
    Shape* square = squareFactory->createShape("square");

    square->draw();

    delete square;
    delete squareFactory;

    return 0;
}