### [생성_01_factory-method]

```cpp
#if 1
// https://www.geeksforgeeks.org/factory-method-for-designing-pattern/
// pointer version

#include <iostream>
using namespace std;

// Product interface
class Vehicle {
public:
    virtual ~Vehicle() {};
    virtual void printVehicle() const = 0;
};

// Concrete Products
class TwoWheeler : public Vehicle {
public:
    void printVehicle() const override { cout << "I am two wheeler\n"; }
};

class FourWheeler : public Vehicle {
public:
    void printVehicle() const override { cout << "I am four wheeler\n"; }
};

// Creator Interface
class VehicleFactory {
public:
    virtual ~VehicleFactory() {};
    virtual Vehicle* createVehicle() const = 0;
};

// Concrete Creators
class TwoWheelerFactory : public VehicleFactory {
public:
    Vehicle* createVehicle() const override { return new TwoWheeler(); }
};

class FourWheelerFactory : public VehicleFactory {
public:
    Vehicle* createVehicle() const override { return new FourWheeler(); }
};

// Client
class Client {
private:
    Vehicle* _vehicle;
public:
    Client(VehicleFactory* factory) { _vehicle = factory->createVehicle(); }
    Vehicle* getVehicle() { return _vehicle; }
};


int main()
{
    VehicleFactory* twoWheelerFactory = new TwoWheelerFactory{};
    Client* twoWheelerClient = new Client(twoWheelerFactory);
    Vehicle* twoWheeler = twoWheelerClient->getVehicle();
    twoWheeler->printVehicle();

    VehicleFactory* FourWheelFactory = new FourWheelerFactory{};
    Client* fourWheelerClient = new Client(FourWheelFactory);
    Vehicle* fourWheeler = fourWheelerClient->getVehicle();
    fourWheeler->printVehicle();

    delete twoWheeler;
    delete twoWheelerClient;
    delete fourWheeler;
    delete fourWheelerClient;

    return 0;
}
#endif
```

### [생성_02_abstract_factory]

```cpp
#if 1
// https://www.geeksforgeeks.org/abstract-factory-pattern/
#include <iostream>
using namespace std;

// Abstract product interfaces
class Car {
public:
    virtual ~Car() {};
    virtual void assemble() const = 0;
};

class CarSpec {
public:
    virtual ~CarSpec() {};
    virtual void display() const = 0;
};

// Concrete products for Car
class Sedan : public Car {
public:
    void assemble() const override { cout << "Assembling Sedan car.\n"; }
};

class Hatchback: public Car {
public:
    void assemble() const override { cout << "Assembling Hatchback car.\n"; }
};

// Concrete product for CarSpec
class NorthAmericaSpec : public CarSpec {
public:
    void display() const override {
        cout << "North America Car Spec.: Safety features compliant with local regulations.\n";
    }
};

class EuropeSpec: public CarSpec {
public:
    void display() const override {
        cout << "Europe Car Spec.: Fuel efficiency and emissions compliant with EU standards.";
    }
};


// Abstract factory interface
class CarFactory {
public:
    virtual ~CarFactory() {};
    virtual Car* createCar() const = 0;
    virtual CarSpec* createSpec() const = 0;
};


// Concrete factories
class NorthAmericaCarFactory : public CarFactory {
public:
    Car* createCar() const override { return new Sedan(); }
    CarSpec* createSpec() const override { return new NorthAmericaSpec(); }
};


class EuropeCarFactory: public CarFactory {
public:
    Car* createCar() const override { return new Hatchback(); }
    CarSpec* createSpec() const override { return new EuropeSpec(); }
};


// Client
class Client {
private:
    Car* _car;
    CarSpec* _carSpec;
public:
    Client(CarFactory* carFactory) {
        _car= carFactory->createCar();
        _carSpec = carFactory->createSpec();
    }
    Car* getCar() { return _car; }
    CarSpec* getSpec() { return _carSpec; }

};


int main()
{
    if (0) {
        CarFactory* northAmeriaFactory = new NorthAmericaCarFactory();
        Car* northAmericaCar = northAmeriaFactory->createCar();
        CarSpec* northAmericaSpec = northAmeriaFactory->createSpec();

        northAmericaCar->assemble();
        northAmericaSpec->display();

        delete northAmeriaFactory;
        delete northAmericaCar;
        delete northAmericaSpec;

        CarFactory* europeFactory = new EuropeCarFactory();
        Car* europeCar = europeFactory->createCar();
        CarSpec* europeSpec = europeFactory->createSpec();

        europeCar->assemble();
        europeSpec->display();

        delete europeFactory;
        delete europeCar;
        delete europeSpec;
    }
    if (1) {
        Client* northAmericaClient = new Client(new NorthAmericaCarFactory());
        Car* northAmericaCar = northAmericaClient->getCar();
        CarSpec* northAmericaSpec = northAmericaClient->getSpec();

        northAmericaCar->assemble();
        northAmericaSpec->display();

        delete northAmericaClient;
        delete northAmericaCar;
        delete northAmericaSpec;

        Client* europeClient = new Client(new EuropeCarFactory());
        Car* europeCar = europeClient->getCar();
        CarSpec* europeSpec = europeClient->getSpec();

        europeCar->assemble();
        europeSpec->display();

        delete europeClient;
        delete europeCar;
        delete europeSpec;
    }

    return 0;
}
#endif
```

