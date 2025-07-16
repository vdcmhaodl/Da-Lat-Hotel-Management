#include "hotel.h"

hotel::hotel(int flr)
{
    this->num_floor = flr;
    for(int i = 0; i < flr; i++)
    {
        floor temp(i);
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
    floor temp(num_floor);
    Floor.push_back(temp);
}

room hotel::findRoomByNumber(std::string ID)
{
    int flr = (ID[0] - '0') * 10 + (ID[1] - '0');
    return Floor[flr].findRoomByNumber(ID);
}
    
std::vector<floor> hotel::findRoomsByType(int type)
{
    std::vector<floor> ans;
    for(int i = 0; i < num_floor; i++)
    {
        floor temp(i, Floor[i].findRoomsByType(type), type);    
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
        std::cout << "Floor " << i + 1 << ":\n";
        Floor[i].displayAllFloorRooms();
    }
}

std::vector<room> hotel::sortFloorRoomByPrice(int flr, bool ascend)
{
    return Floor[flr].sortRoomsByPrice(ascend);
}

std::vector<floor> hotel::sortRoomsByPrice(bool ascend)
{
    std::vector<floor> ans;
    for(int i = 0; i < num_floor; i++)
    {
        floor temp(i, Floor[i].sortRoomsByPrice(ascend), 0);
        ans.push_back(temp);
    }
    return ans;
}

std::vector<floor> hotel::sortAvailableRoomByPrice(bool ascend)
{
    std::vector<floor> ans;
    for(int i = 0; i < num_floor; i++)
    {
        floor temp(i, Floor[i].sortAvailableRoomsByPrice(ascend), 0);
        ans.push_back(temp);
    }
    return ans;
}