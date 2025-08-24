#include "menu.h"

<<<<<<< Updated upstream
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
=======
void managerMenu(HotelManagementSystem &system) {
  int choice;
  do {
    std::cout << "\n=== MANAGER MENU ===\n";
    std::cout << "1. Manage Employees\n";
    std::cout << "2. Manage Rooms\n";
    std::cout << "3. Manage Customers\n";
    std::cout << "4. View All Booking History\n";
    std::cout << "5. Generate Booking Report\n";
    std::cout << "6. View Booking Statistics\n";
    std::cout << "7. View Revenue Report\n";
    std::cout << "8. View Customer Booking History\n";
    std::cout << "9. Save System State\n";
    std::cout << "10. Load System State\n";
>>>>>>> Stashed changes
    std::cout << "0. Logout\n";
    std::cin >> choice;

    switch (choice) {
<<<<<<< Updated upstream
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
=======
      case 1:
        // Employee management submenu
        {
          int empChoice;
          std::cout << "\n=== EMPLOYEE MANAGEMENT ===\n";
          std::cout << "1. View Employees\n";
          std::cout << "2. Hire Employee\n";
          std::cout << "3. Fire Employee\n";
          std::cout << "Enter choice: ";
          std::cin >> empChoice;

          switch (empChoice) {
            case 1:
              system.viewEmployees();
              break;
            case 2: {
              system.hireEmployee();
              break;
            }
            case 3: {
              int empId;
              std::cout << "Enter employee ID to fire: ";
              std::cin >> empId;
              system.fireEmployee(empId);
            } break;
          }
        }
        break;

      case 2:
        // Room management
        {
          int roomChoice;
          std::cout << "\n=== ROOM MANAGEMENT ===\n";
          std::cout << "1. Add Room\n";
          std::cout << "2. Remove Room\n";
          std::cout << "3. View All Rooms\n";
          std::cout << "Enter choice: ";
          std::cin >> roomChoice;

          switch (roomChoice) {
            case 1: {
              int floor, type;
              std::cout << "Enter floor: ";
              std::cin >> floor;
              std::cout << "Enter room type (0-7): ";
              std::cin >> type;
              system.addRoom(floor, type);
            } break;
            case 2:
              system.removeRoom();
              break;
            case 3:
              system.showRoom();
              break;
          }
        }
        break;

      case 3:
        // Customer management
        {
          int custChoice;
          std::cout << "\n=== CUSTOMER MANAGEMENT ===\n";
          std::cout << "1. Add Customer\n";
          std::cout << "2. View All Customers\n";
          std::cout << "3. Remove Customer\n";
          std::cout << "Enter choice: ";
          std::cin >> custChoice;

          switch (custChoice) {
            case 1:
              system.addCustomer();
              break;
            case 2:
              system.showCustomer();
              break;
            case 3: {
              int custId;
              std::cout << "Enter customer ID to remove: ";
              std::cin >> custId;
              system.removeCustomer(custId);
            } break;
          }
        }
        break;

      case 4:
        // View all booking history
        system.getManager().viewAllBookingHistory(system.getAllCustomers());
        break;

      case 5:
        // Generate booking report
        system.getManager().generateBookingReport(system.getAllCustomers());
        break;

      case 6:
        // View booking statistics
        system.getManager().viewBookingStatistics(system.getAllCustomers());
        break;

      case 7:
        // View revenue report
        system.getManager().viewRevenueReport(system.getAllCustomers());
        break;

      case 8:
        // View specific customer booking history
        {
          int custId;
          std::cout << "Enter customer ID: ";
          std::cin >> custId;
          system.viewCustomerBookingHistory(custId);
        }
        break;

      case 9:
        system.saveSystemState();
        std::cout << "System state saved successfully!\n";
        break;

      case 10:
        system.loadSystemState();
        std::cout << "System state loaded successfully!\n";
        break;

      case 0:
        std::cout << "Logging out...\n";
        break;

      default:
        std::cout << "Invalid choice!\n";
    }
  } while (choice != 0);
}
void employeeMenu(HotelManagementSystem &system, int empId) {
  int choice;
  do {
    std::cout << "\n=== EMPLOYEE MENU ===\n";
    std::cout << "1. View Available Rooms\n";
    std::cout << "2. Book Room for Customer\n";
>>>>>>> Stashed changes
    std::cout << "3. Give Discount to Customer\n";
    std::cout << "0. Logout\n";
    std::cin >> choice;

    switch (choice) {
<<<<<<< Updated upstream
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
=======
      case 1:
        system.showRoom();
        break;

      case 2: {
        int custId;
        std::cout << "Enter customer ID: ";
        std::cin >> custId;
        customer *cust = system.findCustomer(custId);
        if (cust) {
          system.bookRoom(cust);
        } else {
          std::cout << "Customer not found!\n";
        }
      } break;

      case 3: {
        int custId, discount;
        std::cout << "Enter customer ID: ";
        std::cin >> custId;
        std::cout << "Enter discount percentage: ";
        std::cin >> discount;
        system.giveDiscountToCustomer(custId, discount);
      } break;

      case 4: {
        std::string roomId;
        int lockChoice;
        std::cout << "Enter room ID: ";
        std::cin >> roomId;
        std::cout << "1. Lock Room\n2. Unlock Room\nChoice: ";
        std::cin >> lockChoice;

        // Find employee to perform lock/unlock
        // This would need to be implemented in the system
        std::cout << "Room lock/unlock functionality\n";
      } break;

      case 5:
        // View hotel booking history (employee version)
        {
          // Get employee object and call viewHotelBookingHistory
          // This requires finding the employee by ID in the system
          std::cout << "=== HOTEL BOOKING HISTORY ===\n";
          system.viewAllBookingHistory();
        }
        break;

      case 6:
        // View specific customer booking history
        {
          int custId;
          std::cout << "Enter customer ID: ";
          std::cin >> custId;
          system.viewCustomerBookingHistory(custId);
        }
        break;

      case 7:
        // View room booking history
        {
          std::string roomId;
          std::cout << "Enter room ID: ";
          std::cin >> roomId;

          room *foundRoom = system.getHotel().findRoomByNumber(roomId);
          if (foundRoom) {
            std::cout << "\n=== ROOM BOOKING HISTORY ===\n";
            std::cout << "Room ID: " << roomId << std::endl;
            foundRoom->displayBookingHistory();
          } else {
            std::cout << "Room not found!\n";
          }
        }
        break;

      case 0:
        std::cout << "Logging out...\n";
        break;

      default:
        std::cout << "Invalid choice!\n";
>>>>>>> Stashed changes
    }
  } while (choice != 0);
}

