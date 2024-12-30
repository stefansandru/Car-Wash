#include "../Repository/CarsRepository.h"
#include "../Exceptions/RepoException.h"
#include <gtest/gtest.h>

/// 97% lines covered because of the Random Probability Error.
/// This is because the RepoRandomError methods include a random chance of throwing an exception,
/// which is not consistently controlled in the test cases.
// Tests for CarRepo
TEST(CarRepoTests, AddCar) {
    CarRepo repo;
    Car car("ABC123", "Toyota", "Corolla", "Sedan");
    repo.add(car);
    EXPECT_EQ(repo.get_all_cars().size(), 1);
    EXPECT_THROW(repo.add(car), RepoException);
}

TEST(CarRepoTests, RemoveCar) {
    CarRepo repo;
    Car car1("ABC123", "Toyota", "Corolla", "Sedan");
    Car car2("DEF456", "Ford", "Mustang", "SUV");

    repo.add(car1);
    repo.add(car2);
    repo.remove("ABC123");

    EXPECT_EQ(repo.get_all_cars().size(), 1);
    EXPECT_EQ(repo.get_all_cars()[0].get_registration(), "DEF456");
    EXPECT_THROW(repo.remove("GHI789"), RepoException);

    repo.remove("DEF456");
    EXPECT_TRUE(repo.get_all_cars().empty());
}

TEST(CarRepoTests, ModifyCar) {
    CarRepo repo;
    Car car1("ABC123", "Tesla", "Model S", "Electric");
    repo.add(car1);

    repo.modify("ABC123", "DEF456", "Ford", "Mustang", "SUV");
    EXPECT_EQ(repo.get_all_cars()[0].get_registration(), "DEF456");
    EXPECT_EQ(repo.get_all_cars()[0].get_producer(), "Ford");
    EXPECT_EQ(repo.get_all_cars()[0].get_model(), "Mustang");
    EXPECT_EQ(repo.get_all_cars()[0].get_type(), "SUV");

    EXPECT_THROW(repo.modify("GHI789", "JKL012", "BMW", "X5", "Diesel"), RepoException);
}

// Tests for FileRepo
TEST(FileRepoTests, LoadFromFile) {
    std::ofstream ofs("../Tests/test.csv", std::ofstream::out | std::ofstream::trunc);
    ofs << "ABC123,Toyota,Corolla,Sedan\n";
    ofs.close();

    // the constructor is calling loadFromFile
    FileRepo fileRepo("../Tests/test.csv");

    ASSERT_EQ(fileRepo.get_all_cars().size(), 1);
    EXPECT_EQ(fileRepo.get_all_cars()[0].get_registration(), "ABC123");
}

TEST(FileRepoTests, LoadFromFileRepoException) {
    try {
        FileRepo fileRepo("../not/existent/path.csv");
    } catch (RepoException& e) {
        EXPECT_STREQ(e.what(), "Error reading file: ../not/existent/path.csv");
    }
}

TEST(FileRepoTests, AddCar) {
    std::ofstream ofs("../Tests/test.csv", std::ofstream::out | std::ofstream::trunc);
    ofs.close();

    FileRepo fileRepo("../Tests/test.csv");
    Car car("ABC123", "Toyota", "Camry", "Sedan");
    fileRepo.add(car);

    ASSERT_EQ(fileRepo.get_all_cars().size(), 1);
    EXPECT_EQ(fileRepo.get_all_cars()[0].get_registration(), "ABC123");
}

TEST(FileRepoTests, RemoveCar) {
    std::ofstream ofs("../Tests/test.csv", std::ofstream::out | std::ofstream::trunc);
    ofs << "ABC123,Toyota,Corolla,Sedan\n";
    ofs << "DEF456,Ford,Mustang,SUV\n";
    ofs.close();

    FileRepo fileRepo("../Tests/test.csv");
    fileRepo.remove("ABC123");

    ASSERT_EQ(fileRepo.get_all_cars().size(), 1);
    EXPECT_EQ(fileRepo.get_all_cars()[0].get_registration(), "DEF456");
}

TEST(FileRepoTests, ModifyCar) {
    std::ofstream ofs("../Tests/test.csv", std::ofstream::out | std::ofstream::trunc);
    ofs << "ABC123,Toyota,Corolla,Sedan\n";
    ofs.close();

    FileRepo fileRepo("../Tests/test.csv");
    fileRepo.modify("ABC123", "DEF456", "Ford", "Mustang", "SUV");

    ASSERT_EQ(fileRepo.get_all_cars().size(), 1);
    EXPECT_EQ(fileRepo.get_all_cars()[0].get_registration(), "DEF456");
    EXPECT_EQ(fileRepo.get_all_cars()[0].get_producer(), "Ford");
    EXPECT_EQ(fileRepo.get_all_cars()[0].get_model(), "Mustang");
    EXPECT_EQ(fileRepo.get_all_cars()[0].get_type(), "SUV");
}

// Tests for RepoRandomError
TEST(RepoRandomErrorTests, RandomAdd) {
    RepoRandomError repo;
    repo.set_prob(0); // Ensure no exception
    Car car("ABC123", "Toyota", "Corolla", "Sedan");
    repo.add(car);

    EXPECT_EQ(repo.get_all_cars().size(), 1);
    EXPECT_EQ(repo.get_all_cars()[0].get_registration(), "ABC123");
}

TEST(RepoRandomErrorTests, RandomRemove) {
    RepoRandomError repo;
    repo.set_prob(0); // Ensure no exception
    Car car("ABC123", "Toyota", "Corolla", "Sedan");
    repo.add(car);

    repo.remove("ABC123");

    EXPECT_TRUE(repo.get_all_cars().empty());
}

TEST(RepoRandomErrorTests, RandomRemoveNonExistentCar) {
    try {
        RepoRandomError repo;
        repo.set_prob(0); // Ensure no exception
        Car car("ABC123", "Toyota", "Corolla", "Sedan");
        repo.add(car);

        repo.remove("not-existent");

    } catch (RepoException& e) {
        EXPECT_STREQ(e.what(), "Non-existent car!\n");
    }
}

TEST(RepoRandomErrorTests, RandomModify) {
    RepoRandomError repo;
    repo.set_prob(0); // Ensure no exception
    Car car("ABC123", "Toyota", "Corolla", "Sedan");
    repo.add(car);

    repo.modify("ABC123", "DEF456", "Ford", "Mustang", "SUV");

    EXPECT_EQ(repo.get_all_cars()[0].get_registration(), "DEF456");
    EXPECT_EQ(repo.get_all_cars()[0].get_producer(), "Ford");
    EXPECT_EQ(repo.get_all_cars()[0].get_model(), "Mustang");
    EXPECT_EQ(repo.get_all_cars()[0].get_type(), "SUV");
}

TEST(RepoRandomErrorTests, RandomModifyNonExistentCar) {
    try {
        RepoRandomError repo;
        repo.set_prob(0); // Ensure no exception
        Car car("ABC123", "Toyota", "Corolla", "Sedan");
        repo.add(car);

        repo.modify("not-existent", "DEF456", "Ford", "Mustang", "SUV");

    } catch (RepoException& e) {
        EXPECT_STREQ(e.what(), "Non-existent car!\n");
    }
}