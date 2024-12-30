
#include "validator.h"
#include "../Exceptions/ValidateException.h"
#include <sstream>
#include <cassert>

void Validator::validate(const Car &car) {
    vector<string> messages;
    int exist_nr = 0;
    int exist_letter = 0;
    for(char c : car.get_registration()){
        if(isdigit(c))
            exist_nr = 1;
        if(isalpha(c))
            exist_letter = 1;
    }
    if(exist_nr == 0 || exist_letter == 0)
        messages.emplace_back("Invalid registration!"
                           " Must contain at least one letter and at least one number.");
    if(car.get_producer().empty())
        messages.emplace_back("Enter a producer.");
    if(car.get_model().empty())
        messages.emplace_back("Enter a model.");
    if(car.get_type().empty())
        messages.emplace_back("Enter a type.");
    if(!messages.empty())
        throw ValidateException(messages);
}
