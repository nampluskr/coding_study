#pragma once

#include "product.h"

#if 1

class Builder {
private:
    Product* product_;
public:
    Builder() { product_ = new Product("", "", ""); }
    static Builder* start() { return new Builder; }
    Builder* setCPU(const string& cpu) { product_->setCPU(cpu); return this; }
    Builder* setRAM(const string& ram) { product_->setRAM(ram); return this; }
    Builder* setSSD(const string& ssd) { product_->setSSD(ssd); return this; }
    Product* build() { return product_; }
};
#else

class Builder {
private:
    Product product_;
public:
    Builder() { product_ = Product({ "", "", "" }); }
    static Builder& start() { return Builder({}); }
    Builder& setCPU(const string& cpu) { product_.setCPU(cpu); return *this; }
    Builder& setRAM(const string& ram) { product_.setRAM(ram); return *this; }
    Builder& setSSD(const string& ssd) { product_.setSSD(ssd); return *this; }
    Product& build() { return *product_; }
};

#endif