#pragma once
#include "HotelManagement.h"
#include <iostream>

void managerMenu(HotelManagementSystem& system);

void employeeMenu(HotelManagementSystem& system, int empId);

void customerMenu(HotelManagementSystem& system, customer* cust);
