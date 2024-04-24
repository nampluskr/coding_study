### [행동_01_chain_responsibility]

```cpp
#if 1
// https://www.geeksforgeeks.org/chain-responsibility-design-pattern/
#include <iostream>
#include <vector>
using namespace std;


enum Priority { BASIC=0, INTERMEDIATE, CRITICAL };

class Request {
private:
    Priority priority;
public:
    Request(Priority priority) { this->priority = priority; }
    Priority getPriority() { return priority; }
};


// Handler Interface
class SupportHandler {
public:
    virtual ~SupportHandler() {}
    virtual SupportHandler* setNextHandler(SupportHandler* nextHandler) = 0;
    virtual void handdlerRequest(Request* request) = 0;
};

// Concrete handlers
class Level1SupprotHandler : public SupportHandler {
private:
    SupportHandler* nextHandeler;
public:
    SupportHandler* setNextHandler(SupportHandler* nextHandler) override {
        this->nextHandeler = nextHandler;
        return nextHandeler;
    }
    void handdlerRequest(Request* request) override {
        if (request->getPriority() == Priority::BASIC)
            cout << "Level 1 Support handled the request.\n";
        else if (nextHandeler != nullptr)
            nextHandeler->handdlerRequest(request);
    }
};

class Level2SupprotHandler : public SupportHandler {
private:
    SupportHandler* nextHandeler;
public:
    SupportHandler* setNextHandler(SupportHandler* nextHandler) override {
        this->nextHandeler = nextHandler;
        return nextHandeler;
    }
    void handdlerRequest(Request* request) override {
        if (request->getPriority() == Priority::INTERMEDIATE)
            cout << "Level 2 Support handled the request.\n";
        else if (nextHandeler != nullptr)
            nextHandeler->handdlerRequest(request);
    }
};

class Level3SupprotHandler : public SupportHandler {
private:
    SupportHandler* nextHandeler;
public:
    SupportHandler* setNextHandler(SupportHandler* nextHandler) override {
        this->nextHandeler = nextHandler;
        return nextHandeler;
    }
    void handdlerRequest(Request* request) override {
        if (request->getPriority() == Priority::CRITICAL)
            cout << "Level 3 Support handled the request.\n";
        else
            cout << "Request cannot be handled.\n";
    }
};


// Client


int main()
{
    if (1) {
        SupportHandler* level1Handler = new Level1SupprotHandler();
        SupportHandler* level2Handler = new Level2SupprotHandler();
        SupportHandler* level3Handler = new Level3SupprotHandler();

        level1Handler->setNextHandler(level2Handler)->setNextHandler(level3Handler);

        //level1Handler->setNextHandler(level2Handler);
        //level2Handler->setNextHandler(level3Handler);

        Request* request1 = new Request(Priority::BASIC);
        Request* request2 = new Request(Priority::INTERMEDIATE);
        Request* request3 = new Request(Priority::CRITICAL);

        level1Handler->handdlerRequest(request1);
        level1Handler->handdlerRequest(request2);
        level1Handler->handdlerRequest(request3);

        delete level1Handler;
        delete level2Handler;
        delete level3Handler;

        delete request1;
        delete request2;
        delete request3;
    }

    cout << endl;
    if (1) {
        Level1SupprotHandler handler1;
        Level2SupprotHandler handler2;
        Level3SupprotHandler handler3;

        handler1.setNextHandler(&handler2)->setNextHandler(&handler3);

        //handler1.setNextHandler(&handler2);
        //handler2.setNextHandler(&handler3);

        Request req1{ Priority::BASIC };
        Request req2{ Priority::INTERMEDIATE };
        Request req3{ Priority::CRITICAL };

        handler1.handdlerRequest(&req1);
        handler2.handdlerRequest(&req2);
        handler3.handdlerRequest(&req3);
    }

    return 0;
}
#endif
```

### [행동_02_command]

