
cmake_minimum_required(VERSION 3.28)
project(CarWash)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 17)

# Enable Qt5 Auto Features
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

# Specify the Qt5 installation path (update if necessary)
set(Qt5_DIR "/opt/homebrew/Cellar/qt@5/5.15.16/lib/cmake/Qt5")

# Find Qt5 components
find_package(Qt5 COMPONENTS
        Core
        Gui
        Widgets
        REQUIRED)

# Set the Google Test and Google Mock root
set(GTEST_ROOT "/opt/homebrew/opt/googletest")

# Locate GoogleTest and GoogleMock
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS} ${GTEST_ROOT}/include)
link_directories(${GTEST_ROOT}/lib)

# Add the executable and source files
add_executable(CarWash
        main.cpp
        Domain/car.cpp
        Domain/CarTypeCountDTO.h
        Exceptions/ExportException.h
        Exceptions/ValidateException.h
        Exceptions/RepoException.h
        Export/export.cpp
        GUI/CarsTableModel.h
        GUI/MainGUI.cpp
        GUI/CarWashGUI.cpp
        GUI/RaportGUI.cpp
        Repository/CarsRepository.cpp
        Repository/CarWashRepository.cpp
        Service/service.cpp
        Service/undo.h
        Validators/validator.cpp
        Tests/ServiceTest.cpp
        Tests/CarsRepositoryTest.cpp
)

# Link libraries to the executable
target_link_libraries(CarWash PRIVATE
        gmock
        gmock_main
        gtest
        gtest_main
        Qt5::Core
        Qt5::Gui
        Qt5::Widgets
)