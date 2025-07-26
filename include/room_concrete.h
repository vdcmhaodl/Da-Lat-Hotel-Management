#pragma once
#include "room_build.h"

class singleNormalRoom : public roomBuilder
{
private:
    room_basic* room;
public:
    singleNormalRoom();
    void buildSingle_beds() override;
    void buildLarge_beds() override;
    void buildBathrooms() override;
    void buildBath() override;
    void buildTV() override;
    void buildBalcol() override;
    void buildLoving_chair() override;
    void buildFridge() override;
    void buildRooms() override;
    room_basic* getResult() override;
    ~singleNormalRoom();
};

class doubleNormalRoom : public roomBuilder
{
private:
    room_basic* room;
public:
    doubleNormalRoom();
    void buildSingle_beds() override;
    void buildLarge_beds() override;
    void buildBathrooms() override;
    void buildBath() override;
    void buildTV() override;
    void buildBalcol() override;
    void buildLoving_chair() override;
    void buildFridge() override;
    void buildRooms() override;
    room_basic* getResult() override;
    ~doubleNormalRoom();
};

class singleVipRoom : public roomBuilder
{
private:
    room_basic* room;
public:
    singleVipRoom();
    void buildSingle_beds() override;
    void buildLarge_beds() override;
    void buildBathrooms() override;
    void buildBath() override;
    void buildTV() override;
    void buildBalcol() override;
    void buildLoving_chair() override;
    void buildFridge() override;
    void buildRooms() override;
    room_basic* getResult() override;
    ~singleVipRoom();
};

class doubleVipRoom : public roomBuilder
{
private:
    room_basic* room;
public:
    doubleVipRoom();
    void buildSingle_beds() override;
    void buildLarge_beds() override;
    void buildBathrooms() override;
    void buildBath() override;
    void buildTV() override;
    void buildBalcol() override;
    void buildLoving_chair() override;
    void buildFridge() override;
    void buildRooms() override;
    room_basic* getResult() override;
    ~doubleVipRoom();
};