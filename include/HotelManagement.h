#pragma once
#include "hotel.h"
#include "customer.h"
#include "manager.h"
#include <vector>

class HotelManagementSystem
{
private:
  hotel h;
  manager m;
  std::vector<customer *> listOfCustormer;
  int nextCustomerId = 24127000; // Safe default value
  int nextEmployeeId = 0;        // Start from 0, not 1

public:
  HotelManagementSystem(int floor, const std::string name,
                        const std::string phone, const std::string email,
                        const int id, double salary, bool gender, const std::string position)
      : h(floor), m(name, phone, email, id, gender, salary)
  {
    // Validate constructor parameters
    if (floor < 1)
      h = hotel(1); // At least 1 floor
    nextCustomerId = (nextCustomerId < 24127000) ? 24127000 : nextCustomerId;
    nextEmployeeId = (nextEmployeeId < 1) ? 1 : nextEmployeeId;
    m.setPassword("31082025");
  };
  ~HotelManagementSystem();
  // Password-check function
  bool checkPassManager(std::string pass);
  bool checkPassEmployee(int id, std::string pass);
  bool checkPassCustomer(int id, std::string pass);
  // Manage people
  void hireEmployee();
  void fireEmployee(int id);
  void viewEmployees();
  customer *addCustomer();
  customer *findCustomer(int id);
  void updateBaseCustomerId(int n);

  // Manage Room
  void addRoom(int flr, int type);
  void removeCustomer(int id);
  void showCustomer();
  void bookRoom(customer *cus);
  void showRoom();
  void showRoomByID(std::string ID);
  void removeRoom();

  manager& getManager();
  hotel &getHotel();
  bool isEmployee(int id);
  customer *getCustomerById(int id);
  void giveDiscountToCustomer(int custId, int percent);

  // Booking history methods
  void viewAllBookingHistory();
  void viewCustomerBookingHistory(int customerId);
  std::vector<customer *> getAllCustomers() const;

  // Helper methods for booking operations
  void addBookingRecord(customer *cust, const booking_record &record);
  void updateCustomerBookingStatus(int customerId, std::string roomID,
                                   date checkin, std::string status);

  // Save/load with validation
  void saveSystemState();
  void loadSystemState();
};