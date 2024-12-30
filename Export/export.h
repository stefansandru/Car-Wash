

#ifndef LAB8_CARS_V1_EXPORT_H
#define LAB8_CARS_V1_EXPORT_H

#include <string>
#include "../Domain/car.h"

using std::vector;

// Writs in filePath the given list of carsMap
// format: Comma Separated Values
// Throws ExportException if it cannot create the file
void exportToCVS(const std::string& filePath, const vector<Car>& cars);

// Writs in filePath the given list of carsMap
// format: HTML
// Throws ExportException if it cannot create the file
void exportToHTML(const std::string& filePath, const vector<Car>& cars);

void test_export();
#endif //LAB8_CARS_V1_EXPORT_H
