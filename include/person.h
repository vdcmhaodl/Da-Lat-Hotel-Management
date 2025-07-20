#pragma once
#include <string>
#include <string.h>

#include "hotel.h"

enum class Role
{
    None,
    Customer,
    Employee,
    Manager
};

class person
{
private:
    bool checkPhone(std::string phone);
    bool checkEmail(std::string email);
protected:
    std::string name;
    std::string phone;
    std::string email;
    int id;
    Role role;
public:
    person();
    person(std::string name, std::string phone, std::string email, int id, Role role);
    person& operator=(const person &other);
    std::string getName();
    std::string getPhone();
    std::string getEmail();
    int getID();
    Role getRole();
    void setName(std::string name);
    bool setPhone(std::string phone);
    bool setEmail(std::string email);
    void setID(int ID);
    void setRole(Role role);
    void viewRoomInfo(std::string id, hotel& h);
    void viewAvailableRoom(hotel& h);
    bool editPersonalInfo(std::string name, std::string phone, std::string email);
    bool bookRoom(std::string id, hotel& h, date checkin, date checkout);
    bool cancelRoom(room &a);
};