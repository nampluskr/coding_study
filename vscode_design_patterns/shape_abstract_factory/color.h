#pragma once
#include <iostream>
using namespace std;

class Color {
public:
  virtual void fill() = 0;
};

class Red : public Color {
public:
  void fill() override { cout << "Fill in red.\n"; }
};

class Green : public Color {
public:
  void fill() override { cout << "Fill in greem.\n"; }
};