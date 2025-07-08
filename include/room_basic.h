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
    double price;
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
    void setPrice(double price);
    void setView(view v);
};

