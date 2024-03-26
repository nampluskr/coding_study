### [simUDuck]

```cpp
#include <iostream>

class FlyBehavior {
public:
	FlyBehavior() {};
	virtual ~FlyBehavior() {};

	virtual void fly() = 0;
};

class FlyWithWings : public FlyBehavior {
public:
	FlyWithWings() {};
	virtual ~FlyWithWings() {};

	void fly() { std::cout << "\n날고 있어요!\n"; }
};

class FlyNoWay : public FlyBehavior {
public:
	FlyNoWay() {};
	virtual ~FlyNoWay() {};

	void fly() { std::cout << "\n저는 못 날아요!\n"; }
};

class FlyRocketPowered: public FlyBehavior {
public:
	FlyRocketPowered() {};
	virtual ~FlyRocketPowered() {};

	void fly() { std::cout << "\n로켓 추진으로 날아갑니다!\n"; }
};

class QuackBehavior {
public:
	QuackBehavior() {};
	virtual ~QuackBehavior() {};

	virtual void quack() = 0;
};

class Quack : public QuackBehavior {
public:
	Quack() {};
	virtual ~Quack() {};

	void quack() { std::cout << "\n꽥!\n"; }
};

class MuteQuack : public QuackBehavior {
public:
	MuteQuack() {};
	virtual ~MuteQuack() {};

	void quack() { std::cout << "\n<< 조용~ >>\n"; }
};

class Squeak : public QuackBehavior {
public:
	Squeak() {};
	virtual ~Squeak() {};

	void quack() { std::cout << "\n삑!\n"; }
};


class Duck {
private:
	FlyBehavior *flyBehavior = nullptr;
	QuackBehavior *quackBehavior = nullptr;

public:
	Duck() {}
	virtual ~Duck() {
		delete flyBehavior;
		delete quackBehavior;
	}

	void setFlyBehavior(FlyBehavior *fb) {
		delete flyBehavior;
		flyBehavior = fb;
	}
	void setQuackBehavior(QuackBehavior *qb) {
		delete quackBehavior;
		quackBehavior = qb;
	}

	void performFly() {
		flyBehavior->fly();
	}
	void performQuack() {
		quackBehavior->quack();
	}

	virtual void display() = 0;
};

class MallardDuck : public Duck {
public:
	MallardDuck() {
		setFlyBehavior(new FlyWithWings());
		setQuackBehavior(new Quack());
	}
	virtual ~MallardDuck() {}

	void display() {
		std::cout << "\nI'm a real Mallard duck!\n";
	}
};

int main()
{
	MallardDuck mallard;
	mallard.display();
	mallard.performFly();
	mallard.performQuack();

	mallard.setFlyBehavior(new FlyRocketPowered());
	mallard.performFly();

	return 0;
}
```

### [Simple Factor]

```cpp
#if 1
// https://github.com/fsaadatmand/Head-First-Design-Pattern-CPP-Examples/blob/master/Factory/pizzas
#include <iostream>
#include <string>
#include <vector>
//#include <memory>
using namespace std;

class Pizza {
protected:
	string name = {};
	string dough = {};
	string sauce = {};
	vector<string> toppings = {};

public:
	Pizza() = default;
	virtual ~Pizza() = default; // necessay if class includes a virtual function

	virtual void prepare() const {
		cout << "Preparing " + name;
		cout << "Tossing dough...\n";
		cout << "Adding sauce...\n";
		cout << "Adding toppings: \n";
		for (const auto &topping : toppings)
			cout << "   " + topping << '\n';
	}
	virtual void bake() const { cout << "Bake for 25 minutes at 350\n"; }
	virtual void cut() const { cout << "Cutting the pizza into diagonal slices\n"; }
	virtual void box() const { cout << "Place pizza in offical PizzaStore box\n"; }
	string getName() const { return name; }
};

class CheesePizza : public Pizza {
public:
	CheesePizza() {
		name = "Cheese Pizza";
		dough = "Thin Crust Dough";
		sauce = "Marinara sauce";
		toppings.push_back("Grated Regiano Cheese");
	}
};

class ClamPizza : public Pizza {
public:
	ClamPizza() {
		name = "Clam Pizza";
		dough = "Thin Crust Dough";
		sauce = "Marinara sauce";
		toppings.push_back("Grated Regiano Clam");
		toppings.push_back("Fresh Clams");
	}
};


class VeggiePizza : public Pizza {
public:
	VeggiePizza() {
		name = "Veggie Pizza";
		dough = "Thin Crust Dough";
		sauce = "Marinara sauce";
		toppings.push_back("Grated Regiano Veggie");
		toppings.push_back("Fresh Veggies");
	}
};

class SimplePizzaFactory {
public:
	Pizza* createPizza(string type) {
		if (type == "cheese")
			return new CheesePizza();
		if (type == "clam")
			return new ClamPizza();
		if (type == "veggie")
			return new VeggiePizza();
		return nullptr; // no match
	}
};


class PizzaStore {
private:
	SimplePizzaFactory* factory = nullptr;

public:
	PizzaStore() = default;
	PizzaStore(SimplePizzaFactory* f) : factory(f) {}

	Pizza* orderPizza(string type) {
		auto pizza = factory->createPizza(type);
		pizza->prepare();
		pizza->bake();
		pizza->cut();
		pizza->box();
		return pizza;
	}
};

int main()
{
	auto factory = new SimplePizzaFactory();
	auto pizzaStore = PizzaStore(factory);
	auto pizza = pizzaStore.orderPizza("cheese");

	return 0;
}
#endif
```
