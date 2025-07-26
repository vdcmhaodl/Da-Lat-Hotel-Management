#include "room_director.h"
#include "room_concrete.h"

#include <iostream>

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
}

room_basic* room_director::getResult(roomBuilder* builder) { return builder->getResult(); }

void room_item_director::construct(room_itemBuilder* builder)
{
    builder->buildTowel();
    builder->buildSandals();
    builder->buildHair_dryer();
    builder->buildSleep_dress();
}

room_item* room_item_director::getResult(room_itemBuilder* builder) { return builder->getResult(); }

// int main()
// {
//     room_director temp;
//     doubleNormalRoom concrete;
//     temp.construct(&concrete);
//     std::cout << temp.getResult(&concrete) << '\n';
//     room_basic* room = temp.getResult(&concrete);
//     std::cout << room << ' ' << temp.getResult(&concrete) << '\n';
//     std::cout << "Single beds: " << room->getSingle_beds() << '\n';
//     std::cout << "Large beds: " << room->getLarge_beds() << '\n';
//     std::cout << "Bathrooms: " << room->getBathrooms() << '\n';
//     std::cout << "Bath: " << room->getBath() << '\n';
//     std::cout << "TV: " << room->getTV() << '\n';
//     std::cout << "Balcol: " << room->getBalcol() << '\n';
//     std::cout << "Loving chair: " << room->getLoving_chair() << '\n';
//     std::cout << "Fridge: " << room->getFridge() << '\n';
//     std::cout << "Rooms: " << room->getRooms() << '\n';
//     delete room;
//     return 0;
// }