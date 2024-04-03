#pragma once

#include <iostream>
#include <string>
using namespace std;

class Product {
private:
    string cpu_;
    string ram_;
    string ssd_;
public:
    Product(string cpu, string ram, string ssd) {
        this->cpu_ = cpu;
        this->ram_ = ram;
        this->ssd_ = ssd;
    }
    //void setCPU(string cpu) { this->cpu_ = cpu; }
    //void setRAM(string ram) { this->ram_ = ram; }
    //void setSSD(string ssd) { this->ssd_ = ssd; }

    void info() {
        cout << "[Computer] ";
        cout << "CPU " + cpu_ + " / RAM " + ram_ + " / SSD " + ssd_ << endl;
    }
};