#pragma once
#include <iostream>
#include <string>
using namespace std;

// Abstract Product
class Computer {
private:
    string cpu;
    string ram;
    string storage;

protected:
    string getCPU() const { return cpu; }
    void setCPU(const string& cpu) { this->cpu = cpu; }

    string getRAM() const { return ram; }
    void setRAM(const string& ram) { this->ram = ram; }

    string getStorage() const { return storage; }
    void setStorage(const string& storage) { this->storage = storage; }

public:
    virtual ~Computer() = default;
    void operate() {
        turnOn();
        displaySpec();
        turnOff();
        cout << "\n";
    }
    void displaySpec() { 
        cout << ">> CPU: " << getCPU() 
             << " RAM: " << getRAM() 
             << " Storage: " << getStorage() << "\n";
    }
    virtual void turnOn() = 0;
    virtual void turnOff() = 0;
};

// Concrete Product
class DesktopComputer: public Computer{
public:
    DesktopComputer() {
        setCPU("Intel");
        setRAM("Samsung");
        setStorage("SSD");
    }
protected:
    void turnOn() override  { cout << "[Desktop] Turn on.\n"; }
    void turnOff() override { cout << "[Desktop] Turn off.\n"; }
};

class LaptopComputer: public Computer{
public:
    LaptopComputer() {
        setCPU("AMD");
        setRAM("Hynix");
        setStorage("HDD");
    }
protected:
    void turnOn() override  { cout << "[Laptop] Turn on.\n"; }
    void turnOff() override { cout << "[Laptop] Turn off.\n"; }
};