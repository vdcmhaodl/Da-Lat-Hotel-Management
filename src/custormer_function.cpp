#include "customer.h"

/*
void customer::viewBookingHistory(hotel &h)
{
    std::cout << "Booking History for " << getName() << ":\n";
    if (booking_history.empty())
    {
        std::cout << "No booking history available.\n";
        return;
    }

    for (auto &Room : booking_history)
    {
        Room.displayInfo();
    }
} */


/*
void customer::showBill(room &a)
{
    if (!checkBookingHistory(a.getID()))
    {
        std::cout << "Room not found in booking history.\n";
        return;
    }

    bill = a.calculateStayCost() * (1 - discount) * calculateNightStays();
    std::cout << "Bill for room " << a.getID() << ":\n";
    std::cout << "Total cost: " << bill << "\n";
    std::cout << "Checkout date: " << checkout.day << "/" << checkout.month << "/" << checkout.year << "\n";
}

bool customer::payBill(room &a)
{
    if (!checkBookingHistory(a.getID()))
    {
        std::cout << "Room not found in booking history.\n";
        return false;
    }

    std::cout << "Payment successful for room " << a.getID() << ".\n";

    // Remove the room from booking history after payment
    booking_history.erase(std::remove_if(booking_history.begin(), booking_history.end(),
                                         [&a](const room &r)
                                         { return r.getID() == a.getID(); }),
                          booking_history.end());
    // update the status of the room
    a.checkOut(checkout);

    return true;
}*/

void customer::showInfo() 
{   
   std::cout << "Custormer "<< id << "\n";
   std::cout << "Name: " << name << "\n"; 
   std::cout << "Phone: " << phone << "\n";
   std::cout << "Email: " << email << "\n";
   std::cout << "Current discount: " << discount << "\n";
   std::cout << "Date checkin" << checkin.day << "/" << checkin.month << "/" << checkout.year << std::endl;
}

std::string customer::getName() { 
    return name; 
}

std::string customer::getPosition() {
    return "No position available\n"; // Customers do not have any position in the hotel system !
}

