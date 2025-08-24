#include "employee.h"

employee::employee() : person() {
    salary = 0.0;
    position = "Unknown";
}

employee::employee(const std::string name, const std::string phone,
                   const std::string email, const int id, const bool gender,
                   double salary)
    : person(name, phone, email, id, gender) {
    this->salary = salary;
    this->position = "Unknown";
}
