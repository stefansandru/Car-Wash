
#ifndef LAB6_CARS_V1_CAR_H
#define LAB6_CARS_V1_CAR_H

#include <string>
#include <iostream>
#include <utility>

using std::string;
using std::cout;

class CarType {
public:
    static const string Sedan;
    static const string SUV;
    static const string Coupe;
};

class Car{
private:
    string registration;
    string producer;
    string model;
    string type;

public:
    Car() = default;

    Car(string reg, string pr, string model, string type):
            registration{std::move(reg)},
            producer{std::move(pr)},
            model{std::move(model)},
            type{std::move(type)}{}

    Car(const Car& ot):
            registration{(ot.registration)},
            producer{(ot.producer)},
            model{(ot.model)},
            type{(ot.type)} {
        cout << "Copy\n";
    }

    bool operator==(const Car& c) const {
        return this->get_registration() == c.get_registration()
        && this->get_producer() == c.get_producer()
        && this->get_model() == c.get_model()
        && this->get_type() == c.get_type();
    }

    [[nodiscard]] string get_registration() const;
    [[nodiscard]] string get_producer() const;
    [[nodiscard]] string get_model() const;
    [[nodiscard]] string get_type() const;

    void set_registration(const string& new_registration);
    void set_producer(const string& new_producer);
    void set_model(const string& new_model);
    void set_type(const string& new_type);

};

// true if car1 < car2
bool less_than_registration(const Car& car1, const Car& car2);

// true if car1 < car2
bool less_than_producer_and_model(const Car& car1, const Car& car2);

// true if car1 < car2
bool less_than_type(const Car& car1, const Car& car2);

#endif //LAB6_CARS_V1_CAR_H
