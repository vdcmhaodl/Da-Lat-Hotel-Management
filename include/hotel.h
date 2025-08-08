#pragma once

#include <vector>
#include <algorithm>

#include "room.h"
// #include "init_price_type.h"

class floor_
{
private:
    std::vector <room> rooms[9];
    int flr;
    int Type[9] = {};
    int price[9];
    int num_rooms;
public:
    floor_();
    floor_(int flr);
    floor_(int flr, std::vector<room> rooms, int type);
    int getNumRooms();
    void updateRoomPrice(int roomType, double price);
    void addRoom(int type);
    //void addRoomDirectly(const room& r);
    void addRoom(room& r);
    bool removeRoom(std::string ID);
    room& findRoomByNumber(std::string ID);
    std::vector<room> findAvailableRooms();
    std::vector<room> findRoomsByType(int type);
    std::vector<room> findAllRooms();
    void displayAllFloorRooms();
    std::vector<room> sortRoomsByPrice(bool ascend);
    std::vector<room> sortAvailableRoomsByPrice(bool ascend);
};

class hotel
{
private:
    int num_floor = 0;
    std::vector<floor_> Floor;
public:
    hotel();
    hotel(int flr);
    room& findRoomByNumber(std::string ID);
    std::vector<floor_> findRoomsByType(int type);
    std::vector<floor_> findAvailableRooms();
    std::vector<floor_> getFloors() const;
    void updatePrice(int roomType, double price);
    void addRoom(int flr, int type);
    void addRoomToFloor(int flr, room& r);
    void removeRoom(int flr, std::string ID);
    void addFloor();
    void addFloor(floor_ fl);
    void displayAllFloorRooms(int flr);
    void displayAllRooms();
    void displayAllAvailableRooms();
    std::vector<room> sortFloorRoomByPrice(int flr, bool ascend);
    std::vector<floor_> sortRoomsByPrice(bool ascend);
    std::vector<floor_> sortAvailableRoomByPrice(bool ascend);
};

bool cmp(room a, room b);