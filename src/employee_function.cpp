#include "employee.h"

/*
 void employee::viewRoomBookingHistory(room &a) {
    // This function displays the booking history of the room
    std::cout << "Booking history for room: " << a.getID() << std::endl;
    a.displayBookingHistory();
 }
 */
void employee::updatePosition(const std::string &newPosition)
{
   position = newPosition;
}

void employee::showInfo()
{
   std::cout << "Employee "<< id << "\n";
   std::cout << "Name: " << name << "\n"; 
   std::cout << "Phone: " << phone << "\n";
   std::cout << "Email: " << email << "\n";
   std::cout << "Salary: " << salary << "\n";
   std::cout << "Position: " << position << "\n"; 
}

std::string employee::getName()
{
   return name;
}

std::string employee::getPosition()
{
   return position;
}

int employee::getID() const { 
    return id; 
}