#include "manager.h"
#include "customer.h"
#include "employee.h"
#include "room.h"
#include "hotel.h"
#include <vector>

#include "HotelManagement.h"
#include "menu.h"

int main()
{
    HotelManagementSystem system(5, "ManagerJohn", "555-1234", "manager@hotel.com", 1, 60000, "Manager");
    std::cout << "Create system successfully\n";
    system.loadSystemState();

    // Add some initial data
    // system.addRoom(1, 1);
    // system.addRoom(2, 2);

    int choice;
    do {
        std::cout << "\n===== Welcome to Hotel Management System =====\n";
        std::cout << "1. Login as Manager\n";
        std::cout << "2. Login as Employee\n";
        std::cout << "3. Login as Customer\n";
        std::cout << "0. Exit\n";
        std::cout << "Enter choice: ";
        std::cin >> choice;
        
        switch (choice) {
            case 1:
                managerMenu(system);
                break;
            case 2: {
                int id;
                std::cout << "Enter your employee ID: ";
                std::cin >> id;
                if (system.isEmployee(id))
                    employeeMenu(system, id);
                else
                    std::cout << "Employee not found.\n";
                break;
            }
            case 3: {
                int id;
                std::cout << "Enter your customer ID: ";
                std::cin >> id;
                customer* cust = system.getCustomerById(id);
                if (cust != nullptr)
                    customerMenu(system, cust);
                else
                    std::cout << "Customer not found.\n";
                break;
            }
        };

    } while (choice != 0);
    
    system.saveSystemState();
    return 0;
}

/* Run the build.bat to before run the project */