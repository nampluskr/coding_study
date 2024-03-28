### Adapter: Turkey

```cpp
#if 1
#include <iostream>
using namespace std;

// [target] interface
class Duck {
public:
	virtual ~Duck() {}
	virtual void quack() = 0;
	virtual void fly() = 0;
};

class MallardDuck : public Duck {
public:
	void quack() override {
		cout << "Quack.\n";
	}
	void fly() override {
		cout << "I'm flying.\n";
	}
};

// [adaptee] interface
class Turkey {
public:
	virtual ~Turkey() {}
	virtual void gobble() = 0;
	virtual void fly() = 0;
};

// [adapter]
class TurkeyAdapter : public Duck {
private:
	Turkey* turkey;
public:
	TurkeyAdapter(Turkey* turkey) {
		this->turkey = turkey;
	}
	void quack() {
		turkey->gobble();
	}
	void fly() {
		for(int i = 0; i < 5; i++)
			turkey->fly();
	}
};

class WildTurkey : public Turkey {
public:
	void gobble() override {
		cout << "Gobble gobble.\n";
	}
	void fly() override {
		cout << "I'm flying a short distance.\n";
	}
};


int main()
{
	cout << "\nThe Duck says ...\n";
	auto* duck = new MallardDuck();
	duck->quack();
	duck->fly();

	cout << "\nThe Turkey says ...\n";
	auto* turkey = new WildTurkey();
	auto* turkeyAdapter = new TurkeyAdapter(turkey);
	turkey->gobble();
	turkey->fly();

	cout << "\nThe Turkey Adapter says ...\n";
	turkeyAdapter->quack();
	turkeyAdapter->fly();

	delete duck;
	delete turkey;
	delete turkeyAdapter;

	return 0;
}
#endif
```
