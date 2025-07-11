#pragma once

#include "room_basic.h"

class roomBuilder : public room_basic
{
public:
    virtual void buildSingle_beds() = 0;
    virtual void buildLarge_beds() = 0;
    virtual void buildBathrooms() = 0;
    virtual void buildBath() = 0;
    virtual void buildTV() = 0;
    virtual void buildBalcol() = 0;
    virtual void buildLoving_chair() = 0;
    virtual void buildFridge() = 0;
    virtual void buildRooms() = 0;
    virtual void buildPrice() = 0;
    virtual void buildView() = 0;
    virtual room_basic* getResult() = 0;
    virtual ~roomBuilder() = default;
};

class room_itemBuilder : public room_item
{
public:
    virtual void buildTowel() = 0;
    virtual void buildHair_dryer() = 0;
    virtual void buildSleep_dress() = 0;
    virtual void buildSandals() = 0;
    virtual room_item* getResult() = 0;
    virtual ~room_itemBuilder() = default;
};