### [생성_03_builder]

- `builder_ptr.cpp`

```cpp
#if 0
// https://www.geeksforgeeks.org/builder-design-pattern/
#include <iostream>
#include <string>
using namespace std;


// Product
class Computer {
private:
    string _cpu;
    string _ram;
    string _storage;
public:
    void setCPU(const string& cpu) { _cpu = cpu; }
    void setRAM(const string& ram) { _ram = ram; }
    void setStorage(const string& storage) { _storage = storage; }
    void info() const {
        cout << "Computer Spec:"
             << "\nCPU: " << _cpu
             << "\nRAM: " << _ram
             << "\nStorage: " << _storage << "\n\n";
    }
};

// Builder Interface
class Builder {
public:
    virtual ~Builder() {};
    virtual void buildCPU() = 0;
    virtual void buildRAM() = 0;
    virtual void buildStorage() = 0;
    virtual Computer getComputer() = 0;
};

// Concrete Builders
class GamingComputerBuilder : public Builder {
private:
    Computer* _computer;
public:
    GamingComputerBuilder() { _computer = new Computer(); }
    ~GamingComputerBuilder() { delete _computer; }
    void buildCPU() override { _computer->setCPU("Gaming CPU"); }
    void buildRAM() override { _computer->setRAM("16G DDR4"); }
    void buildStorage() override { _computer->setStorage("1TB SSD"); }
    Computer getComputer() override { return *_computer; }
};

// Concrete Builders
class LaptopComputerBuilder : public Builder {
private:
    Computer* _computer;
public:
    LaptopComputerBuilder() { _computer = new Computer(); }
    ~LaptopComputerBuilder() { delete _computer; }
    void buildCPU() override { _computer->setCPU("CPU"); }
    void buildRAM() override { _computer->setRAM("8G DDR4"); }
    void buildStorage() override { _computer->setStorage("500GB HDD"); }
    Computer getComputer() override { return *_computer; }
};

// Director
class ComputerDirector {
public:
    void construct(Builder* builder) {
        builder->buildCPU();
        builder->buildRAM();
        builder->buildStorage();
    }
};


int main()
{
    GamingComputerBuilder* gamingBuilder = new GamingComputerBuilder();
    LaptopComputerBuilder* laptopBuilder = new LaptopComputerBuilder();
    ComputerDirector director;

    director.construct(gamingBuilder);
    Computer gamingComputer = gamingBuilder->getComputer();
    gamingComputer.info();

    director.construct(laptopBuilder);
    Computer laptopComputer = laptopBuilder->getComputer();
    laptopComputer.info();

    delete gamingBuilder;
    delete laptopBuilder;

    return 0;
}
#endif
```

- `builder_ref.cpp`

```cpp
#if 1
// https://www.geeksforgeeks.org/builder-design-pattern/
#include <iostream>
#include <string>
using namespace std;


// Product
class Computer {
private:
    string _cpu;
    string _ram;
    string _storage;
public:
    void setCPU(const string& cpu) { _cpu = cpu; }
    void setRAM(const string& ram) { _ram = ram; }
    void setStorage(const string& storage) { _storage = storage; }
    void info() const {
        cout << "Computer Spec:"
             << "\nCPU: " << _cpu
             << "\nRAM: " << _ram
             << "\nStorage: " << _storage << "\n\n";
    }
};

// Builder Interface
class Builder {
public:
    virtual ~Builder() {};
    virtual void buildCPU() = 0;
    virtual void buildRAM() = 0;
    virtual void buildStorage() = 0;
    virtual Computer getComputer() = 0;
};

// Concrete Builders
class GamingComputerBuilder : public Builder {
private:
    Computer _computer;
public:
    void buildCPU() override { _computer.setCPU("Gaming CPU"); }
    void buildRAM() override { _computer.setRAM("16G DDR4"); }
    void buildStorage() override { _computer.setStorage("1TB SSD"); }
    Computer getComputer() override { return _computer; }
};

// Concrete Builders
class LaptopComputerBuilder : public Builder {
private:
    Computer _computer;
public:
    void buildCPU() override { _computer.setCPU("CPU"); }
    void buildRAM() override { _computer.setRAM("8G DDR4"); }
    void buildStorage() override { _computer.setStorage("500GB HDD"); }
    Computer getComputer() override { return _computer; }
};

// Director
class ComputerDirector {
public:
    void construct(Builder& builder) {
        builder.buildCPU();
        builder.buildRAM();
        builder.buildStorage();
    }
};


int main()
{
    GamingComputerBuilder gamingBuilder;
    LaptopComputerBuilder laptopBuilder;
    ComputerDirector director;

    director.construct(gamingBuilder);
    Computer gamingComputer = gamingBuilder.getComputer();
    gamingComputer.info();

    director.construct(laptopBuilder);
    Computer laptopComputer = laptopBuilder.getComputer();
    laptopComputer.info();

    return 0;
}
#endif
```

