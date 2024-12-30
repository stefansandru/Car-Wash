#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "../Service/service.h"
#include "../Exceptions/RepoException.h"
#include "../Exceptions/ValidateException.h"

using ::testing::ReturnRef;
using ::testing::Return;
using ::testing::Throw;

class MockRepo : public RepoAbstract {
private:
    std::vector<Car> cars;

public:
    MOCK_METHOD(void, add, (const Car& car), (override));
    MOCK_METHOD(void, remove, (const std::string& registration), (override));
    MOCK_METHOD(void, modify, (const std::string& registration,
            const std::string& new_reg,
            const std::string& new_pr,
            const std::string& new_model,
            const std::string& new_type), (override));
   MOCK_METHOD(const std::vector<Car>&, get_all_cars, (), (const, override));

    void add_car(const Car& car) {
        cars.push_back(car);
    }

    void remove_car(const std::string& registration) {
        cars.erase(std::remove_if(cars.begin(), cars.end(), [&registration](const Car& car) {
            return car.get_registration() == registration;
        }), cars.end());
    }

    const std::vector<Car>& get_all_cars_internal() const {
        return cars;
    }

    void modify_car(const std::string& registration,
            const std::string& new_reg,
            const std::string& new_pr,
            const std::string& new_model,
            const std::string& new_type) {
        for (auto& car : cars) {
            if (car.get_registration() == registration) {
                car.set_registration(new_reg);
                car.set_producer(new_pr);
                car.set_model(new_model);
                car.set_type(new_type);
                break;
            }
        }
    }
};

class ServiceTest : public ::testing::Test {
protected:
    MockRepo mockRepo;
    Service service{mockRepo};

    void SetUp() override {
        ON_CALL(mockRepo, add(testing::_)).WillByDefault(testing::Invoke(&mockRepo, &MockRepo::add_car));
        ON_CALL(mockRepo, remove(testing::_)).WillByDefault(testing::Invoke(&mockRepo, &MockRepo::remove_car));
        ON_CALL(mockRepo, modify(testing::_, testing::_, testing::_, testing::_, testing::_)).WillByDefault(testing::Invoke(&mockRepo, &MockRepo::modify_car));
        ON_CALL(mockRepo, get_all_cars()).WillByDefault(testing::Invoke(&mockRepo, &MockRepo::get_all_cars_internal));

        mockRepo.add_car(Car("ABC123", "Toyota", "Corolla", "Sedan"));
        mockRepo.add_car(Car("DEF456", "Ford", "Focus", "Coupe"));
        mockRepo.add_car(Car("GHI789", "BMW", "X5", "SUV"));
        mockRepo.add_car(Car("JKL012", "Toyota", "Yaris", "Sedan"));
    }
};

TEST_F(ServiceTest, AddCarSuccess) {
    service.add_srv("test1", "Toyota", "Corolla", "Sedan");

    vector<Car> allCars = mockRepo.get_all_cars_internal();
    ASSERT_EQ(allCars.size(), 5);
    EXPECT_EQ(allCars[4].get_registration(), "test1");
}

TEST_F(ServiceTest, RemoveCarSuccess) {
    service.delete_car_srv("ABC123");

    EXPECT_EQ(mockRepo.get_all_cars_internal().size(), 3);
    vector<Car> allCars = mockRepo.get_all_cars_internal();
    bool found = std::find_if(allCars.begin(), allCars.end(), [](const Car& car) {
        return car.get_registration() == "ABC123";
    }) != allCars.end();
    EXPECT_FALSE(found);
}


TEST_F(ServiceTest, ModifyCarSuccess) {
    service.modify_car_srv("ABC123", "XYZ789", "Honda", "Civic", "Coupe");

    EXPECT_EQ(mockRepo.get_all_cars_internal()[0].get_registration(), "XYZ789");
    EXPECT_EQ(mockRepo.get_all_cars_internal()[0].get_producer(), "Honda");
    EXPECT_EQ(mockRepo.get_all_cars_internal()[0].get_model(), "Civic");
    EXPECT_EQ(mockRepo.get_all_cars_internal()[0].get_type(), "Coupe");
}


TEST_F(ServiceTest, GetAllCars) {
    EXPECT_CALL(mockRepo, get_all_cars()).WillOnce(ReturnRef(mockRepo.get_all_cars_internal()));
    auto result = service.get_all_cars_srv();
    ASSERT_EQ(result.size(), 4);
    EXPECT_EQ(result[0].get_registration(), "ABC123");
    EXPECT_EQ(result[1].get_registration(), "DEF456");
    EXPECT_EQ(result[2].get_registration(), "GHI789");
    EXPECT_EQ(result[3].get_registration(), "JKL012");
}

TEST_F(ServiceTest, RegistrationSort) {
    EXPECT_CALL(mockRepo, get_all_cars()).WillOnce(ReturnRef(mockRepo.get_all_cars_internal()));
    auto result = service.registration_sort();
    ASSERT_EQ(result.size(), 4);
    EXPECT_EQ(result[0].get_registration(), "ABC123");
    EXPECT_EQ(result[1].get_registration(), "DEF456");
    EXPECT_EQ(result[2].get_registration(), "GHI789");
    EXPECT_EQ(result[3].get_registration(), "JKL012");
}

