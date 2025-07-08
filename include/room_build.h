#pragma once

#include "room_basic.h"

class roomBuilder : public basic_room
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

class singleCityNormalRoom : public roomBuilder
{
    basic_room* room;
public:
    void buildSingle_beds() override;
    void buildLarge_beds() override;
    void buildBathrooms() override;
    void buildBath() override;
    void buildTV() override;
    void buildBalcol() override;
    void buildLoving_chair() override;
    void buildFridge() override;
    void buildRooms() override;
    void buildPrice() override;
    void buildView() override;
};

class doubleCityNormalRoom : public roomBuilder
{
    basic_room* room;
public:
    void buildSingle_beds() override;
    void buildLarge_beds() override;
    void buildBathrooms() override;
    void buildBath() override;
    void buildTV() override;
    void buildBalcol() override;
    void buildLoving_chair() override;
    void buildFridge() override;
    void buildRooms() override;
    void buildPrice() override;
    void buildView() override;
};

class singleCityLargeRoom : public roomBuilder
{
    basic_room* room;
public:
    void buildSingle_beds() override;
    void buildLarge_beds() override;
    void buildBathrooms() override;
    void buildBath() override;
    void buildTV() override;
    void buildBalcol() override;
    void buildLoving_chair() override;
    void buildFridge() override;
    void buildRooms() override;
    void buildPrice() override;
    void buildView() override;
};

class doubleCityLargeRoom : public roomBuilder
{
    basic_room* room;
public:
    void buildSingle_beds() override;
    void buildLarge_beds() override;
    void buildBathrooms() override;
    void buildBath() override;
    void buildTV() override;
    void buildBalcol() override;
    void buildLoving_chair() override;
    void buildFridge() override;
    void buildRooms() override;
    void buildPrice() override;
    void buildView() override;
};