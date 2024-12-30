
#ifndef LAB6_CARS_V1_REPO_H
#define LAB6_CARS_V1_REPO_H

#include "../Domain/car.h"
#include <utility>
#include <ostream>
#include <vector>
#include <fstream>
#include <map>

using std::map;
using std::vector;


class RepoAbstract {
public:

    virtual void add(const Car &car) =0;

    virtual void remove(const string& registration)  = 0;

    virtual void modify(const string& registartion,
                    const string& new_reg,
                    const string& new_pr,
                    const string& new_model,
                    const string& new_type)  = 0;

    virtual const vector<Car>& get_all_cars() const = 0;

    virtual ~RepoAbstract() = default;


};

class CarRepo: public RepoAbstract{
protected:
    vector<Car> allCars;
public:
    CarRepo() = default;
    CarRepo(const CarRepo& ot) = delete;

    void add(const Car& car) override;

    void remove(const string& registration) override;

    void modify(const string& registartion,
                const string& new_reg,
                const string& new_pr,
                const string& new_model,
                const string& new_type) override;

    const vector<Car>& get_all_cars() const override;

    vector<Car>::iterator carIterator(const string& registration);

};

class FileRepo : public CarRepo{
private:
    string filename;
public:
    void loadFromFile();
    void writeToFile();

    FileRepo(string filename): CarRepo(), filename{std::move(filename)} {
        loadFromFile();
    }

    void add(const Car &car) override;

    void remove(const string& registration) override;

    void modify(const string& registartion,
                const string& new_reg,
                const string& new_pr,
                const string& new_model,
                const string& new_type) override;
};

class RepoRandomError : public RepoAbstract{
private:
    double prob = 11;
    map <int,Car> carsMap;
    vector<Car> carsList;
public:
    RepoRandomError() = default;

    ~RepoRandomError() override = default;

    void add(const Car &o) override;

    void remove(const string& registration) override;

    void set_prob(int new_p){
        prob = new_p;
    }

    void modify(const string& registration,
                const string& new_reg,
                const string& new_pr,
                const string& new_model,
                const string& new_type) override;

    const vector<Car>& get_all_cars() const override {
        return carsList;
    }
};

#endif //LAB6_CARS_V1_REPO_H
