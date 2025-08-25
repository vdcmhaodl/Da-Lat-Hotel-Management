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
  HotelManagementSystem *system =
      new HotelManagementSystem(5, "Huynh Thai Hoang", "0983824401",
                                "manager@hotel.com", 1, 1, 60000, "Manager");
  std::cout << "Create system successfully\n";

  system->loadSystemState();

  int choice;
  do
  {
    std::cout << "\n===== Welcome to Hotel Management System =====\n";
    std::cout << "1. Log in to an existing account\n";
    std::cout << "2. Create a new account\n";
    std::cout << "0. Exit\n";

    std::cin >> choice;
    switch (choice)
    {
    case 1:
    {
      int choice2;
      do
      {
        std::cout << "====================\n";
        std::cout << "1. Login as Manager\n";
        std::cout << "2. Login as Employee\n";
        std::cout << "3. Login as Customer\n";
        std::cout << "0. Exit\n";
        std::cout << "Enter choice: ";
        std::cin >> choice2;
        switch (choice2)
        {
        case 1:
        {
          std::string pass;
          std::cout << "Enter the password for Manager: ";
          std::cin >> pass;
          if (system->checkPassManager(pass))
            managerMenu(*system);
          else
            std::cout << "Wrong password!\n";
          break;
        }
        case 2:
        {
          int id;
          std::string pass;
          std::cout << "Enter your employee ID: ";
          std::cin >> id;
          std::cout << "Enter your employee password: ";
          std::cin >> pass;
          if (system->isEmployee(id) && system->checkPassEmployee(id, pass))
            employeeMenu(*system, id);
          else
            std::cout << "Employee not found or wrong password!.\n";
          break;
        }
        case 3:
        {
          int id;
          std::string pass;
          std::cout << "Enter your customer ID: ";
          std::cin >> id;
          std::cout << "Enter your customer password: ";
          std::cin >> pass;
          if (system->checkPassCustomer(id, pass))
          {
            customer *cust = system->getCustomerById(id);
            if (!cust)
            {
              std::cout << "Error in getting customer!\n";
              break;
            }
            customerMenu(*system, cust);
          }
          else
            std::cout << "Customer not found or wrong password!.\n\n";
          break;
        }
        };
      } while (choice2 != 0);
      break;
    }
    case 2:
    {
      std::cout << "Create a customer's account\n";
      customer *c = system->addCustomer();
      if (c)
        std::cout << "Create successfully, now you can book your desired room in our hotel for your vacation!\n";
      else
      {
        std::cout << "Create failed!\n";
        break;
      }
      std::cout << "Here's your personal information: \n";
      c->showInfo();
      break;
    }
    default:
      break;
    };
  } while (choice != 0);
  system->saveSystemState();
  delete system;
  return 0;
}