### [생성_04_prototype]

```cpp
#if 1
// https://www.geeksforgeeks.org/prototype-pattern-c-design-patterns/
// https://www.geeksforgeeks.org/prototype-design-pattern/
#include <iostream>
using namespace std;


// Prototype Interface
class Shape {
public:
    virtual ~Shape() {};
    virtual Shape* clone() const = 0;
    virtual void draw() const = 0;
};

// Concrete Prototypes
class Circle : public Shape {
private:
    int _radius;
public:
    Circle(int radius) { _radius = radius; }
    Shape* clone() const override { return new Circle(*this); }
    void draw() const override { 
        cout << "Drawing a circle with radius " << _radius << ".\n";
    }
};

class Rectangle: public Shape {
private:
    int _width, _height;
public:
    Rectangle(int width, int height) { _width = width; _height = height; }
    Shape* clone() const override { return new Rectangle(*this); }
    void draw() const override { 
        cout << "Drawing a rectangle with width " << _width 
            << " and height " << _height << ".\n";
    }
};


// Client
class ShapeClient {
private:
    Shape* _shapePrototype;
public:
    ShapeClient(Shape* shapePrototype=nullptr) {
        _shapePrototype = shapePrototype;
    }
    Shape* createShape() { return _shapePrototype->clone(); }
    void setPrototype(Shape* shapePrototype) { 
        _shapePrototype = shapePrototype;
    }
};


int main()
{
    if (0) {
        Shape* circlePrototype = new Circle(5);
        ShapeClient* client = new ShapeClient(circlePrototype);
        Shape* redCircle = client->createShape();

        redCircle->draw();

        delete circlePrototype;
        delete client;
    }

    if (0) {
        Circle circle(5);
        Rectangle rectangle(4, 6);

        Shape* shape1 = circle.clone();
        Shape* shape2 = rectangle.clone();

        shape1->draw();
        shape2->draw();

        delete shape1;
        delete shape2;
    }

    if (1) {
        ShapeClient* client = new ShapeClient();

        Circle circle(5);
        client->setPrototype(&circle);
        Shape* shape1 = client->createShape();
        shape1->draw();

        Rectangle rectangle(4, 6);
        client->setPrototype(&rectangle);
        Shape* shape2 = client->createShape();
        shape2->draw();

        delete client;
    }

    return 0;
}
#endif
```

### [생성_05_singleton]

- `singleton_ptr.cpp`

```cpp
#if 1
// https://www.geeksforgeeks.org/singleton-pattern-c-design-patterns/
#include <iostream>
#include <string>

using namespace std;


class Singleton {
private:
    string _name;
    static Singleton* instance;
    Singleton(const string name) {
        _name = name;
        cout << "Singleton instance is created.\n";
    }
    ~Singleton() {
        cout << "Singleton instance is destroyed.\n";
    }

public:
    static Singleton* getInstance(const string& name) {
        if (!instance)
            instance = new Singleton(name);
        return instance;
    }
    void someOpreations() {
        cout << "Singleton is performing some operations\n";
    }
    // Delete copy constructor
    Singleton(const Singleton&) = delete;
    // Delete assignment operator
    Singleton& operator=(const Singleton&) = delete;
    string name() const { return _name; }
};

Singleton* Singleton::instance = nullptr;

int main()
{
    Singleton* instance1 = Singleton::getInstance("first");
    instance1->someOpreations();

    Singleton* instance2 = Singleton::getInstance("second");
    instance2->someOpreations();

    cout << "instance1: " << &instance1 << " name: " << instance1->name() << "\n";
    cout << "instance2: " << &instance2 << " name: " << instance2->name() << "\n";

    return 0;
}
#endif
```

- `singleton_ref.cpp`
 
```cpp
#if 0
// https://www.geeksforgeeks.org/singleton-pattern-c-design-patterns/
#include <iostream>
#include <string>

using namespace std;

class Singleton {
private:
    string _name;
    static Singleton* instance;
    Singleton(const string name) { 
        _name = name;
        cout << "Singleton instance is created.\n";
    }
    ~Singleton() { 
        cout << "Singleton instance is destroyed.\n";
    }

public:
    static Singleton& getInstance(const string& name) {
        if (!instance)
            instance = new Singleton(name);
        return *instance;
    }
    void someOpreations() { 
        cout << "Singleton is performing some operations\n";
    }
    // Delete copy constructor
    Singleton(const Singleton&) = delete;
    // Delete assignment operator
    Singleton& operator=(const Singleton&) = delete;
    string name() const { return _name; }
};

Singleton* Singleton::instance = nullptr;

int main()
{
    Singleton& instance1 = Singleton::getInstance("first");
    instance1.someOpreations();

    Singleton& instance2 = Singleton::getInstance("second");
    instance2.someOpreations();

    cout << "instance1: " << &instance1 << " name: " << instance1.name() << "\n";
    cout << "instance2: " << &instance2 << " name: " << instance2.name() << "\n";

    return 0;
}
#endif
```
