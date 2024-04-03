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
    Product() {}
    Product(const string& cpu, const string& ram, const string& ssd) :
        cpu_(cpu), ram_(ram), ssd_(ssd) {}
    //{
    //    cpu_ = cpu; ram_ = ram; ssd_ = ssd;
    //}
    void setCPU(const string& cpu) { cpu_ = cpu; }
    void setRAM(const string& ram) { ram_ = ram; }
    void setSSD(const string& ssd) { ssd_ = ssd; }

    void info() {
        cout << "[Computer] ";
        cout << "CPU " + cpu_ + " / RAM " + ram_ + " / SSD " + ssd_ << endl;
    }
};