#if 0
// Nesteruk - Design Patterns in Modern C++
// Chap 21. State - State-Driven State Transitions
#include <iostream>
using namespace std;


class LightSwitch;

// [Interface]
class State {
public:
    virtual void on(LightSwitch* ls) {
        cout << "Light is already on." << endl;
    }
    virtual void off(LightSwitch* Is) {
        cout << "Light is already off." << endl;
    }
};

// [context] State machine
class LightSwitch {
private:
    State* state;

public:
    LightSwitch(State* state) {
        this->setState(state);
    }
    void setState(State* state) {
        this->state = state;
    }
};


class OnState: public State {
public:
    OnState() { 
        cout << "Light turned on" << endl; 
    }
    void off(LightSwitch* ls) override;
};


class OffState: public State {
public:
    OffState() { 
        cout << "Light turned off" << endl;
    }
    void on(LightSwitch* ls) override;
};

void OnState::off(LightSwitch* ls) {
    cout << "Switching light off ..." << endl;
    ls->setState(new OffState());
    delete this;
}

void OffState::on(LightSwitch* ls) {
    cout << "Switching light on ..." << endl;
    ls->setState(new OnState());
    delete this;
}


int main()
{
    auto* lightswitch = new LightSwitch(new OffState());
    //lightswitch->setState(new OnState());
    //lightswitch->setState(new OffState());

    delete lightswitch;
    return 0;
}
#endif