#include "manager.h"

manager::manager() : employee()
{
    position = "Manager"; // It could be another name (Ex: "Product manager") instead of "Manager", we can change it later
}
manager::manager(const std::string name, const std::string phone,
                 const std::string email, const int id, double salary, const std::string position)
    : employee(name, phone, email, id, salary, position) {
        this->role = Role::Manager; // Set the role to Manager
}