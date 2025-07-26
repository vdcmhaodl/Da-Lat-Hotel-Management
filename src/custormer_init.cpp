#include "customer.h"
#include <vector>

customer::customer() : person()
{
    role = Role::Customer;
}

customer::customer(std::string name, std::string phone, std::string email, int id) : person(name, phone, email, id, Role::Customer)
{
    role = Role::Customer;
}

customer &customer::operator=(const customer &other)
{
    if (this != &other) {
        // Call the base class assignment operator
        // to copy the base class members of derived class
        person::operator=(other);

        // booking_history = other.booking_history;
    }
    return *this;
}

