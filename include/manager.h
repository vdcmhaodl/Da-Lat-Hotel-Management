#pragma once

#include "employee.h"
#include <vector>
#include <iomanip>

// Forward declaration
class HotelManagementSystem;

class manager : public employee {
 private:
  std::vector<IPerson*> ListOfEmployees;

 public:
  // mananager_init
  manager();
  manager(const std::string name, const std::string phone,
          const std::string email, const int id, double salary);
  virtual ~manager() = default;

  // manager_fucntion
  void add(IPerson* person);  // hireEmployee
  void remove(int id);        // fireEmployee
  void viewEmployeeList();
  void updateEmployeePosition(int id, const std::string& newPosition);
  void generateReport();
  void showInfo() override;
  std::string getName() override;
  int getID() const override;
  bool hasEmployee(int id);
  std::vector<IPerson*> getEmployeeList();

  // Manager-specific booking history methods
  void viewAllBookingHistory(const std::vector<customer*>& customers);
  void generateBookingReport(const std::vector<customer*>& customers);
  void viewBookingStatistics(const std::vector<customer*>& customers);
  void viewRevenueReport(const std::vector<customer*>& customers);
};