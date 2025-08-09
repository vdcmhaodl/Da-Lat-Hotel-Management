#pragma once

#include <string>

enum view
{
    city,
    nature
};

class room_basic
{
private:
    int single_beds;
    int large_beds;
    int bathrooms;
    bool bath;
    int TV;
    bool balcol;
    bool loving_chair;
    bool fridge;   
    int rooms;
public:
    room_basic();
    room_basic(room_basic& a);
    void setSingle_beds(int num);
    void setLarge_beds(int num);
    void setBathrooms(int num);
    void setBath(bool flag);
    void setTV(int num);
    void setBalcol(bool flag);
    void setLoving_chair(bool flag);
    void setFridge(bool flag);
    void setRooms(int num);
    int getSingle_beds();
    int getLarge_beds();
    int getBathrooms();
    bool getBath();
    int getTV();
    bool getBalcol();
    bool getLoving_chair();
    bool getFridge();
    int getRooms();
};

class room_item
{
private:
    int towel;
    int sleep_dress;
    int sandals;
    int hair_dryer;
public:
    room_item();
    room_item(room_item& a);
    void setTowel(int num);
    void setHair_dryer(int num);
    void setSleep_dress(int num);
    void setSandals(int num);
    int getTowel();
    int getHair_dryer();
    int getSleep_dress();
    int getSandals();
};