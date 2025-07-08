#pragma once

#include <string>
#include <room_basic.h>
struct date
{
    int date;
    int month;
    int year;
};
class room
{
private:
    int roomNumber;
    int roomType;
    int capacity;
    double pricePerNight;
    bool isOccupied;
    std::string current_guest;
    date checkinDate;
    date checkoutDate;

public:
    room();
    room(int roomNumber, int roomType, int capacity, double pricePerNight);
    void checkIn();
    void checkOut();
    bool isAvailable();
    void addService(std::string name, double cost);
    double calculateStayCost();
    void displayInfo();
};