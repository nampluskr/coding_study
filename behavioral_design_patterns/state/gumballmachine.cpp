#include <iostream>
using namespace std;

class GumballMachine;

// [interface]
class State {
public:
    virtual void insertQuarter() = 0;
    virtual void ejectQuarter() = 0;
    virtual void turnCrank() = 0;
    virtual void dispense() = 0;
};

class SoldState: public State {
private:
    GumballMachine* machine;
public:
    SoldState(GumballMachine* machine) {
        this->machine = machine;
    }
    void insertQuarter() override {}
    void ejectQuarter() override {}
    void turnCrank() override {}
    void dispense() override {}
};

class SoldOutState : public State {
private:
    GumballMachine* machine;
public:
    SoldOutState(GumballMachine* machine) {
        this->machine = machine;
    }
    void insertQuarter() override {}
    void ejectQuarter() override {}
    void turnCrank() override {}
    void dispense() override {}
};

class NoQuarterState : public State {
private:
    GumballMachine* machine;
public:
    NoQuarterState(GumballMachine* machine) {
        this->machine = machine;
    }
    void insertQuarter() override {}
    void ejectQuarter() override {}
    void turnCrank() override {}
    void dispense() override {}
};

class HasQuarterState : public State {
private:
    GumballMachine* machine;
public:
    HasQuarterState(GumballMachine* machine) {
        this->machine = machine;
    }
    void insertQuarter() override {}
    void ejectQuarter() override {}
    void turnCrank() override {}
    void dispense() override {}
};


// [context]
class GumballMachine {
private:
    State* soldOutState;
    State* noQuarterState;
    State* hasQuarterState;
    State* soldState;

    State* state = soldOutState;
    int count = 0;
public:

};


int main()
{

    return 0;
}