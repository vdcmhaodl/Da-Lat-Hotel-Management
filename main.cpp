#include "manager.h"
#include "customer.h"
#include "employee.h"

int main()
{
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
}

/*
COMMAND TO BUILD main.cpp

g++ main.cpp ./src/custormer_check.cpp ./src/custormer_function.cpp ./src/custormer_getset.cpp ./src/custormer_init.cpp ./src/employee_function.cpp ./src/employee_init.cpp ./src/manager_function.cpp ./src/manager_init.cpp ./src/person_check.cpp ./src/person_getset.cpp ./src/person_init.cpp ./src/person_function.cpp -Iinclude -o main.exe

*/