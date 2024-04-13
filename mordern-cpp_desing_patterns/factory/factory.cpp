#include <iostream>
#include <memory>

using namespace std;

// 컴퓨터 인터페이스 (추상 기본 클래스)
class Computer {
public:
    virtual void turnOn() = 0;
    virtual void turnOff() = 0;
    virtual void displaySpecs() = 0;

    virtual ~Computer() = default;
};

// 데스크탑 클래스 (구체적인 클래스)
class Desktop : public Computer {
public:
    void turnOn() override {
        cout << "데스크탑을 켭니다." << endl;
    }

    void turnOff() override {
        cout << "데스크탑을 끕니다." << endl;
    }

    void displaySpecs() override {
        cout << "데스크탑 사양: " << endl;
        cout << "- CPU: i7-12700K" << endl;
        cout << "- RAM: 32GB" << endl;
        cout << "- 저장공간: 1TB SSD" << endl;
    }
};

// 노트북 클래스 (구체적인 클래스)
class Laptop : public Computer {
public:
    void turnOn() override {
        cout << "노트북을 켭니다." << endl;
    }

    void turnOff() override {
        cout << "노트북을 끕니다." << endl;
    }

    void displaySpecs() override {
        cout << "노트북 사양: " << endl;
        cout << "- CPU: i5-11400H" << endl;
        cout << "- RAM: 16GB" << endl;
        cout << "- 저장공간: 512GB SSD" << endl;
    }
};

// 팩토리 함수 (컴퓨터 객체 생성)
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
    // 팩토리 함수 사용하여 컴퓨터 객체 생성 및 사용
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
