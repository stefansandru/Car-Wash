
#ifndef LAB6_CARS_V1_VALIDATOR_H
#define LAB6_CARS_V1_VALIDATOR_H

#include "../Domain/car.h"
#include <vector>

using std::string;
using std::vector;
using std::ostream;

class Validator {
public:
    static void validate(const Car& car);
};

void test_validator();

#endif //LAB6_CARS_V1_VALIDATOR_H
