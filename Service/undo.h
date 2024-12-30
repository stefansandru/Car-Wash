

#ifndef LAB8_CARS_V1_UNDO_H
#define LAB8_CARS_V1_UNDO_H

#include <utility>
#include "../Domain/car.h"
#include "../Repository/CarsRepository.h"

class UndoExceptions{
private:
    string message;

public:
    UndoExceptions(string msg): message{std::move(msg)} {}

    string get_message() const{
        return message;
    }
};

class UndoAction {
public:
    virtual void doUndo() = 0;
    virtual ~UndoAction()= default;
};

class UndoAdd : public UndoAction {
    RepoAbstract& repo;
    Car addedCar;
public:
    UndoAdd(RepoAbstract& rep, const  Car& car) : repo{rep}, addedCar{car} {}

    void doUndo() override {
        repo.remove(addedCar.get_registration());
    }
};

class UndoRemove : public UndoAction {
    RepoAbstract& repo;
    Car removedCar;
public:
    UndoRemove(RepoAbstract& rep, const  Car& car) : repo{rep}, removedCar{car} {}

    void doUndo() override {
        repo.add(removedCar);
    }
};

class UndoModify : public UndoAction {
    RepoAbstract& repo;
    Car modifiedCar;
    string currentCarRegistration;
public:
    UndoModify(RepoAbstract& rep, string current, const Car& car) :
    repo{rep},
    currentCarRegistration{std::move(current)},
    modifiedCar{car} {}

    void doUndo() override {
        repo.modify(currentCarRegistration,
                    modifiedCar.get_registration(),
                    modifiedCar.get_producer(),
                    modifiedCar.get_model(),
                    modifiedCar.get_type());
    }
};

#endif //LAB8_CARS_V1_UNDO_H
