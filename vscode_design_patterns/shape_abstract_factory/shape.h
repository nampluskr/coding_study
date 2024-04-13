#pragma once
#include <iostream>
using namespace std;

class Shape {
public:
  virtual void draw() = 0;
};

class Circle : public Shape {
public:
  void draw() override {
    cout << "Draw a circle." << endl;
  }
};

class Square : public Shape {
public:
  void draw() override {
    cout << "Draw a square." << endl;
  }
};