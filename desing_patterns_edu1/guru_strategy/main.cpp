#include "context.h"
#include "strategy.h"

void client_code(Strategy* stratgy) {
    
}

int main()
{
    Context* context = new Context;
    context->doSomethig("the given data");

    cout << endl;
    context->setStragety(new ConcreteStrategyA);
    context->doSomethig("the given data");

    cout << endl;
    context->setStragety(new ConcreteStrategyB);
    context->doSomethig("the given data");

    delete context;
    return 0;
}