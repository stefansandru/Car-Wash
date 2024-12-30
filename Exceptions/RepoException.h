

#ifndef CARWASH_REPOEXCEPTION_H
#define CARWASH_REPOEXCEPTION_H

#include <exception>
#include <string>


class RepoException : public std::exception {
private:
    std::string message;
public:
    explicit RepoException(std::string msg) : message(std::move(msg)) {}

    [[nodiscard]] const char* what() const noexcept override {
        return message.c_str();
    }
};

#endif //CARWASH_REPOEXCEPTION_H
