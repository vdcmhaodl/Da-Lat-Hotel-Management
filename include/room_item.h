#pragma once
#include "room_build.h"

class singleRoomItem : public room_itemBuilder
{
room_item* item;
public:
    singleRoomItem();
    void buildTowel() override;
    void buildHair_dryer() override;
    void buildSleep_dress() override;
    void buildSandals() override;
    room_item* getResult() override;
};

class doubleRoomItem : public room_itemBuilder
{
room_item* item;
public:
    doubleRoomItem();
    void buildTowel() override;
    void buildHair_dryer() override;
    void buildSleep_dress() override;
    void buildSandals() override;
    room_item* getResult() override;
};