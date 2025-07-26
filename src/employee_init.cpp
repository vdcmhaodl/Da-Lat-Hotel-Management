#include "employee.h"

employee::employee() : person() {
    role = Role::Employee;
    salary = 0.0;
    position = "Unknown";
}

employee::employee(const std::string name, const std::string phone,
                   const std::string email, const int id,
                   double salary, const std::string position)
    : person(name, phone, email, id, Role::Employee) {
    this->salary = salary;
    this->position = position;
}
