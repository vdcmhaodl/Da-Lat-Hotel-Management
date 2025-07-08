#pragma once
#include <string>
#include <string.h>

enum class Role
{
    Customer,
    Employee,
    Manager
};

class person
{
private:
    bool checkPhone();
    bool checkEmail();
protected:
    std::string name;
    std::string phone;
    std::string email;
    int id;
    std::string role;
public:
    bool bookRoom();
    bool cancelRoom();
    void viewRoomInfo(int id);
    void viewAvailableRoom();
    bool editPersonalInfo();
};