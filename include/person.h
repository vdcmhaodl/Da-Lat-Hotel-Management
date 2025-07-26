#pragma once
#include "person_interface.h"
#include <string>
#include <string.h>

// FROM information of room.h
enum status
{
    in,
    out
};

struct service
{
    std::string name;
    double cost;
};

struct date
{
    int day;
    int month;
    int year;
};

struct date_satus
{
    date Date;
    status Status;
    std::string guest;
};

// END HERE

enum class Role
{
    None,
    Customer,
    Employee,
    Manager
};

class person: public IPerson
{
protected:
    // basic information
    std::string name;
    std::string phone;
    std::string email;  
    int id;
    Role role;
public:

    // basic constructors 
    person(); 
    virtual ~person() = default;
    person(std::string name, std::string phone, std::string email, int id, Role role);
    person& operator=(const person &other);

    // getters
    std::string getPhone();
    std::string getEmail(); 
    int getID() const override;

    // setters
    void setName(std::string name);
    bool setPhone(std::string phone);
    bool setEmail(std::string email);
    void setID(int ID);
    void setRole(Role role);

    void showInfo() override;
    std::string getPosition() override;
    std::string getName() override;

    // Wait for class Room to complete
    // void viewRoomInfo(std::string id, hotel& h);
    // void viewAvailableRoom(hotel& h);
    // bool editPersonalInfo(std::string name, std::string phone, std::string email);
    // bool bookRoom(std::string id, hotel& h, date checkin, date checkout);
    // bool cancelRoom(room &a);
};