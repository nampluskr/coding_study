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
    string cpu_, ram_, ssd_;
public:
    void make() override { setCPU(); setRAM(); setSSD(); }
    void setCPU() override { this->cpu_ = "I7"; }
    void setRAM() override { this->ram_ = "32GB"; }
    void setSSD() override { this->ssd_ = "512GB"; }
    Product* getProduct() override { return new Product(cpu_, ram_, ssd_); }
};


class ConcreteBuilderModel2 : public Builder {
private:
    string cpu_, ram_, ssd_;
public:
    void make() override { setCPU(); setRAM(); setSSD(); }
    void setCPU() override { this->cpu_ = "I3"; }
    void setRAM() override { this->ram_ = "16GB"; }
    void setSSD() override { this->ssd_ = "256GB"; }
    Product* getProduct() override { return new Product(cpu_, ram_, ssd_); }
};


class Director {
private:
    Builder* builder_;
public:
    void setBuilder(Builder* builder) { this->builder_ = builder; }
    void make() { builder_->make(); }
    Product* getProduct() { return builder_->getProduct(); }
};