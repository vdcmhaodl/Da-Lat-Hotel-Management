#include "room.h"

void room::checkIn(date checkin, std::string cur_guest)
{
    this->current_guest = cur_guest;
    this->isOccupied = 1;

    date_satus temp;
    temp.Date = checkin;
    temp.Status = in;
    temp.guest = cur_guest;
    this->book_history.push_back(temp);
}
void room::checkOut(date checkout)
{
    this->isOccupied = 0;

    date_satus temp;
    temp.Date = checkout;
    temp.Status = out;
    temp.guest = this->current_guest;
    this->book_history.push_back(temp);
    this->Service.clear();
    this->current_guest = "";
}

bool room::isAvailable()
{
    return this->isOccupied;
}

void room::addService(std::string name, double cost)
{
    service temp;
    temp.name = name;
    temp.cost = cost;
    this->Service.push_back(temp);
}

double room::calculateStayCost()
{
    int cost = 0;
    for(int i = 0; i < this->Service.size(); i++)
        cost += this->Service[i].cost;
    return cost;
}

void room::displayInfo()
{
    std::cout << "Room number: " << this->roomNumber << '\n';
    std::cout << "Room type: " << this->typeName << '\n';
    std::cout << "Room status: " << ((this->isAvailable()) ? "Available" : "Not available") << '\n';
}