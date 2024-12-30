

#ifndef LAB8_CARS_V1_CARWASH_H
#define LAB8_CARS_V1_CARWASH_H

#include "../Domain/car.h"
#include "CarsRepository.h"
#include <vector>

using std::vector;

class CarWashRepo {
private:
    vector<Car> waitingList;

public:
    size_t size();
    const vector<Car> & getWaitingList() const;
    void clearWaitingList();
    void addToWaitingList(const Car& car);
//    void randomAddToWaitingList(size_t cars_number, const vector<Car>& cars_list);
};

void test_CarWash();

#endif //LAB8_CARS_V1_CARWASH_H
