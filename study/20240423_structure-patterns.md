### [구조_01_adapter]

```cpp
#if 0
// https://www.geeksforgeeks.org/adapter-pattern/

#include <iostream>
#include <string>
using namespace std;


// Target interface (Printer)
class Printer {
public:
    virtual ~Printer() {};
    virtual void print() = 0;
};

class MordernPrinter : public Printer {
public:
    void print() override {
        cout << "Modern Printer is printing a document.\n";
    }
};

// Adaptee (LegacyPrinter)
class LegacyPrinter {
public:
    void printDocument() {
        cout << "Legacy Printer is printing a document.\n";
    }
};

// Adapter (PrinterAdapter)
class PrinterAdpater : public Printer {
private:
    LegacyPrinter _legacyPrinter;
public:
    void print() override { _legacyPrinter.printDocument(); }
};

// Client
class Client {
private:
    Printer* _printer;
public:
    Client(Printer* printer) { setPrinter(printer); }
    void setPrinter(Printer* printer) { _printer = printer; }
    void print() { _printer->print(); }
};

int main()
{
    if (0) {
        MordernPrinter printer;
        PrinterAdpater adapter;

        printer.print();
        adapter.print();
    }

    if (1) {
        MordernPrinter printer;
        PrinterAdpater adapter;

        Client* client = new Client(&printer);
        client->print();

        client->setPrinter(&adapter);
        client->print();

        delete client;
    }


    return 0;
}
#endif
```

- `adapter_1.cpp`

 ```cpp
#if 1
// https://www.geeksforgeeks.org/adapter-pattern-c-design-patterns/
#include <iostream>
#include <string>
using namespace std;

// Legacy Printer vs. Modern Printer


// Target Interface (Printer)
//class Computer {
//public:
//    virtual ~Computer() {};
//    virtual void sendCommand(const string& command) = 0;
//};

class ModernComputer {
public:
    virtual void sendCommand(const string& command) {
        cout << "Sending command: " << command << "\n";
    }
};


// Adaptee (LegacyPrinter)
class LegacyPrinter {
public:
    void printInUpperCase(const string& text) {
        cout << "Printing: " << text << ".\n";
    }
};

// Adapter (PrinterAdpater)
class PrinterAdapter: public ModernComputer {
//class PrinterAdapter {
private:
    LegacyPrinter legacyPrinter;
public:
    void sendCommand(const string& command) {
        string uppercaseCommand = command;
        for (char& c : uppercaseCommand)
            c = toupper(c);
        legacyPrinter.printInUpperCase(uppercaseCommand);
    }
};

// Client
class Client {
private:
    ModernComputer* _computer;
public:
    Client(ModernComputer* computer) { setPrinter(computer); }
    void setPrinter(ModernComputer* computer) { _computer = computer; }
    void sendCommand(const string& command) {
        _computer->sendCommand(command);
    }
};


int main()
{
    if (0) {
        ModernComputer computer;
        PrinterAdapter legacyadapter;

        computer.sendCommand("Print this in lowercase");
        legacyadapter.sendCommand("Print this in lowercase (adapted)");
    };

    if (1) {
        ModernComputer computer;
        PrinterAdapter legacyAdapter;

        Client* client = new Client(&computer);
        client->sendCommand("Print this in lowercase");

        client->setPrinter(&legacyAdapter);
        client->sendCommand("Print this in lowercase (adapted)");

        delete client;
    }

    return 0;
}
#endif
```
