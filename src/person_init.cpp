#include "person.h"

person::person()
{
    name = "";
    phone = "";
    email = "";
    id = 0;
}

person::person(std::string name, std::string phone, std::string email, int id)
{
    this->name = name;
    this->phone = phone;
    this->email = email;
    this->id = id;
}

person& person::operator=(const person &other)
{
    this->name = other.name;
    this->phone = other.phone;
    this->email = other.email;
    this->id = other.id;
    return *this;
}