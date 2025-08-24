#pragma once
#include "employee.h"
#include <vector>
#include <iomanip>
#include <fstream>

class manager : public employee {
 private:
  std::vector<IPerson*> ListOfEmployees;

 public:
  manager();
  manager(const std::string name, const std::string phone,
          const std::string email, const int id, const bool gender, double salary);
  virtual ~manager() = default;

  void add(IPerson* person);
  void remove(int id);
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

  void saveToFile(std::ofstream& out);
  void loadFromFile(std::ifstream& in);
  void saveEmployeesToFile(std::ofstream& out);
  void loadEmployeesFromFile(std::ifstream& in);
};