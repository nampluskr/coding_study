#include "shape.h"

// [factory.h]
class ShapeFactory {
public:
  static Shape* createShape(const string& type) {
    if (type == "circle")
        return new Circle();
    else if (type == "square")
        return new Square();
    else
      return nullptr;
  }
};

// client code
int main() {
  Shape* circle = ShapeFactory::createShape("circle");
  circle->draw();

  Shape* square = ShapeFactory::createShape("square");
  square->draw();

  delete circle;
  delete square;

  return 0;
}