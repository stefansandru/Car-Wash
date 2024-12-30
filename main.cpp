#include <QApplication>
#include <gtest/gtest.h>
#include "Repository/CarsRepository.h"
#include "Service/service.h"
#include "GUI/MainGUI.h"
#include "Exceptions/RepoException.h"

void add_some_cars(RepoAbstract& repo) {
    try {
        repo.add(Car("ABC123", "Tesla", "Model S", CarType::Sedan));
    } catch (RepoException &e) {
    }
    try {
        repo.add(Car("GHI789", "Tesla", "Model 3", CarType::Sedan));
    } catch (RepoException &e) {
    }
    try {
        repo.add(Car("34i", "BMW", "X5", CarType::SUV));
    } catch (RepoException &e) {
    }
    try {
        repo.add(Car("u4", "BMW", "X6", CarType::SUV));
    } catch (RepoException &e) {
    }
    try {
        repo.add(Car("34iub", "Audi", "A5", CarType::Coupe));
    } catch (RepoException &e) {
    }
    try {
        repo.add(Car("JKL012", "Ford", "Mustang", CarType::Coupe));
    } catch (RepoException &e) {
    }
    try {
        repo.add(Car("MNO345", "Ford", "Focus", CarType::Sedan));
    } catch (RepoException &e) {
    }
    try {
        repo.add(Car("PQR678", "Audi", "Q7", CarType::SUV));
    } catch (RepoException &e) {
    }
    // Adding 12 more cars
    try {
        repo.add(Car("RST901", "Tesla", "Model X", CarType::SUV));
    } catch (RepoException &e) {
    }
    try {
        repo.add(Car("UVW234", "Tesla", "Model Y", CarType::SUV));
    } catch (RepoException &e) {
    }
    try {
        repo.add(Car("XYZ567", "BMW", "3 Series", CarType::Sedan));
    } catch (RepoException &e) {
    }
    try {
        repo.add(Car("ABC890", "BMW", "5 Series", CarType::Sedan));
    } catch (RepoException &e) {
    }
    try {
        repo.add(Car("DEF123", "Audi", "A4", CarType::Sedan));
    } catch (RepoException &e) {
    }
    try {
        repo.add(Car("GHI456", "Audi", "A6", CarType::Sedan));
    } catch (RepoException &e) {
    }
    try {
        repo.add(Car("JKL789", "Ford", "Explorer", CarType::SUV));
    } catch (RepoException &e) {
    }
    try {
        repo.add(Car("PQR345", "Tesla", "Roadster", CarType::Coupe));
    } catch (RepoException &e) {
    }
    try {
        repo.add(Car("STU678", "BMW", "X3", CarType::SUV));
    } catch (RepoException &e) {
    }
    try {
        repo.add(Car("VWX901", "Audi", "Q5", CarType::SUV));
    } catch (RepoException &e) {
    }
    try {
        repo.add(Car("YZA234", "Ford", "Edge", CarType::SUV));
    } catch (RepoException &e) {
    }
}

int main(int argc , char* argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    printf("%s", reinterpret_cast<const char *>(RUN_ALL_TESTS()));

    QApplication a(argc, argv);
     CarRepo CarsRepo;
//    FileRepo ("../DataStorage/Cars.csv");
    // RepoRandomError CarsRepo;
    add_some_cars(CarsRepo);
    CarWashRepo carWashList;
    Service srv{CarsRepo};
    MainGUI gui{ srv };
    gui.show();
    return QApplication::exec();
}

