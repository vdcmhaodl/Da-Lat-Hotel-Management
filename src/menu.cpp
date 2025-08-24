#include "menu.h"

void managerMenu(HotelManagementSystem& system) {
  int choice;
  do {
    std::cout << "\n--- Manager Menu ---\n";
    std::cout << "1. Hire Employee\n";
    std::cout << "2. Fire Employee\n";
    std::cout << "3. View Employees\n";
    std::cout << "4. Add Room\n";
    std::cout << "5. Remove Room\n";
    std::cout << "6. Show Rooms\n";
    std::cout << "7. Add customers\n";
    std::cout << "8. Show Customers\n";
    std::cout << "0. Logout\n";
    std::cin >> choice;

    switch (choice) {
      case 1: {
        std::string name, phone, email;
        int id;
        double salary;
        std::cout << "Enter employee name: ";

        std::cin.ignore();
        std::getline(std::cin, name);

        std::cout << "Phone: ";
        std::cin >> phone;
        std::cout << "Email: ";
        std::cin >> email;
        std::cout << "ID: ";
        std::cin >> id;
        std::cout << "Salary: ";
        std::cin >> salary;

        employee* newEmp = new employee(name, phone, email, id, salary);
        system.hireEmployee(newEmp);
        break;
      }
      case 2: {
        int id;
        std::cout << "Enter employee ID to fire: ";
        std::cin >> id;
        system.fireEmployee(id);
        break;
      }
      case 3:
        system.viewEmployees();
        break;
      case 4: {
        int flr, type;
        std::cout << "Enter floor and room type: ";
        std::cin >> flr >> type;
        system.addRoom(flr, type);
        break;
      }
      case 5:
        system.removeRoom();
        break;
      case 6: {
        system.showRoom();
        break;
      }
      case 7: {
        system.addCustomer();
        break;
      }
      case 8:
        system.showCustomer();
        break;
    }
  } while (choice != 0);
}

void employeeMenu(HotelManagementSystem& system, int empId) {
  int choice;
  do {
    std::cout << "\n--- Employee Menu ---\n";
    std::cout << "1. Lock Room\n";
    std::cout << "2. Unlock Room\n";
    std::cout << "3. Give Discount to Customer\n";
    std::cout << "0. Logout\n";
    std::cin >> choice;

    switch (choice) {
      case 1: {
        std::string roomId;
        std::cout << "Enter room ID to lock: ";
        std::cin >> roomId;
        system.getManager().lockRoom(system.getHotel(), roomId);
        break;
      }
      case 2: {
        std::string roomId;
        std::cout << "Enter room ID to unlock: ";
        std::cin >> roomId;
        system.getManager().unlockRoom(system.getHotel(), roomId);
        break;
      }
      case 3: {
        int custId, percent;
        std::cout << "Enter customer ID: ";
        std::cin >> custId;
        customer* c = system.findCustomer(custId);
        if (!c) {
          std::cout << "NOT FOUND CUSTOMER\n";
          break;
        }
        std::cout << "Enter discount %: ";
        std::cin >> percent;
        system.getManager().giveDiscount(*c, percent);
        break;
      }
    }
  } while (choice != 0);
}

void customerMenu(HotelManagementSystem& system, customer* cust) {
  int choice;
  do {
    std::cout << "\n--- Customer Menu ---\n";
    std::cout << "1. Book Room\n";
    std::cout << "2. Cancel Room\n";
    std::cout << "3. View Bill\n";
    std::cout << "4. Pay Bill\n";
    std::cout << "5. View My Booked Rooms\n";  // New option
    std::cout << "0. Logout\n";
    std::cin >> choice;

    switch (choice) {
      case 1:
        system.bookRoom(cust);
        break;
      case 2: {
        std::string roomID;
        std::cout << "Enter room ID to cancel: ";
        std::cin >> roomID;
        cust->cancelRoom(roomID);
        break;
      }
      case 3:
        cust->showBill();
        break;
      case 4: {
        std::string roomID;
        std::cout << "Enter room ID to pay bill: ";
        std::cin >> roomID;
        cust->payBill(roomID);
        break;
      }
      case 5:
        cust->viewBookedRooms();
        break;
    }
  } while (choice != 0);
}
