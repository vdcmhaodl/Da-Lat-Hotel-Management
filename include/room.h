#pragma once

#include <string>
#include <vector>
#include <iostream>
#include <queue>

#include "room_basic.h"
#include "room_director.h"
#include "room_cityview.h"
#include "room_natureview.h"
#include "room_item.h"

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

class room
{
private:
    std::string ID;
    room_basic* roomType;
    std::string typeName;
    room_item* item;
    double pricePerNight;
    bool isOccupied;
    std::string current_guest;
    std::vector<date_satus> book_history;
    std::vector<date_satus> booking_queue;
    std::vector<service> Service;
public:
    room(std::string roomNumber, double pricePerNight);
    room(room &a);
    room& operator=(const room& a);
    std::string getID();
    bool book(std::string guest_name, date checkin_date, date checkout_date);
    bool cancel(std::string guest_name);
    void updatePrice(double price);
    void checkIn(date checkin, std::string cur_guest);
    void checkOut(date checkout);
    bool isAvailable();
    double checkPrice();
    void addService(std::string name, double cost);
    double calculateStayCost();
    void displayInfo();
    ~room();
};