TEST_F(ServiceTest, ProducerAndModelSort) {
    auto result = service.producer_and_model_sort();

    ASSERT_EQ(result.size(), 4);
    EXPECT_EQ(result[0].get_registration(), "GHI789");
    EXPECT_EQ(result[1].get_registration(), "DEF456");
    EXPECT_EQ(result[2].get_registration(), "ABC123");
    EXPECT_EQ(result[3].get_registration(), "JKL012");
}

TEST_F(ServiceTest, TypeSort) {
    auto result = service.type_sort();

    ASSERT_EQ(result.size(), 4);
    EXPECT_EQ(result[0].get_registration(), "DEF456");
    EXPECT_EQ(result[1].get_registration(), "ABC123");
    EXPECT_EQ(result[2].get_registration(), "JKL012");
    EXPECT_EQ(result[3].get_registration(), "GHI789");
}

TEST_F(ServiceTest, FilterCars) {
    auto result = service.filterCars("ABC", "Toyota", "Corolla", "Sedan");

    ASSERT_EQ(result.size(), 1);
    EXPECT_EQ(result[0].get_registration(), "ABC123");
}

TEST_F(ServiceTest, SearchCarSuccess) {
    Car car = service.search_car("ABC123");

    EXPECT_EQ(car.get_registration(), "ABC123");
}

TEST_F(ServiceTest, SearchCarNotFound) {
    Car car = service.search_car("XYZ789");

    EXPECT_TRUE(car.get_registration().empty());
}

TEST_F(ServiceTest, UndoAddSuccess) {
    service.add_srv("test1", "Toyota", "Corolla", "Sedan");
    EXPECT_EQ(mockRepo.get_all_cars_internal().size(), 5);

    service.undo_srv();
    EXPECT_EQ(mockRepo.get_all_cars_internal().size(), 4);
}

TEST_F(ServiceTest, UndoRemoveSuccess) {
    service.delete_car_srv("ABC123");
    EXPECT_EQ(mockRepo.get_all_cars_internal().size(), 3);

    service.undo_srv();
    EXPECT_EQ(mockRepo.get_all_cars_internal().size(), 4);
}

TEST_F(ServiceTest, UndoModifySuccess) {
    service.modify_car_srv("ABC123", "XYZ789", "Honda", "Civic", "Coupe");
    EXPECT_EQ(mockRepo.get_all_cars_internal()[0].get_registration(), "XYZ789");
    EXPECT_EQ(mockRepo.get_all_cars_internal()[0].get_producer(), "Honda");
    EXPECT_EQ(mockRepo.get_all_cars_internal()[0].get_model(), "Civic");
    EXPECT_EQ(mockRepo.get_all_cars_internal()[0].get_type(), "Coupe");

    service.undo_srv();
    EXPECT_EQ(mockRepo.get_all_cars_internal()[0].get_registration(), "ABC123");
    EXPECT_EQ(mockRepo.get_all_cars_internal()[0].get_producer(), "Toyota");
    EXPECT_EQ(mockRepo.get_all_cars_internal()[0].get_model(), "Corolla");
    EXPECT_EQ(mockRepo.get_all_cars_internal()[0].get_type(), "Sedan");
}

TEST_F(ServiceTest, UndoThrowsWhenNoActions) {
    try {
        service.undo_srv();
    } catch (const UndoExceptions& e) {
        EXPECT_EQ(e.get_message(), "\nNo more undo operations!\n");
    }

}

TEST_F(ServiceTest, TypeAndNumberOfCars) {
    auto result = service.typeAndNumberOfCars();
    EXPECT_EQ(result["Sedan"].get_nr(), 2);
    EXPECT_EQ(result["SUV"].get_nr(), 1);
    EXPECT_EQ(result["Coupe"].get_nr(), 1);
}

TEST_F(ServiceTest, AddToWaitingListSuccess) {
    service.addToWaitingList_srv("ABC123");
    EXPECT_EQ(service.sizeOfWaitingList(), 1);
    EXPECT_EQ(service.getWaitingList()[0].get_registration(), "ABC123");
}

TEST_F(ServiceTest, AddToWaitingListNonExistingCar) {
    try {
        service.addToWaitingList_srv("ABC123");
    } catch (const RepoException& e) {
        EXPECT_STREQ(e.what(), "Non-existent car!\n");
    }
}

TEST_F(ServiceTest, RandomAddToWaitingList) {
    service.randomAddToWaitingList_srv(3);
    service.randomAddToWaitingList_srv(4);

    EXPECT_EQ(service.sizeOfWaitingList(), 4);
}

TEST_F(ServiceTest, ClearWaitingList) {
    service.addToWaitingList_srv("ABC123");
    service.clearWaitingList_srv();
    EXPECT_EQ(service.clearWaitingList_srv(), 0);
}