<<<<<<< Updated upstream
void customerMenu(HotelManagementSystem& system, customer* cust) {
  int choice;
  do {
    std::cout << "\n--- Customer Menu ---\n";
    std::cout << "1. Book Room\n";
    std::cout << "2. Cancel Room\n";
    std::cout << "3. View Bill\n";
    std::cout << "4. Pay Bill\n";
    std::cout << "5. View My Booked Rooms\n";  // New option
=======
void customerMenu(HotelManagementSystem &system, customer *cust) {
  int choice;
  do {
    std::cout << "\n=== CUSTOMER MENU ===\n";
    std::cout << "Welcome, " << cust->getName() << "!\n";
    std::cout << "1. View Available Rooms\n";
    std::cout << "2. Book Room\n";
    std::cout << "3. Cancel Room\n";
    std::cout << "4. View My Booking History\n";
    std::cout << "5. View Current Bookings\n";
    std::cout << "6. Show Bill\n";
    std::cout << "7. Pay Bill\n";
    std::cout << "8. View Personal Information\n";
>>>>>>> Stashed changes
    std::cout << "0. Logout\n";
    std::cin >> choice;

    switch (choice) {
      case 1:
<<<<<<< Updated upstream
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
=======
        // View available rooms
        cust->viewAvailableRooms(system.getHotel());
        break;

      case 2:
        // Book room
        {
          std::string roomId;
          int checkinDay, checkinMonth, checkinYear;
          int checkoutDay, checkoutMonth, checkoutYear;

          std::cout << "Enter room ID: ";
          std::cin >> roomId;

          std::cout << "Enter check-in date (day month year): ";
          std::cin >> checkinDay >> checkinMonth >> checkinYear;

          std::cout << "Enter check-out date (day month year): ";
          std::cin >> checkoutDay >> checkoutMonth >> checkoutYear;

          date checkin = {checkinDay, checkinMonth, checkinYear};
          date checkout = {checkoutDay, checkoutMonth, checkoutYear};

          if (cust->bookRoom(system.getHotel(), roomId, checkin, checkout)) {
            std::cout << "Room booked successfully!\n";
          } else {
            std::cout << "Failed to book room!\n";
          }
        }
        break;

      case 3:
        // Cancel room
        {
          std::string roomId;
          std::cout << "Enter room ID to cancel: ";
          std::cin >> roomId;

          if (cust->cancelRoom(roomId)) {
            std::cout << "Room cancelled successfully!\n";
          } else {
            std::cout << "Failed to cancel room!\n";
          }
        }
        break;

      case 4:
        // View booking history
        cust->viewMyBookingHistory();
        break;

      case 5:
        // View current bookings
        cust->showCurrentBookings();
        break;

      case 6:
        // Show bill
        cust->showBill();
        break;

      case 7:
        // Pay bill
        {
          std::string roomId;
          std::cout << "Enter room ID to pay for: ";
          std::cin >> roomId;

          if (cust->payBill(roomId)) {
            std::cout << "Bill paid successfully!\n";
          } else {
            std::cout << "Failed to pay bill!\n";
          }
        }
        break;

      case 8:
        // View personal information
        cust->showInfo();
        break;

      case 0:
        std::cout << "Logging out...\n";
        break;

      default:
        std::cout << "Invalid choice!\n";
>>>>>>> Stashed changes
    }
  } while (choice != 0);
}
