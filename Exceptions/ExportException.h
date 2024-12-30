
#ifndef CARWASH_EXPORTEXCEPTION_H
#define CARWASH_EXPORTEXCEPTION_H

#include <exception>
#include <string>
#include <utility>

class ExportException : public std::exception {
private:
    std::string message;
public:
    explicit ExportException(std::string  msg) : message(std::move(msg)) {}

    [[nodiscard]] const char* what() const noexcept override {
        return message.c_str();
    }
};

#endif //CARWASH_EXPORTEXCEPTION_H
