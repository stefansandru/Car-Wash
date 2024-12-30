
#ifndef LAB6_CARS_V1_SERVICE_H
#define LAB6_CARS_V1_SERVICE_H

#include "../Repository/CarsRepository.h"
#include "../Validators/validator.h"
#include "../Domain/CarTypeCountDTO.h"
#include "../Repository//CarWashRepository.h"
#include "../Service/undo.h"
#include "../Repository/CarsRepository.h"
#include <string>
#include <map>
using std::unique_ptr;

using std::vector;
using std::string;

class Service{
private:
    RepoAbstract& CarsRepo;
    vector<unique_ptr<UndoAction>> undoActions;
    CarWashRepo CarWashRepo;

public:
    Service(RepoAbstract& repo): CarsRepo{repo} {}

    Service(const Service& ot) = delete;

    void add_srv(string reg, string pr, string model, string type);

    void delete_car_srv(const string& registration);

    void modify_car_srv(const string& registartion,
                                const string& new_reg,
                                const string& new_pr,
                                const string& new_model,
                                const string& new_type);

    const vector<Car>& get_all_cars_srv() noexcept;

    Car search_car(const string& registration);

    // Function for general sort
    // returns sorted list
    vector<Car> general_sort(bool (*sort_function)(const Car&, const Car&));

    // Function for sort
    // returns sorted list
    vector<Car> registration_sort();

    // Function for sortint by prodcer and model
    // returns sorted list
    vector<Car> producer_and_model_sort();

    // Function for sortint by type
    // returns sorted list
    vector<Car> type_sort();

    // retuns filtered list of carsMap
    vector<Car> filterCars(const string& registration,
                           const string& producer,
                           const string& model,
                           const string& type);
//    vector<Car> filterProducer(const string& prod);
//    vector<Car> filterModel(const string& prod, const string& model);
//    vector<Car> filterType(const string& type);

    std::map<string,CarTypeCountDTO> typeAndNumberOfCars();

    void undo_srv();

    // returns the number of carsMap in wating list
    size_t sizeOfWaitingList();

    const vector<Car>& getWaitingList() const;

    // Clear all carsMap to the car wash waiting list
    size_t clearWaitingList_srv();

    // Add a car to the car wash waiting list
    size_t addToWaitingList_srv(const string& registration);

    // Add a number of existing carsMap to the car wash waiting list
    size_t randomAddToWaitingList_srv(size_t cars_number);

    bool isInCarWashList(string registration) const;
};



#endif //LAB6_CARS_V1_SERVICE_H
