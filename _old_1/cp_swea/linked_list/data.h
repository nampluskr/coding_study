#pragma once
#include <ostream>
using namespace std;

struct Data {
    int number, id;

    bool operator==(const Data& data) const {
        return number == data.number && id == data.id;
    }
    // bool operator==(int number) const {
    //     return this->number == number;
    // }
    friend ostream& operator<<(ostream& os, const Data& data) {
        os << "(" << data.number << ", " << data.id << ")";
        return os;
    }
};