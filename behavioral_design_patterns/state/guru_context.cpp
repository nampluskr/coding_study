#if 0
// https://refactoring.guru/ko/design-patterns/state/cpp/example#lang-features
#include <iostream>
#include <typeinfo>
#include <string>
using namespace std;

class Machine;

// interface
class State {
protected:
    Machine* machine;

public:
    virtual ~State() {};

    void setMachine(Machine* machine) {
        this->machine = machine;
    }
    virtual void Handle1() = 0;
    virtual void Handle2() = 0;
};

// context
class Machine {
private:
    State* state;

public:
    Machine(State* state) {
        this->state = nullptr;
        this->setState(state);
    }
    ~Machine() {
        delete state;
    }
    void setState(State* state) {
        cout << "Machine: Transition to " << typeid(*state).name() << ".\n";
        if (this->state != nullptr)
            delete this->state;
        this->state = state;
        this->state->setMachine(this);
    }
    void Request1() {
        this->state->Handle1();
    }
    void Request2() {
        this->state->Handle2();
    }
};


class StateA : public State {
public:
    void Handle1() override;
    void Handle2() override {
        cout << "StateA handles request2.\n";
    }
};


class StateB : public State {
public:
    void Handle1() override {
        cout << "StateB handles request1.\n";
    }
    void Handle2() override {
        cout << "StateB handles request2.\n";
        cout << "StateB wants to change the state of the machine.\n";
        this->machine->setState(new StateA());
    }
};

void StateA::Handle1() {
    cout << "StateA handles request1.\n";
    cout << "StateA wants to change the state of the machine.\n";
    this->machine->setState(new StateB());
}

// client code
int main()
{
    //auto* state = new StateA();
    //auto* machine = new Machine(state);

    //cout << endl;
    //machine->Request1();

    //cout << endl;
    //machine->Request2();

    //delete state;
    //delete machine;

    auto machine = Machine(new StateA());

    cout << endl;
    machine.Request1();

    cout << endl;
    machine.Request2();


    return 0;
}
#endif