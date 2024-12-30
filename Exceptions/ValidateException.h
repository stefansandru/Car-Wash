

#ifndef CARWASH_VALIDATEEXCEPTION_H
#define CARWASH_VALIDATEEXCEPTION_H

#include <vector>
#include <string>
#include <ostream>
#include <sstream>


using std::vector;
using std::string;
using std::ostream;

class ValidateException : public std::exception {
    string message;

public:
    explicit ValidateException(const std::vector<std::string>& messages) {
        for (const auto& msg : messages) {
            message += msg + "\n";
        }
    };

    [[nodiscard]] const char* what() const noexcept override {
        return message.c_str();
    }
};

#endif //CARWASH_VALIDATEEXCEPTION_H
