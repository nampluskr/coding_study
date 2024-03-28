### Practice 03 - 설비 전원 On/Off

```cpp
#include <iostream>

using namespace std;

class State
{
public:
        virtual void PressButton() = 0;
};

class Machine
{
private:
        State* onState;
        State* offState;
        State* powerSavingState;
        State* state;

public:
        Machine();
        void PressButton();
        void setonState();
        void setoffState();
        void setpowerSavingState();

        void setState(State* state);
};

class OnState : public State
{
private:
        Machine* machine;
public:
        OnState(Machine* machine);
        virtual void PressButton() override;
};

class OffState : public State
{
private:
        Machine* machine;

public:
        OffState(Machine* machine);
        virtual void PressButton() override;
};

class PowerSavingState : public State
{
private:
        Machine* machine;

public:
        PowerSavingState(Machine* machine);
        virtual void PressButton() override;
};


int main()
{
        Machine* machine = new Machine();
        machine->PressButton();
        machine->PressButton();
        machine->setpowerSavingState();
        machine->PressButton();
        return 0;
}

Machine::Machine()
{
        onState = new OnState(this);
        offState = new OffState(this);
        powerSavingState = new PowerSavingState(this);
        state = onState;
}
void Machine::PressButton()
{
        state->PressButton();
}
void Machine::setonState() { setState(onState); }
void Machine::setoffState() { setState(offState); }
void Machine::setpowerSavingState() { setState(powerSavingState); }

void Machine::setState(State* state)
{
        if (state == powerSavingState)
        {
                if (this->state == onState)
                        cout << "절전 모드로 변경됩니다" << endl;
                else
                        return;
        }
        this->state = state;
}

OnState::OnState(Machine* machine)
{
        this->machine = machine;
}
void OnState::PressButton()
{
        cout << "설비 OFF" << endl;
        machine->setoffState();
}

OffState::OffState(Machine* machine)
{
        this->machine = machine;
}

void OffState::PressButton()
{
        cout << "설비 ON" << endl;
        machine->setonState();
}

PowerSavingState::PowerSavingState(Machine* machine)
{
        this->machine = machine;
}
void PowerSavingState::PressButton()
{
        cout << "설비 ON" << endl;
        machine->setpowerSavingState();
}
```

### 
