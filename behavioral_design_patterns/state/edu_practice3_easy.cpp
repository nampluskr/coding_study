#if 0
#include <iostream>
using namespace std;

#define ON      0
#define OFF     1
#define SLEEP   2

class State {
public:
    virtual void pressButton() = 0;
};

class Machine {
private:
    State* state;
public:
    Machine(State* state) {
        this->setState(state);
    }
    void setState(State* state) {
        this->state = state;
    }
};


class OnState : public State {
public:
    void pressButton() override {}
};

class OffState : public State {
public:
    void pressButton() override {}
};

class SleepState : public State {
public:
    void pressButton() override {}
};



int main()
{
    return 0;
}
#endif