```cpp
#if 1
#include <iostream>
#include <vector>
using namespace std;

// Receiver
class Device {
public:
    virtual ~Device() {}
    virtual void turnOn() const = 0;
    virtual void turnOff() const = 0;
};

class TV : public Device {
public:
    void turnOn() const override { cout << "TV is now on.\n"; }
    void turnOff() const override { cout << "TV is now off.\n"; }
    void changeChannel() const { cout << "Channel changed.\n"; }
};

class Stereo : public Device {
public:
    void turnOn() const override { cout << "Stereo is now on.\n"; }
    void turnOff() const override { cout << "Stereo is now off.\n"; }
    void adjustVolume() const { cout << "Volume adjusted.\n"; }
};


// Command Interface (Absract class)
class Command {
public:
    virtual ~Command() {}
    virtual void execute() const = 0;
};

// Concrete Commands
class TurnOnCommand : public Command {
private:
    Device* device;
public:
    TurnOnCommand(Device* device) : device(device) {}
    void execute() const override { device->turnOn(); }
};

class TurnOffCommand : public Command {
private:
    Device* device;
public:
    TurnOffCommand(Device* device) : device(device) {}
    void execute() const override { device->turnOff(); }
};

class AdjustVolumeCommand : public Command {
private:
    Stereo* stereo;
public:
    AdjustVolumeCommand(Stereo* stereo) : stereo(stereo) {}
    void execute() const override { stereo->adjustVolume(); }
};

class ChangeChannelCommand : public Command {
private:
    TV* tv;
public:
    ChangeChannelCommand(TV* tv) : tv(tv) {}
    void execute() const override { tv->changeChannel(); }
};

// Invoker
class RemoteControl {
private:
    Command* command;
public:
    void setCommand(Command* command) { this->command = command; }
    void pressButton() { command->execute(); }
};


int main()
{
    if (0) {
        // create devices
        TV* tv = new TV();
        Stereo* stereo = new Stereo();

        // create commands
        Command* turnOnTV = new TurnOnCommand(tv);
        Command* turnOffTV = new TurnOffCommand(tv);
        Command* adjustVolumeStereo = new AdjustVolumeCommand(stereo);
        Command* changeChannelTV = new ChangeChannelCommand(tv);

        RemoteControl* remote = new RemoteControl();

        remote->setCommand(turnOnTV);
        remote->pressButton();

        remote->setCommand(turnOffTV);
        remote->pressButton();

        remote->setCommand(adjustVolumeStereo);
        remote->pressButton();

        remote->setCommand(changeChannelTV);
        remote->pressButton();

        delete tv;
        delete stereo;
        delete remote;
        delete turnOnTV;
        delete turnOffTV;
        delete adjustVolumeStereo;
        delete changeChannelTV;
    }
    if (1) {
        // create devices
        TV tv;
        Stereo stereo;

        // create commands
        TurnOnCommand turnOnTV(&tv);
        TurnOffCommand turnOffTV(&tv);
        AdjustVolumeCommand adjustVolumeStereo(&stereo);
        ChangeChannelCommand changeChannelTV(&tv);

        RemoteControl remote;

        remote.setCommand(&turnOnTV);
        remote.pressButton();

        remote.setCommand(&turnOffTV);
        remote.pressButton();

        remote.setCommand(&adjustVolumeStereo);
        remote.pressButton();

        remote.setCommand(&changeChannelTV);
        remote.pressButton();
    }

    return 0;
}
#endif
```

### [행동_04_mediator]

