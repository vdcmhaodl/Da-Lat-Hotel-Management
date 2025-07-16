#include "room_director.h"

void room_director::construct(roomBuilder* builder)
{
    builder->buildSingle_beds();
    builder->buildLarge_beds();
    builder->buildBathrooms();
    builder->buildBath();
    builder->buildTV();
    builder->buildBalcol();
    builder->buildLoving_chair();
    builder->buildFridge();
    builder->buildRooms();
    builder->buildView();
}

room_basic* room_director::getResult(roomBuilder* builder)
{
    return builder->getResult();
}

void room_item_director::construct(room_itemBuilder* builder)
{
    builder->buildTowel();
    builder->buildSandals();
    builder->buildHair_dryer();
    builder->buildSleep_dress();
}

room_item* room_item_director::getResult(room_itemBuilder* builder) 
{ 
    return builder->getResult(); 
}