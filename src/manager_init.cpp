#include "manager.h"

manager::manager() : employee(){}
manager::manager(const std::string name, const std::string phone,
                 const std::string email, const int id, double salary)
    : employee(name, phone, email, id, salary) {}
