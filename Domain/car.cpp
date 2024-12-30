
#include "car.h"

const string CarType::Sedan = "Sedan";
const string CarType::SUV = "SUV";
const string CarType::Coupe = "Coupe";

string Car::get_registration() const{
    return this->registration;
}
string Car::get_producer() const {
     return this->producer;
}
string Car::get_model() const{
    return this->model;
}
string Car::get_type() const{
    return this->type;
}

void Car::set_registration(const string& new_registration) {
    this->registration = new_registration;
}
void Car::set_producer(const string& new_producer) {
    this->producer = new_producer;
}
void Car::set_model(const string& new_model) {
    this->model = new_model;
}
void Car::set_type(const string& new_type) {
    this->type = new_type;
}

bool less_than_registration(const Car& car1, const Car& car2){
    string reg1 = car1.get_registration();
    string reg2 = car2.get_registration();
    std::transform(reg1.begin(), reg1.end(), reg1.begin(), ::tolower);
    std::transform(reg2.begin(), reg2.end(), reg2.begin(), ::tolower);
    return car1.get_registration() < car2.get_registration();
}

bool less_than_producer_and_model(const Car& car1, const Car& car2){
    string prod1 = car1.get_producer();
    string prod2 = car2.get_producer();
    std::transform(prod1.begin(), prod1.end(), prod1.begin(), ::tolower);
    std::transform(prod2.begin(), prod2.end(), prod2.begin(), ::tolower);
    if(prod1 == prod2){
        string model1 = car1.get_model();
        string model2 = car2.get_model();
        std::transform(model1.begin(), model1.end(), model1.begin(), ::tolower);
        std::transform(model2.begin(), model2.end(), model2.begin(), ::tolower);
        return model1 < model2;
    }
    return prod1 < prod2;
}

bool less_than_type(const Car& car1, const Car& car2){
    string type1 = car1.get_type();
    string type2 = car2.get_type();
    std::transform(type1.begin(), type1.end(), type1.begin(), ::tolower);
    std::transform(type2.begin(), type2.end(), type2.begin(), ::tolower);
    return type1 < type2;
}