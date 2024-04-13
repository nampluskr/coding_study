#include <iostream>
#include <memory>

using namespace std;

// ��ǻ�� �������̽� (�߻� �⺻ Ŭ����)
class Computer {
public:
    virtual void turnOn() = 0;
    virtual void turnOff() = 0;
    virtual void displaySpecs() = 0;

    virtual ~Computer() = default;
};

// ����ũž Ŭ���� (��ü���� Ŭ����)
class Desktop : public Computer {
public:
    void turnOn() override {
        cout << "����ũž�� �մϴ�." << endl;
    }

    void turnOff() override {
        cout << "����ũž�� ���ϴ�." << endl;
    }

    void displaySpecs() override {
        cout << "����ũž ���: " << endl;
        cout << "- CPU: i7-12700K" << endl;
        cout << "- RAM: 32GB" << endl;
        cout << "- �������: 1TB SSD" << endl;
    }
};

// ��Ʈ�� Ŭ���� (��ü���� Ŭ����)
class Laptop : public Computer {
public:
    void turnOn() override {
        cout << "��Ʈ���� �մϴ�." << endl;
    }

    void turnOff() override {
        cout << "��Ʈ���� ���ϴ�." << endl;
    }

    void displaySpecs() override {
        cout << "��Ʈ�� ���: " << endl;
        cout << "- CPU: i5-11400H" << endl;
        cout << "- RAM: 16GB" << endl;
        cout << "- �������: 512GB SSD" << endl;
    }
};

// ���丮 �Լ� (��ǻ�� ��ü ����)
unique_ptr<Computer> createComputer(const string& type) {
    if (type == "desktop") {
        return make_unique<Desktop>();
    }
    else if (type == "laptop") {
        return make_unique<Laptop>();
    }
    else {
        return nullptr;
    }
}

int main() {
    // ���丮 �Լ� ����Ͽ� ��ǻ�� ��ü ���� �� ���
    unique_ptr<Computer> desktop = createComputer("desktop");
    desktop->turnOn();
    desktop->displaySpecs();
    desktop->turnOff();

    unique_ptr<Computer> laptop = createComputer("laptop");
    laptop->turnOn();
    laptop->displaySpecs();
    laptop->turnOff();

    return 0;
}