```cpp
#if 1
// https://www.geeksforgeeks.org/mediator-design-pattern/

#include <iostream>
#include <string>
using namespace std;


// Colleague
class AirPlane {
public:
    virtual ~AirPlane() {}
    virtual void requestTakeOff() = 0;
    virtual void requestLanding() = 0;
    virtual void notifyAirTrafficControl(const string& message) = 0;
};

// Mediator (Abstract)
class AirTrafficControlTower {
public:
    virtual void requestTakeOff(AirPlane* airplane) = 0;
    virtual void requestLanding(AirPlane* airplane) = 0;
};

// Concrete Colleague
class CommercialAirPlane : public AirPlane {
private:
    AirTrafficControlTower* mediator;
public:
    CommercialAirPlane(AirTrafficControlTower* mediator): mediator(mediator) {}
    void requestTakeOff() override {
        mediator->requestTakeOff(this);
    }
    void requestLanding() override {
        mediator->requestLanding(this);
    }
    void notifyAirTrafficControl(const string& message) override {
        cout << "Commercial Airplane: " << message << endl;
    }

};

// Concrete Mediator
class AirPortControlTower : public AirTrafficControlTower {
public:
    void requestTakeOff(AirPlane* airplane) override {
        cout << "Requesting takeoff clearance.\n";
    }
    void requestLanding(AirPlane* airplane) override {
        cout << "Requesting landing clearance.\n";
    }
};



int main()
{
    if (0) {
        AirTrafficControlTower* controlTower = new AirPortControlTower();

        AirPlane* airplane1 = new CommercialAirPlane(controlTower);
        AirPlane* airplane2 = new CommercialAirPlane(controlTower);

        airplane1->requestTakeOff();
        airplane2->requestLanding();

        delete controlTower;
        delete airplane1;
        delete airplane2;
    }
    if (1) {
        AirPortControlTower controlTower;
        CommercialAirPlane airplane1(&controlTower);
        CommercialAirPlane airplane2(&controlTower);

        airplane1.requestTakeOff();
        airplane2.requestLanding();
    }
    return 0;
}
#endif
```

### [행동_05_memento]

```cpp
#if 1
// https://www.geeksforgeeks.org/memento-design-pattern/

#include <iostream>
#include <string>
#include <vector>
using namespace std;

// Memento
class DocumentMemento {
private:
    string content;
public:
    DocumentMemento(const string& content) : content(content) {}
    string getSavedContent() { return content; }
};


// Originator
class Document {
private:
    string content;
public:
    Document(const string& content): content(content) {}
    void write(const string& text) { content += text; }
    string getContent() const { return content; }
    DocumentMemento* createMemento() { return new DocumentMemento(content); }
    void restoreFromMemento(DocumentMemento* memento) {
        content = memento->getSavedContent();
    }
};

// Caretaker
class History {
private:
    vector<DocumentMemento*> mementos;
public:
    //History() {}
    void addMemento(DocumentMemento* memento) { mementos.push_back(memento); }
    DocumentMemento* getMemento(int index) { return mementos[index]; }
};

// Client


int main()
{
    if (1) {
        Document* document = new Document("Initial content\n");
        History* history = new History();

        // Write some content
        document->write("Additional content\n");
        history->addMemento(document->createMemento());     // index = 0
        cout << document->getContent();
        cout << "======================\n\n";

        // Write some Content
        document->write("More content\n");
        history->addMemento(document->createMemento());     // index = 1
        cout << document->getContent();
        cout << "======================\n\n";

        // Restore to previous state
        document->restoreFromMemento(history->getMemento(0));
        cout << document->getContent();

        document->restoreFromMemento(history->getMemento(1));
        cout << document->getContent();

        delete document;
        delete history;
    }
    return 0;
}
#endif
```

### [행동_06_oberver]

```cpp
#if 1
// https://www.geeksforgeeks.org/observer-pattern-c-design-patterns/
#include <iostream>
#include <string>
#include <vector>
using namespace std;

// Observer (Interface)
class Observer {
public:
    virtual ~Observer() {};
    virtual void update(int temperature, int humidity, int pressure) = 0;
};

// Subject
class WeatherStation {
private:
    int temperature, humidity, pressure;
    vector<Observer*> observers;
public:
    void registerObserver(Observer* observer) { observers.push_back(observer); }
    void removeObserver(Observer* observer) {}
    void notifyObservers() const {
        for (const auto obs : observers)
            obs->update(temperature, humidity, pressure);
    }
    void setMeasurements(int temperature, int humidity, int pressure) {
        this->temperature = temperature;
        this->humidity = humidity;
        this->pressure = pressure;
        notifyObservers();
    }
};

// Concrete Observer
class Display : public Observer {
public:
    void update(int temperature, int humidity, int pressure) {
        cout << "Display: Temperature = " << temperature
            << "°C, Humidity = " << humidity
            << "%, Pressure = " << pressure << " hPa"
            << endl;
    }
};


int main()
{
    WeatherStation station;

    Display display1, display2;
    station.registerObserver(&display1);
    station.registerObserver(&display2);

    station.setMeasurements(25, 60, 1013);
    //station.setMeasurements(20, 50, 1000);

    return 0;
}
#endif
```
