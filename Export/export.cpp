
#include "export.h"
#include  "../Exceptions/ExportException.h"
#include <fstream>
#include <string>
#include <assert.h>

#include "../Service/service.h"

void exportToCVS(const std::string& filePath, const vector<Car>& cars) {
    std::ofstream out(filePath, std::ios::trunc);
    if (!out.is_open()) {
        throw ExportException("Unable to open file: " + filePath);
    }
//    out << "Registration, Producer, Model, Type" << std::endl;
    if (cars.size() == 0) {
        out << "Car list is empty. No data to export.";
    }else {
        for (const auto& c : cars) {
            out << c.get_registration() << ", ";
            out << c.get_producer() << ", ";
            out << c.get_model() << ", ";
            out << c.get_type() << std::endl;
        }
    }
    out.close();
}

void exportToHTML(const std::string& filePath, const vector<Car>& cars) {
    std::ofstream out(filePath, std::ios::trunc);
    if (!out.is_open()) {
        throw ExportException("Unable to open file: " + filePath);
    }
    out << R"(<!DOCTYPE html>
    <html lang="en">
    <head>
    <meta charset="UTF-8">
        <title>CarWashRepo</title>
    </head>)";
    out << "<body>" << std::endl;
    out << R"(<table border="1" style="width:100%">)" << std::endl;

    // Table header
    out << "<tr>" << std::endl;
    out << "<th>Registration</th>" << std::endl;
    out << "<th>Producer</th>" << std::endl;
    out << "<th>Model</th>" << std::endl;
    out << "<th>Type</th>" << std::endl;
    out << "</tr>" << std::endl;

    for (const auto& car : cars) {
        out << "<tr>" << std::endl;
        out << "<td>" << car.get_registration() << "</td>" << std::endl;
        out << "<td>" << car.get_producer() << "</td>" << std::endl;
        out << "<td>" << car.get_model() << "</td>" << std::endl;
        out << "<td>" << car.get_type() << "</td>" << std::endl;
        out << "</tr>" << std::endl;
    }
    out << "</table>" << std::endl;
    out << "</body></html>" << std::endl;
    out.close();
}
