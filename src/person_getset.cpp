#include "person.h"

std::string person::getName() { return this->name; }
std::string person::getPhone() { return this->phone; }
std::string person::getEmail() { return this->email; }
int person::getID() { return this->id; }
Role person::getRole() { return this->role; }

void person::setName(std::string name) { this->name = name; }
void person::setID(int ID) { this->id = ID; }
void person::setRole(Role role) { this->role = role; }
bool person::setPhone(std::string phone)
{
    if(!this->checkPhone(phone)) return 0;
    this->phone = phone;
    return 1;
}
bool person::setEmail(std::string email)
{
    if(!this->checkEmail(email)) return 0;
    this->email = email;
    return 1;
}