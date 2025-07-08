#pragma once

#include "room_build.h"

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