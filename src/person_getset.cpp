#include "person.h"

// for getters
std::string person::getPhone() { return this->phone; }
std::string person::getEmail() { return this->email; }
int person::getID() const { return this->id; }

// for setters
void person::setName(std::string name) { this->name = name; }
void person::setID(int ID) { this->id = ID; }

bool person::setPhone(std::string phone)
{
    this->phone = phone;
    return 1;
}
bool person::setEmail(std::string email)
{
    this->email = email;
    return 1;
}

std::string person::getName() { 
    return name;
}

void person::setGender(bool gender)
{
    this->gender = gender;
}
    
void person::setPassword(std::string password)
{
    this->password = password;
}