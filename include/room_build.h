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
    virtual ~roomBuilder() = default;
};