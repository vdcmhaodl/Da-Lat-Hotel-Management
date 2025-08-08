#include "hotel.h"

hotel::hotel() { 
    this->num_floor = 0;
}

hotel::hotel(int flr)
{
    this->num_floor = flr;
    for(int i = 0; i < flr; i++)
    {
        floor_ temp(i);
        this->Floor.push_back(temp);
    }
}

void hotel::updatePrice(int roomType, double price)
{
    for(int i = 0; i < num_floor; i++)
        Floor[i].updateRoomPrice(roomType, price);
}
    
void hotel::addRoom(int flr, int type)
{
    Floor[flr].addRoom(type);
}

void hotel::removeRoom(int flr, std::string ID)
{
    Floor[flr].removeRoom(ID);
}
    
void hotel::addFloor()
{
    num_floor++;
    floor_ temp(num_floor);
    Floor.push_back(temp);
}

void hotel::addFloor(floor_ fl)
{ 
    num_floor++;
    Floor.push_back(fl);
}

room& hotel::findRoomByNumber(std::string ID)
{
    int flr = (ID[0] - '0') * 10 + (ID[1] - '0');
    return Floor[flr].findRoomByNumber(ID);
}
    
std::vector<floor_> hotel::findRoomsByType(int type)
{
    std::vector<floor_> ans;
    for(int i = 0; i < num_floor; i++)
    {
        floor_ temp(i, Floor[i].findRoomsByType(type), type);    
        ans.push_back(temp);
    }
    return ans;
}
    
void hotel::displayAllFloorRooms(int flr)
{
    std::cout << "Floor " << flr << ":\n";
    Floor[flr].displayAllFloorRooms();
}

void hotel::displayAllRooms()
{
    for(int i = 0; i < num_floor; i++)
    {
        std::cout << "Floor " << i << ":\n";
        Floor[i].displayAllFloorRooms();
    }
}

std::vector<room> hotel::sortFloorRoomByPrice(int flr, bool ascend)
{
    return Floor[flr].sortRoomsByPrice(ascend);
}

std::vector<floor_> hotel::sortRoomsByPrice(bool ascend)
{
    std::vector<floor_> ans;
    for(int i = 0; i < num_floor; i++)
    {
        floor_ temp(i, Floor[i].sortRoomsByPrice(ascend), 0);
        ans.push_back(temp);
    }
    return ans;
}

std::vector<floor_> hotel::sortAvailableRoomByPrice(bool ascend)
{
    std::vector<floor_> ans;
    for(int i = 0; i < num_floor; i++)
    {
        floor_ temp(i, Floor[i].sortAvailableRoomsByPrice(ascend), 0);
        ans.push_back(temp);
    }
    return ans;
}

std::vector<floor_> hotel::findAvailableRooms()
{
    std::vector<floor_> ans;
    for(int i = 0; i < Floor.size(); i++)
    {
        floor_ temp(i, Floor[i].findAvailableRooms(), 0);
        ans.push_back(temp);
    }
    return ans;
}

void hotel::displayAllAvailableRooms()
{
    std::vector<floor_> availableRooms = this->findAvailableRooms();
    for(int i = 0; i < availableRooms.size(); i++)
    {
        std::cout << "Floor " << i << ": \n";
        availableRooms[i].displayAllFloorRooms();
    }
}

void hotel::addRoomToFloor(int flr, room& r) { 
    Floor[flr].addRoom(r);
}

std::vector<floor_> hotel::getFloors() const { 
    return Floor;
}