
#include "CarWashRepository.h"
#include "../Domain/car.h"
#include <vector>
#include <random>
#include <assert.h>
using std::vector;

size_t CarWashRepo::size() {
    return waitingList.size();
}

const vector<Car> & CarWashRepo::getWaitingList() const {
    return waitingList;
}

void CarWashRepo::clearWaitingList() {
    vector<Car> emptyVector;
    waitingList = emptyVector;
}

void CarWashRepo::addToWaitingList(const Car &car) {
    waitingList.push_back(car);
}
