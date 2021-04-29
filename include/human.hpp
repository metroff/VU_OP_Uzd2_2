#pragma once

#include <string>

/// @brief Human klasė sauganti žmogaus vardą ir pavardę.
class Human {
    protected:
        std::string firstName;
        std::string lastName;

    public:
        Human(const std::string &_firstName = "", const std::string &_lastName = "") : firstName(_firstName), lastName(_lastName) {};

        virtual std::string getFirstName() const = 0;
        virtual std::string getLastName() const = 0;

        void setFirstName(const std::string &firstName) {
            this->firstName = firstName;
        }

        void setLastName(const std::string &lastName) {
            this->lastName = lastName;
        }
};