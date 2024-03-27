### template pattern

```cpp
#include <iostream>
using namespace std;

class CaffeineBeverage {
public:
	void prepareRecipe() {
		boilWater();
		brew();
		pourInCup();
		addCondiments();
	}
protected:
	virtual void brew() {}
	virtual void addCondiments() {}
	void boilWater() { cout << "물 끓이는 중" << endl; }
	void pourInCup() { cout << "컵에 따르는 중" << endl; }
};

class Tea: public CaffeineBeverage {
protected:
	void brew() override {
		cout << "차를 우려내는 중" << endl;
	}
	void addCondiments() override {
		cout << "레몬을 추가하는 중" << endl;
	}
};

class Coffee: public CaffeineBeverage {
protected:
	void brew() override {
		cout << "필터로 커피를 우려내는 중" << endl;
	}
	void addCondiments() override  {
		cout << "설탕과 커피를 추가하는 중" << endl;
	}
};

int main()
{
	cout << endl << ">> Tea:" << endl;
	auto* tea = new Tea();
	tea->prepareRecipe();

	cout << endl << ">> Coffee:" << endl;
	auto* coffee = new Coffee();
	coffee->prepareRecipe();

	delete tea;
	delete coffee;

	return 0;
}
```

### Observer Pattern: Weather Station

```cpp
#include <iostream>
#include <list>
using namespace std;

// Interface
class Observer {
public:
	virtual ~Observer() = default;
	virtual void update(double t, double h, double p) = 0;
};

// Interface
class DisplayElement {
public:
	virtual ~DisplayElement() = default;
	virtual void display() const = 0;
};

// Interface
class Subject {
public:
	virtual ~Subject() = default;
	virtual void registerObserver(Observer *obs) = 0;
	virtual void removeObserver(Observer *obs) = 0;
	virtual void notifyObservers() = 0;
};


class WeatherData : public Subject {
private:
	// TODO: Weather class -> getter & setter
	double temperature = 0.0f;
	double humidity = 0.0f;
	double pressure = 0.0f;
	list<Observer *> observers = {};

public:
	WeatherData() = default;
	void registerObserver(Observer *obs) override {
		observers.push_back(obs);
	}
	void removeObserver(Observer *obs) override {
		if (!observers.empty())
			observers.remove(obs);
	}
	void notifyObservers() override {
		for (auto obs : observers)
			obs->update(temperature, humidity, pressure);
	}
	void measurementChanged() {
		notifyObservers();
	}
	void setMeasurements(const double &t, const double &h, const double &p) {
		temperature = t;
		humidity = h;
		pressure = p;
		measurementChanged();
	}
};


class CurrentConditionsDisplay : public Observer, public DisplayElement {
private:
	double temperature = 0.0f;
	double humidity = 0.0f;
	WeatherData *weatherData = nullptr;

public:
	CurrentConditionsDisplay() = default;
	CurrentConditionsDisplay(WeatherData *wd) : weatherData(wd) {
		weatherData->registerObserver(this);
	}
	void update(double t, double h, double p) override {
		temperature = t;
		humidity = h;
		display();
	}
	void display() const override {
		cout << "Current Conditions: " << temperature
			 << "F degree and " << humidity << "% humidity\n";
	}
};


class ForcastDisplay : public Observer, public DisplayElement {
private:
	double currentPressure = 29.92f;
	double prevPressure = 0.0f;
	Subject *weatherData = nullptr;

public:
	ForcastDisplay() = default;
	ForcastDisplay(Subject *wd) : weatherData(wd) { 
		weatherData->registerObserver(this);
	}
	void update(double t, double h, double p) override {
		prevPressure = currentPressure;
		currentPressure = p;
		display();
	}
	void display() const override {
		cout << "Forcast: ";
		if (currentPressure > prevPressure)
			cout << "Improving weather on the way!\n";
		else if (currentPressure == prevPressure)
			cout << "Forcast: More of the same\n";
		else if (currentPressure < prevPressure)
			cout << "Forcast: Watch out for cooler, rainy weather\n";
	}
};


class StatisticsDisplay : public Observer, public DisplayElement {
private:
	double minTemp = 200.0f;
	double maxTemp = 0.0f;
	double tempSum = 0.0f;
	int numberOfReadings = 0;
	Subject *weatherData = nullptr;

public:
	StatisticsDisplay() = default;
	StatisticsDisplay(Subject *wd) : weatherData(wd) {
		weatherData->registerObserver(this);
	}
	void update(double t, double h, double p) override {
		tempSum += t;
		++numberOfReadings;
		if (t < minTemp)
			minTemp = t;
		if (t > maxTemp)
			maxTemp = t;
		display();
	}
	void display() const override {
		cout << "Avg/Max/Min Temperature = " << tempSum / numberOfReadings << "/" 
			 << maxTemp << "/" << minTemp << '\n';
	}
};


int main()
{
	auto* weatherData = new WeatherData();
	auto currentDisplay = CurrentConditionsDisplay(weatherData);
	
	cout << endl;
	currentDisplay.display();

	cout << endl;
	weatherData->setMeasurements(80, 65, 30.4f);

	auto statsDisplay = StatisticsDisplay(weatherData);
	auto forcastDisplay = ForcastDisplay(weatherData);

	cout << endl;
	weatherData->setMeasurements(80, 65, 30.4f);

	cout << endl;
	weatherData->setMeasurements(82, 70, 29.2f);
	
	cout << endl;
	weatherData->setMeasurements(78, 90, 29.2f);

	return 0;
}
```

