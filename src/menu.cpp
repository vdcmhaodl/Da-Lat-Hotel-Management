#include "menu.h"

void managerMenu(HotelManagementSystem &system)
{
  int choice;
  do
  {
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
    std::cout << "0. Logout\n";
    std::cout << "Enter your choice: ";
    std::cin >> choice;

    switch (choice)
    {
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

        switch (empChoice)
        {
        case 1:
          system.viewEmployees();
          break;
        case 2:
        {
          system.hireEmployee();
          break;
        }
        case 3:
        {
          int empId;
          std::cout << "Enter employee ID to fire: ";
          std::cin >> empId;
          system.fireEmployee(empId);
        }
        break;
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

        switch (roomChoice)
        {
        case 1:
        {
          int floor, type;
          std::cout << "Enter floor: ";
          std::cin >> floor;
          std::cout << "Enter room type (0-7): ";
          std::cin >> type;
          system.addRoom(floor, type);
        }
        break;
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

        switch (custChoice)
        {
        case 1:
          system.addCustomer();
          break;
        case 2:
          system.showCustomer();
          break;
        case 3:
        {
          int custId;
          std::cout << "Enter customer ID to remove: ";
          std::cin >> custId;
          system.removeCustomer(custId);
        }
        break;
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
void employeeMenu(HotelManagementSystem &system, int empId)
{
  int choice;
  do
  {
    std::cout << "\n=== EMPLOYEE MENU ===\n";
    std::cout << "1. View Available Rooms\n";
    std::cout << "2. Book Room for Customer\n";
    std::cout << "3. Give Discount to Customer\n";
    std::cout << "4. Lock/Unlock Room\n";
    std::cout << "5. View Hotel Booking History\n";
    std::cout << "6. View Customer Booking History\n";
    std::cout << "7. View Room Booking History\n";
    std::cout << "0. Logout\n";
    std::cout << "Enter your choice: ";
    std::cin >> choice;

    switch (choice)
    {
    case 1:
      system.showRoom();
      break;

    case 2:
    {
      int custId;
      std::cout << "Enter customer ID: ";
      std::cin >> custId;
      customer *cust = system.findCustomer(custId);
      if (cust)
      {
        system.bookRoom(cust);
      }
      else
      {
        std::cout << "Customer not found!\n";
      }
    }
    break;

    case 3:
    {
      int custId, discount;
      std::cout << "Enter customer ID: ";
      std::cin >> custId;
      std::cout << "Enter discount percentage: ";
      std::cin >> discount;
      system.giveDiscountToCustomer(custId, discount);
    }
    break;

    case 4:
    {
      std::string roomId;
      int lockChoice;
      std::cout << "Enter room ID: ";
      std::cin >> roomId;
      std::cout << "1. Lock Room\n2. Unlock Room\nChoice: ";
      std::cin >> lockChoice;

      // Find employee to perform lock/unlock
      // This would need to be implemented in the system
      std::cout << "Room lock/unlock functionality\n";
    }
    break;

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
        if (foundRoom)
        {
          std::cout << "\n=== ROOM BOOKING HISTORY ===\n";
          std::cout << "Room ID: " << roomId << std::endl;
          foundRoom->displayBookingHistory();
        }
        else
        {
          std::cout << "Room not found!\n";
        }
      }
      break;

    case 0:
      std::cout << "Logging out...\n";
      break;

    default:
      std::cout << "Invalid choice!\n";
    }
  } while (choice != 0);
}

void customerMenu(HotelManagementSystem &system, customer *cust)
{
  int choice;
  do
  {
    std::cout << "\n=== CUSTOMER MENU ===\n";
    std::cout << "Welcome, " << cust->getName() << "!\n";
    std::cout << "1. View Available Rooms\n";
    std::cout << "2. Book Room\n";
    std::cout << "3. Cancel Room\n";
    std::cout << "4. View My Booking History\n";
    std::cout << "5. Show Bill\n";
    std::cout << "6. Pay Bill\n";
    std::cout << "7. View Personal Information\n";
    std::cout << "0. Logout\n";
    std::cout << "Enter your choice: ";
    std::cin >> choice;

    switch (choice)
    {
    case 1:
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

        if (cust->bookRoom(system.getHotel(), roomId, checkin, checkout))
        {
          std::cout << "Room booked successfully!\n";
        }
        else
        {
          std::cout << "Failed to book room!\n";
        }
      }
      break;

    case 3:
      // Cancel room
      if (cust->cancelRoom())
      {
        std::cout << "Room cancelled successfully!\n";
      }
      else
      {
        std::cout << "Failed to cancel room!\n";
      }
      break;

    case 4:
      // View booking history
      cust->viewMyBookingHistory();
      break;

    case 5:
      // Show bill
      cust->showBill();
      break;

    case 6:
      // Pay bill
      if (cust->payBill())
      {
        std::cout << "Bill paid successfully!\n";
      }
      else
      {
        std::cout << "Failed to pay bill!\n";
      }
      break;

    case 7:
      // View personal information
      cust->showInfo();
      break;

    case 0:
      std::cout << "Logging out...\n";
      break;

    default:
      std::cout << "Invalid choice!\n";
    }
  } while (choice != 0);
}