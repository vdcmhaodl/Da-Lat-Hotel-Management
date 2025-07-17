#include "person.h"

bool person::bookRoom(room &a, date checkin, date checkout)
{
    return a.book(name, checkin, checkout);
}

bool person::cancelRoom(room &a)
{
    return a.cancel(name);
}

void person::viewRoomInfo(std::string id, hotel& h)
{
    room temp = h.findRoomByNumber(id);
    temp.displayInfo();
}

void person::viewAvailableRoom(hotel& h)
{
    h.displayAllAvailableRooms();
}
bool person::editPersonalInfo(std::string name, std::string phone, std::string email)
{
    if(name != "") this->name = name;
    if(this->checkPhone(phone)) this->phone = phone;
    if(this->checkEmail(email)) this->email = email;
}