### Command Pattern

```cpp
#include <iostream>
using namespace std;

// Interface
class Command {
public:
	virtual ~Command() {};
	virtual void execute() {};
	virtual void undo() {};
};


class Light {
private:
	int state;

public:
	void on() { 
		cout << "Turn on the light!" << endl;
		state = 1;
	}
	void off() {
		cout << "Turn off the light!" << endl;
		state = 0;
	}
};


class LightOnCommand : public Command {
private:
	Light* light;

public:
	LightOnCommand(Light* light) { this->light = light; }
	void execute() override { light->on(); }
	void undo() override { light->off(); }
};


class LightOffCommand : public Command {
private:
	Light* light;

public:
	LightOffCommand(Light* light) { this->light = light; }
	void execute() override { light->off(); }
	void undo() override { light->on(); }
};


class GarageDoor {
public:
	void up() { std::cout << "Garage Door is Up\n"; }
	void down() { std::cout << "Garage Door is Down\n"; }
	void stop() { std::cout << "Garage Door is Stopped\n"; }
	void lightOn() { std::cout << "Garage Door Light is On\n"; }
	void lightOff() { std::cout << "Garage Door Light is Off\n"; }
};


class GarageDoorOpen : public Command {
private:
	GarageDoor *garageDoor;
public:
	GarageDoorOpen(GarageDoor *gd) : garageDoor(gd) { }
	void execute() override { garageDoor->up(); }
	void undo() override { garageDoor->down(); }
};

class GarageDoorClose: public Command {
private:
	GarageDoor *garageDoor;
public:
	GarageDoorClose(GarageDoor *gd) : garageDoor(gd) { }
	void execute() override { garageDoor->down(); }
	void undo() override { garageDoor->up(); }
};

class SimpleRemoteControl {
private:
	Command *slot;

public:
	SimpleRemoteControl() = default;
	void setCommand(Command *command) { slot = command; }
	void buttonWasPressed() { slot->execute(); }

};

class RemoteColtrolWithUndo {
	Command* slots[7];
};

int main()
{
	auto remote = SimpleRemoteControl();

	auto light = new Light();
	auto lightOn = new LightOnCommand(light);

	remote.setCommand(lightOn);
	remote.buttonWasPressed();

	auto lightOff = new LightOffCommand(light);
	remote.setCommand(lightOff);
	remote.buttonWasPressed();

	auto garageDoor = new GarageDoor();
	auto garaggeDoorOpen = new GarageDoorOpen(garageDoor);

	remote.setCommand(garaggeDoorOpen);
	remote.buttonWasPressed();

	delete light;
	delete lightOn;
	delete lightOff;
	delete garageDoor;
	delete garaggeDoorOpen;
}
```
