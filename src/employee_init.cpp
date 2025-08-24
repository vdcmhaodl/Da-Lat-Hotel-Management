#include "employee.h"

employee::employee(const std::string name, const std::string phone,
                   const std::string email, const int id, const bool gender,
                   double salary) : person(name, phone, email, id, gender), salary(salary), position("Unknown") {

}
