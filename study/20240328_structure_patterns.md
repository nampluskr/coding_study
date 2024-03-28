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

### Decorator

```cpp
#pragma once
#include <string>
using namespace std;

// [abstract]
class Bread {
protected:
	string desc = "no title";
public:
	//string getDesc() { return desc; }
	virtual string getDesc() = 0;
	virtual int cost() = 0;
};

class Wheat : public Bread {
public:
	Wheat() { desc = "Wheat"; }
	string getDesc() override { return desc; }
	int cost() override { return 100; }
};

class White: public Bread {
public:
	White() { desc = "Wheat"; }
	string getDesc() override { return desc; }
	int cost() override { return 200; }
};
```

```cpp
#pragma once
#include <string>
#include "bread.h"
using namespace std;

// [decorator]
class Vegetable: public Bread {
public:
	//virtual string getDesc() = 0;
};

class Lettuce : public Vegetable {
private:
	Bread* bread;
public:
	Lettuce(Bread* bread) { this->bread = bread; }
	string getDesc() override {
		return bread->getDesc() + ", Lettuce";
	}
	int cost() override { return bread->cost() + 300; }
};

class Tomato: public Vegetable {
private:
	Bread* bread;
public:
	Tomato(Bread* bread) { this->bread = bread; }
	string getDesc() override {
		return bread->getDesc() + ", Tomato";
	}
	int cost() override { return bread->cost() + 400; }
};

```

```cpp
#pragma once

#include <string>
#include "bread.h"
using namespace std;

// [decorator]
class Sauce: public Bread {
public:
	//virtual string getDesc() = 0;
};

class Ranch : public Sauce {
private:
	Bread* bread;
public:
	Ranch(Bread* bread) { this->bread = bread; }
	string getDesc() override {
		return bread->getDesc() + ", Ranch";
	}
	int cost() override { return bread->cost() + 300; }
};

class HonyMustard : public Sauce {
private:
	Bread* bread;
public:
	HonyMustard(Bread* bread) { this->bread = bread; }
	string getDesc() override {
		return bread->getDesc() + ", HonyMustard";
	}
	int cost() override { return bread->cost() + 400; }
};
```

```cpp
#include <iostream>
#include "bread.h"
#include "vegetable.h"
#include "sauce.h"


int main()
{
	Bread* bread1 = new Wheat();
	cout << bread1->getDesc() << " + " << bread1->cost() << "\n";

	cout << endl;
	bread1 = new Lettuce(bread1);
	bread1 = new Lettuce(bread1);
	cout << bread1->getDesc() << " + " << bread1->cost() << "\n";

	cout << endl;
	Bread* bread2 = new White();
	cout << bread2->getDesc() << " + " << bread2->cost() << "\n";

	cout << endl;
	bread2 = new Tomato(bread2);
	bread2 = new Ranch(bread2);
	bread2 = new HonyMustard(bread2);
	cout << bread2->getDesc() << " + " << bread2->cost() << "\n";

	delete bread1;
	delete bread2;

	return 0;
}
```

### Strategy  AGV System
```cpp
#pragma once

#include <iostream>
using namespace std;

// interface
class MoveType {
public:
	virtual ~MoveType() {}
	virtual void move() = 0;
};


class MoveDoubleLegs : public MoveType {
public:
	void move() override { cout << "Move with double legs.\n"; }
};

class MoveRocket: public MoveType {
public:
	void move() override { cout << "Move with rocket.\n"; }
};

class MoveWings: public MoveType {
public:
	void move() override { cout << "Move with wings.\n"; }
};

// interface
class LoadType {
public:
	virtual ~LoadType() {}
	virtual void load() = 0;
};

class LoadRobotArm : public LoadType {
public:
	void load() override { cout << "Load with a robot arm\n"; }
};

class LoadDoubleHands: public LoadType {
public:
	void load() override { cout << "Load with double hands\n"; }
};

class LoadAbsorber: public LoadType {
public:
	void load() override { cout << "Load with a absorber\n"; }
};


// abstract
class Company {
protected:
	MoveType* moveType;
	LoadType* loadType;

public:
	virtual ~Company() {}
	void doMove() { moveType->move(); }
	void doLoad() { loadType->load(); }
	virtual void display() const = 0;
};

class Gadget : public Company{
public:
	Gadget() {
		moveType = new MoveDoubleLegs();
		loadType = new LoadRobotArm();
	}
	void display() const override { cout << ">> Company: Gadget\n"; }
};

class TaekwonV : public Company {
public:
	TaekwonV() {
		moveType = new MoveRocket();
		loadType = new LoadDoubleHands();
	}
	void display() const override { cout << ">> Company: TaekwonV\n"; }
};

class Starwars : public Company {
public:
	Starwars() {
		moveType = new MoveWings();
		loadType = new LoadAbsorber();
	}
	void display() const override { cout << ">> Company: Starwars\n"; }
};
```

```cpp
#include <iostream>
#include "system.h"
using namespace std;

int main()
{
	Company* company1 = new Gadget();
	company1->display();
	company1->doMove();
	company1->doLoad();

	cout << endl;
	Company* company2 = new TaekwonV();
	company2->display();
	company2->doMove();
	company2->doLoad();

	cout << endl;
	Company* company3 = new Starwars();
	company3->display();
	company3->doMove();
	company3->doLoad();

	delete company1;
	delete company2;
	delete company3;
	return 0;
}
```
