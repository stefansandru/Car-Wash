

#ifndef LAB8_CARS_V1_DTO_H
#define LAB8_CARS_V1_DTO_H

#include "car.h"

class CarTypeCountDTO{
private:
    int nr;
    string type;
public:
    CarTypeCountDTO() : nr{0}, type{"."} {};

    void increment(){
        nr++;
    }
    void init(const string &newType){
        nr = 1;
        type = newType;
    }
    int get_nr() const{
        return nr;
    }
};

#endif //LAB8_CARS_V1_DTO_H
