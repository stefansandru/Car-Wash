
#include "service.h"
#include "undo.h"
#include "../Exceptions/ExportException.h"
#include "../Exceptions/RepoException.h"
#include <utility>
#include <cassert>
#include <iostream>
#include <random>

void Service::add_srv(string reg, string pr, string model, string type){
    Car car{std::move(reg), std::move(pr), std::move(model), std::move(type)}; // the car to undo later
    Validator::validate(car);
    CarsRepo.add(car);
    undoActions.push_back(std::make_unique<UndoAdd>(CarsRepo, car));
}

void Service::delete_car_srv(const string &registration) {
    Car car = search_car(registration); // returns the car to undo later
    CarsRepo.remove(registration);
    undoActions.push_back(std::make_unique<UndoRemove>(CarsRepo, car));
}

void Service::modify_car_srv(const string& registartion,
                            const string& new_reg,
                            const string& new_pr,
                            const string& new_model,
                            const string& new_type) {
    Validator::validate(Car(new_reg, new_pr, new_model, new_type));
    Car car = search_car(registartion); // returns the car to undo later
    CarsRepo.modify(registartion, new_reg, new_pr, new_model, new_type);
    undoActions.push_back(std::make_unique<UndoModify>(CarsRepo, new_reg, car));
}

Car Service::search_car(const string& registration) {
    auto it = std::find_if(CarsRepo.get_all_cars().begin(), CarsRepo.get_all_cars().end(),
                           [&registration](const Car& c) { return c.get_registration() == registration; });

    if (it != CarsRepo.get_all_cars().end()) { // daca NU AJUNGE la final, deci exista deja
        return *it; // retueza iterator
    } else {
        return {"", "", "", ""}; // returneaza un car gol DACA MASINA EXISTA
    }
}

const vector<Car>& Service::get_all_cars_srv() noexcept{
    return CarsRepo.get_all_cars();
}

vector<Car> Service::general_sort(bool (*less_than_car)(const Car&, const Car&)) {
    vector<Car> sorting = CarsRepo.get_all_cars();
    for(int i = 0; i < sorting.size(); i++){
        for (int j = i+1; j < sorting.size(); j++){
            if (less_than_car(sorting[j], sorting[i]))
                std::swap(sorting[j], sorting[i]);
        }
    }
    return sorting;
}

vector<Car> Service::registration_sort() {
    return general_sort(less_than_registration);
}

vector<Car> Service::producer_and_model_sort() {
    return general_sort(less_than_producer_and_model);
}

vector<Car> Service::type_sort() {
    return general_sort(less_than_type);
}

vector<Car> Service::filterCars(const string &registration,
                                const string &producer,
                                const string &model,
                                const string &type) {
    vector<Car> filtering;
    std::copy_if(CarsRepo.get_all_cars().begin(),
                 CarsRepo.get_all_cars().end(),
                 std::back_inserter(filtering),
                 [&registration, &producer, &model, &type](const Car& c) {
                     return c.get_registration().rfind(registration, 0) == 0 &&
                            c.get_producer().rfind(producer, 0) == 0 &&
                            c.get_model().rfind(model, 0) == 0 &&
                            c.get_type().rfind(type, 0) == 0;
                 });
    return filtering;
}

std::map<string,CarTypeCountDTO> Service::typeAndNumberOfCars() {
    std::map<string,CarTypeCountDTO> dict;
    for (const auto & car : this->get_all_cars_srv())
        if (dict.find(car.get_type()) != dict.end())
            dict[car.get_type()].increment();
        else
            dict[car.get_type()].init(car.get_type());
    return dict;
}

void Service::undo_srv() {
    if (undoActions.empty())
        throw UndoExceptions("\nNo more undo operations!\n");
    undoActions.back()->doUndo();
    undoActions.pop_back();
}

size_t Service::sizeOfWaitingList() {
    return CarWashRepo.size();
}

const vector<Car>& Service::getWaitingList() const{
    return CarWashRepo.getWaitingList();
}

size_t Service::clearWaitingList_srv() {
    CarWashRepo.clearWaitingList();
    return CarWashRepo.size();
}

size_t Service::addToWaitingList_srv(const string& registration) {
    auto car = this->search_car(registration);
    if (car.get_registration().empty())
        throw RepoException("Non-existent car!\n");
    if (isInCarWashList(registration))
        throw RepoException("Car already in waiting list!\n");
    CarWashRepo.addToWaitingList(car);
    return CarWashRepo.size();
}


size_t Service::randomAddToWaitingList_srv(size_t cars_number) {
    vector<Car> allCars = CarsRepo.get_all_cars();
    std::shuffle(allCars.begin(), allCars.end(), std::default_random_engine(std::random_device{}()));

    size_t carsIterator = 0;
    while (CarWashRepo.size() < cars_number && CarWashRepo.size() < allCars.size()) {
        string curentCarRegistration = allCars[carsIterator].get_registration();
        if (!isInCarWashList(curentCarRegistration)) {
            CarWashRepo.addToWaitingList(allCars[carsIterator]);
        }
        carsIterator++;
    }

    return CarWashRepo.size();
}

bool Service::isInCarWashList(string registration) const {
     return std::any_of(CarWashRepo.getWaitingList().begin(),
                        CarWashRepo.getWaitingList().end(),
                        [&registration](const Car &car){
                            return car.get_registration() == registration; });
}
