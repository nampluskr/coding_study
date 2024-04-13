#if 1
// Chapter 2. Builder
// 2.5 Composite Builder

#include <iostream>
#include <string>
using namespace std;

class PersonAddressBuilder;
class PersonJobBuilder;
class PersonBuilder;
class PersonBuilderBase;


class Person {
    // street_address
    string street_address, post_code, city;

    // emplyment
    string company_name, position;
    int annual_income = 0;

public:
    static PersonBuilder create();

    Person() { cout << ">> Person created\n"; }
    Person(Person&& other)
        : street_address{ move(other.street_address) },
          post_code{ move(other.post_code) },
          city{ move(other.city) },
          company_name{ move(other.company_name) },
          position{ move(other.position) },
          annual_income{ move(other.annual_income) } {}
    ~Person() { cout << ">> Person destroyed\n"; }

    Person& operator=(Person&& other) {
        if (this == &other)
            return *this;

        street_address = move(other.street_address);
        post_code = move(other.post_code);
        city = move(other.city);
        company_name = move(other.company_name);
        position = move(other.position);
        annual_income = move(other.annual_income);

        return *this;
    }

    friend ostream& operator<<(ostream& os, const Person& person) {
        os << "street_address: " << person.street_address << endl
            << "post_code: " << person.post_code << endl
            << "city: " << person.city << endl
            << "company_name: " << person.company_name << endl
            << "position: " << person.position << endl
            << "annual_income: " << person.annual_income;
        return os;
    }

    friend class PersonJobBuilder;
    friend class PersonAddressBuilder;
    friend class PersonBuilder;
};


class PersonBuilderBase {
protected:
    Person& person;
    explicit PersonBuilderBase(Person& person)
        : person(person) {}

public:
    operator Person() const { return move(person); }
    Person get() const { return move(person); }
     
    // builder facets
    PersonAddressBuilder lives() const;
    PersonJobBuilder works() const;
};


class PersonBuilder : public PersonBuilderBase {
    Person p;
public:
    PersonBuilder() : PersonBuilderBase(p) {}
};


class PersonAddressBuilder : public PersonBuilderBase {
    //typedef PersonAddressBuilder Self;
    using Self = PersonAddressBuilder;

public:
    explicit PersonAddressBuilder(Person& person)
        : PersonBuilderBase(person) {}

    Self& at(string street_adress) {
        person.street_address = street_adress;
        return *this;
    }
    Self& with_postcode(string post_code) {
        person.post_code = post_code;
        return *this;
    }
    Self& in(string city) {
        person.city = city;
        return *this;
    }
};


class PersonJobBuilder : public PersonBuilderBase {
    //typedef PersonJobBuilder Self;
    using Self = PersonJobBuilder;
public:
    explicit PersonJobBuilder(Person& person)
        : PersonBuilderBase(person) {}

    Self& at(string company_name) {
        person.company_name = company_name;
        return *this;
    }
    Self& as_a(string position) {
        person.position = position;
        return *this;
    }
    Self& earning(int annual_income) {
        person.annual_income = annual_income;
        return *this;
    }
};

PersonBuilder Person::create() {
    return PersonBuilder{};
}

PersonAddressBuilder PersonBuilderBase::lives() const {
    return PersonAddressBuilder(person);
}

PersonJobBuilder PersonBuilderBase::works() const {
    return PersonJobBuilder(person);
}


int main()
{
    Person person = Person::create()
        .lives().at("123 London Road")
                .with_postcode("SW1 1GB")
                .in("London")
        .works().at("PragmaSoft")
                .as_a("Consultant")
                .earning(10e6);
        //.get();

    cout << person << endl;

    return 0;
}
#endif