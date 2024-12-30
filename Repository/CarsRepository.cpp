
#include "CarsRepository.h"
#include  "../Exceptions/RepoException.h"
#include <vector>
#include <sstream>
#include <algorithm>
#include <utility>
#include <__random/random_device.h>
#include <random>

using std::ifstream;
using std::stringstream;

void CarRepo::add(const Car& car){
    auto it = carIterator(car.get_registration());
    if (it != allCars.end()) {
        throw RepoException("Already existing car!\n");
    }
    allCars.push_back(car);
}

void CarRepo::remove(const string& registration) {
    auto it = carIterator(registration);
    if (it == allCars.end())
        throw RepoException("Non-existent car!\n");
    allCars.erase(it);
}

void CarRepo::modify(const string& registartion,
                     const string& new_reg,
                     const string& new_pr,
                     const string& new_model,
                     const string& new_type) {
    auto it = carIterator(registartion);
    if (it == allCars.end())
        throw RepoException("Non-existent car!\n");

    // Modify the car attributes if it exists
    it->set_registration(new_reg);
    it->set_producer(new_pr);
    it->set_model(new_model);
    it->set_type(new_type);
}

vector<Car>::iterator CarRepo::carIterator(const string& registration) {
    return std::find_if(allCars.begin(), allCars.end(),
                        [&registration](const Car& car) { return car.get_registration() == registration; });
}

const vector<Car>& CarRepo::get_all_cars() const {
    return allCars;
}


void FileRepo::loadFromFile() {
    ifstream in(filename);
    if (!in.is_open()) {
        throw RepoException("Error reading file: " + filename);
    }

    string line;
    while (getline(in, line)) {
        stringstream stream(line);
        string token;
        vector<string> split;
        while (getline(stream, token, ',')) {
            split.push_back(token);
        }
        if (split.size() == 4) {
            string reg = split[0];
            string producer = split[1];
            string model = split[2];
            string type = split[3];
            CarRepo::add({reg, producer, model, type});
        }
    }
    in.close();
}

void FileRepo::writeToFile() {
    std::ofstream out(filename, std::ios::trunc);
    for (const Car &car : allCars) {
        // sau ar trbui sa pui lista de masini, ca in exemplu
        out << car.get_registration() << ","
            << car.get_producer() << ","
            << car.get_model() << ","
            << car.get_type() << '\n';
    }
    out.close();
}

void FileRepo::add(const Car &car) {
    CarRepo::add(car);
    writeToFile();
}

void FileRepo::remove(const string& registration) {
    CarRepo::remove(registration);
    writeToFile();
}

void FileRepo::modify(const string& registartion,
                      const string& new_reg,
                      const string& new_pr,
                      const string& new_model,
                      const string& new_type) {
    CarRepo::modify(registartion, new_reg, new_pr, new_model, new_type);
    writeToFile();
}


void RepoRandomError::add(const Car &o) {
    std::mt19937 mt{ std::random_device{}() };
    std::uniform_int_distribution<> dist(0, 10);
    int rand = dist(mt);
    if (rand < prob)
        throw(RepoException("\nRandom Probability\n\n"));
    auto i = static_cast<int>(carsMap.size());
    carsMap.insert({i,o});
    carsList.push_back(o);
}

void RepoRandomError::remove(const string& registration) {
    std::mt19937 mt{ std::random_device{}() };
    std::uniform_int_distribution<> dist(0, 10);
    int rand = dist(mt);
    if (rand < prob)
        throw(RepoException("\nRandom Probability Error\n\n"));

    // find
    int it = -1;
    for (const auto & i : carsMap)
        if (i.second.get_registration() == registration)
            it = i.first;
    if (it == -1)
        throw RepoException("Non-existent car!\n");

    carsMap.erase(it);
    carsList.erase(carsList.begin() + it);
}

void RepoRandomError::modify(const string& registration,
                             const string& new_reg,
                             const string& new_pr,
                             const string& new_model,
                             const string& new_type){
    std::mt19937 mt{ std::random_device{}() };
    std::uniform_int_distribution<> dist(0, 10);
    int rand = dist(mt);
    if (rand < prob)
        throw(RepoException("\nRandom Probability Error\n\n"));

    // find
    int it = -1;
    for (const auto & i : carsMap)
        if (i.second.get_registration() == registration)
            it = i.first;
    if (it == -1)
        throw RepoException("Non-existent car!\n");
    Car o = carsMap[it];

    carsMap[it].set_registration(new_reg);
    carsMap[it].set_producer(new_pr);
    carsMap[it].set_model(new_model);
    carsMap[it].set_type(new_type);

    carsList[it].set_registration(new_reg);
    carsList[it].set_producer(new_pr);
    carsList[it].set_model(new_model);
    carsList[it].set_type(new_type);
}