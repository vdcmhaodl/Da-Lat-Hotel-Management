#pragma once
#include "hotel.h"
#include "customer.h"
#include "manager.h"
#include <vector>

class HotelManagementSystem {
 private:
  hotel h;
  manager m;
  std::vector<customer *> listOfCustormer;
  int nextCustomerId = 24127000;  // Counter for assigning unique customer IDs

 public:
  HotelManagementSystem(int floor, const std::string name,
                        const std::string phone, const std::string email,
                        const int id, double salary, const std::string position)
      : h(floor), m(name, phone, email, id, salary) {};
  ~HotelManagementSystem();

  // Manage people
  void hireEmployee(IPerson *person);
  void fireEmployee(int id);
  void viewEmployees();
  customer *addCustomer();
  customer *findCustomer(int id);
  void updateBaseCustomerId(int n);

  // Manage Room
  void addRoom(int flr, int type);
  // Function to remove a customer by their ID
  void removeCustomer(int id);
  void showCustomer();
  void bookRoom(customer *cus);
  void showRoom();
  void removeRoom();

  // HotelManagementSystem.h
  manager &getManager();
  hotel &getHotel();
  bool isEmployee(int id);
  customer *getCustomerById(int id);
  void giveDiscountToCustomer(int custId, int percent);

  // Booking history methods
  void viewAllBookingHistory();                     // For manager/employee
  void viewCustomerBookingHistory(int customerId);  // For specific customer
  std::vector<customer *> getAllCustomers() const;  // Helper method

  // Helper methods for booking operations
  void addBookingRecord(customer *cust, const booking_record &record);
  void updateCustomerBookingStatus(int customerId, std::string roomID,
                                   date checkin, std::string status);

  // load save system
  void saveSystemState();
  void loadSystemState();
};