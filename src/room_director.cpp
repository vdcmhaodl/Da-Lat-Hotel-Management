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
    builder->buildPrice();
    builder->buildView();
}