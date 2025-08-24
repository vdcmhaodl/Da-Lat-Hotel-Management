#pragma once
#include "person_interface.h"
#include <string>
#include <string.h>
#include <room.h>

// FROM information of room.h

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
    bool gender;
    std::string password;
    int id;
   // Role role;
public:

    // basic constructors 
    person(); 
    virtual ~person() = default;
    person(std::string name, std::string phone, std::string email, int id, bool gender);
    person& operator=(const person &other);

    // getters
    std::string getPhone();
    std::string getEmail(); 
    std::string getGender();
    std::string getPassword();
    int getID() const override;

    // setters
    void setName(std::string name);
    bool setPhone(std::string phone);
    bool setEmail(std::string email);
    void setGender(bool gender);
    void setPassword(std::string password); 
    void setID(int ID);

    void showInfo() override;
    //std::string getPosition() override;
    std::string getName() override;
};