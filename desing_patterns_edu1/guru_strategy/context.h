#pragma once

#include "strategy.h"

class Context {
private:
    Strategy* strategy_;
public:
    Context(Strategy* strategy = nullptr) { setStragety(strategy); }
    void setStragety(Strategy* strategy) { this->strategy_ = strategy; }
    void doSomethig(const string& data) const {
        cout << ">> [Context] Run business logic\n";
        if (strategy_)
            this->strategy_->excute(data);
        else
            cout << ">> [Context] No Strategy!\n";
    }
};