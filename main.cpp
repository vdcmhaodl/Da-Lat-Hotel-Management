#include "manager.h"
#include "customer.h"
#include "employee.h"
#include "room.h"
#include "hotel.h"
#include <vector>

int main()
{
    /*
    manager *boss = new manager("Thinh", "0983824401", "thinh@gmail.com", 24127171, 2000, "Leader");
    employee* e1 = new employee("Hoang", "0982312332", "hoang@gmail.com", 24127070, 1000, "Dev");
    customer* c1 = new customer("Nhan", "091111111", "nhan@gmail.com", 24128080);
    employee* e2 = new employee("Hao", "09123123312", "Tien@gmail.com", 24128080, 3000, "Data Analyst");

    boss->add(e1);
    boss->add(c1);
    boss->add(e2);

    boss->updateEmployeePosition(24128080,"Tester");
    boss->remove(24127070);

    boss->viewEmployeeList();
    boss->showInfo();
    delete boss;
    delete e1;
    delete c1;
    delete e2;
    */

    /*
    room Phong2("01222", 150);
    room Phong3("123", 300);
    Phong2.book("Hoang", {2,8,2025}, {11,9,2025});
    Phong2.book("Tien", {21,2,3231}, {25,23,2012});
    Phong2.cancel("Hoang");
    Phong2.displayBookingQueue();
    Phong2.displayInfo();
    */

    // hotel with 2 floors
    hotel A(2);


    /*
    std::vector<room>floor_1_type_2 = {room ("1002", 150), room ("1012", 350), room ("1013", 400)};
    std::vector<room>floor_2_type_3 = {room ("2003", 100), room ("2013", 400), room ("2023", 600)};

    floor_ floor_1(1,floor_1_type_2,2);
    floor_ floor_2(2,floor_2_type_3,3);

    floor_2.addRoom(2);

    A.addFloor(floor_1);
    A.addFloor(floor_2);
    */  

    A.addRoom(0,1);
    A.addRoom(1,2);

    A.displayAllRooms();
    return 0;
}

/* Run the build.bat to before run the project */