#pragma once

#include "person.h"

class employee : public person
{
    friend class manager; 
protected: 
    std::string position;
    double salary;
    void updatePosition(const std::string& newPosition); // Only Manager can update position (the derived class)
public:
    employee();
    employee(const std::string name, const std::string phone,
        const std::string email,
        const int id, double salary, const std::string position);
    virtual ~employee() = default;

    void showInfo() override;
    std::string getName() override;
    std::string getPosition() override;
    int getID() const override;
    // Wait for class Room to complete
    // void generateInvoice(room &a);
    // void viewRoomBookingHistory(room &a);
    // void viewRoomBookingQueue(room &a);
};  


