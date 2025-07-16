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
    view v;
public:
    void setSingle_beds(int num);
    void setLarge_beds(int num);
    void setBathrooms(int num);
    void setBath(bool flag);
    void setTV(int num);
    void setBalcol(bool flag);
    void setLoving_chair(bool flag);
    void setFridge(bool flag);
    void setRooms(int num);
    void setView(view v);
    int room_basic::getSingle_beds();
    int room_basic::getLarge_beds();
    int room_basic::getBathrooms();
    bool room_basic::getBath();
    int room_basic::getTV();
    bool room_basic::getBalcol();
    bool room_basic::getLoving_chair();
    bool room_basic::getFridge();
    int room_basic::getRooms();
    view room_basic::getView();
};

class room_item
{
private:
    int towel;
    int sleep_dress;
    int sandals;
    int hair_dryer;
public:
    void setTowel(int num);
    void setHair_dryer(int num);
    void setSleep_dress(int num);
    void setSandals(int num);
    int getTowel();
    int getHair_dryer();
    int getSleep_dress();
    int getSandals();
};