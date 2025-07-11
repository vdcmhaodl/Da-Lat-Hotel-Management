#pragma once

#include "room_build.h"

class room_director
{
public:
    void construct(roomBuilder* builder);
    room_basic* getResult(roomBuilder* builder);
};

class room_item_director
{
public:
    void construct(room_itemBuilder* builder);
    room_item* getResult(room_itemBuilder* builder);
};