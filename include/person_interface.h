#pragma once 
#include <iostream>


// COMPOSITE PATTERN

class IPerson
{ 
public: 
    virtual ~IPerson() = default; 
    virtual void showInfo() = 0;
    virtual std::string getName() = 0;
    //virtual std::string getPosition() = 0;
    virtual int getID() const = 0;
};