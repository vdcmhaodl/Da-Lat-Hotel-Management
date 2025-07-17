#include "person.h"

person::person()
{
    name = "";
    phone = "";
    email = "";
    id = 0;
    role = Role::None;
}

person::person(std::string name, std::string phone, std::string email, int id, Role role)
{
    this->name = name;
    this->phone = phone;
    this->email = email;
    this->id = id;
    this->role = role;
}

person& person::operator=(const person &other)
{
    this->name = other.name;
    this->phone = other.phone;
    this->email = other.email;
    this->id = other.id;
    this->role = other.role;
    return *this;
}