#pragma once

#include "product.h"

// <abstract>
class Builder {
public:
    virtual ~Builder() = default;
    virtual void make() = 0;
    virtual void setCPU() = 0;
    virtual void setRAM() = 0;
    virtual void setSSD() = 0;
    virtual Product* getProduct() = 0;
};


class ConcreteBuilderModel1 : public Builder {
private:
    Product* product_;
public:
    ConcreteBuilderModel1() { product_ = new Product("", "", ""); }
    void make() override { setCPU(); setRAM(); setSSD(); }
    void setCPU() override { product_->setCPU("I7"); }
    void setRAM() override { product_->setRAM("32GB"); }
    void setSSD() override { product_->setSSD("512GB"); }
    Product* getProduct() override { return product_; }
};


class ConcreteBuilderModel2 : public Builder {
private:
    Product* product_;
public:
    ConcreteBuilderModel2() { product_ = new Product("", "", ""); }
    void make() override { setCPU(); setRAM(); setSSD(); }
    void setCPU() override { product_->setCPU("I3"); }
    void setRAM() override { product_->setRAM("16GB"); }
    void setSSD() override { product_->setSSD("256GB"); }
    Product* getProduct() override { return product_; }
};


class Director {
private:
    Builder* builder_;
public:
    void setBuilder(Builder* builder) { this->builder_ = builder; }
    void make() { builder_->make(); }
    Product* getProduct() { return builder_->getProduct(); }
};