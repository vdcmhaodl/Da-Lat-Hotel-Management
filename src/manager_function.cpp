#include "manager.h"
#include <vector>
#include <iostream>
#include <algorithm>
#include <iomanip>
#include <map>

void manager::add(IPerson* person) {
  // If the pointer points to a custormer, no operation
  if (dynamic_cast<employee*>(person)) {
    ListOfEmployees.push_back(person);
  } else {
    // Error !
    std::cout << "Only Employees can be managed by Manager.\n";
  }
}
void manager::remove(int id) {
  auto it = std::remove_if(ListOfEmployees.begin(), ListOfEmployees.end(),
                           [id](IPerson* p) { return p->getID() == id; });
  if (it != ListOfEmployees.end()) {
    std::cout << "Removed employee with ID: " << id << " successfully.\n";
    ListOfEmployees.erase(it, ListOfEmployees.end());
  } else {
    std::cout << "Employee with ID: " << id << " not found.\n";
  }
}
void manager::viewEmployeeList() {
  std::cout << "=====================\n";
  std::cout << "List of Employees:" << std::endl;
  for (auto person : ListOfEmployees) {
    std::cout << "------------------\n";
    employee* emp = dynamic_cast<employee*>(person);
    if (emp) {
      emp->showInfo();
    } else {
      // If Error in casting
      std::cout << "Not an employee.\n";
    }
  }
  std::cout << "=====================\n";
}

void manager::updateEmployeePosition(int id, const std::string& newPosition) {
  for (auto it : ListOfEmployees) {
    employee* emp = dynamic_cast<employee*>(it);
    if (emp->getID() == id) {
      emp->updatePosition(newPosition);
      std::cout << "Updated position for employee id:" << id << " to "
                << newPosition << std::endl;
      return;
    }
  }
  std::cout << "Employee with ID " << id << " not found." << std::endl;
}
void manager::generateReport() {
  std::cout << "Number of Employees: " << ListOfEmployees.size() << std::endl;
  for (auto it : ListOfEmployees) {
    employee* emp = dynamic_cast<employee*>(it);
    emp->showInfo();
    std::cout << "\n";
  }
  /* Additional things will be added here:
  + Average, mininum, maximum salary employees
  + Total number of rooms available
  + Total number of rooms booked
  + Total revenue generated from bookings
  */
}

void manager::showInfo() {
  std::cout << "Manager " << id << ":\n";
  std::cout << "Name: " << name << "\n";
  std::cout << "Phone: " << phone << "\n";
  std::cout << "Email: " << email << "\n";
  std::cout << "Salary: " << salary << "\n";
  std::cout << "Position: " << position << "\n";
}

std::string manager::getName() { return name; }

int manager::getID() const { return id; }

bool manager::hasEmployee(int id) {
  for (auto p : ListOfEmployees) {
    if (p->getID() == id) return true;
  }
  return false;
}

std::vector<IPerson*> manager::getEmployeeList() { return ListOfEmployees; }

void manager::viewAllBookingHistory(const std::vector<customer*>& customers) {
  std::cout << "\n=== COMPLETE HOTEL BOOKING HISTORY (Manager View) ===\n";
  std::cout << std::string(120, '=') << std::endl;

  if (customers.empty()) {
    std::cout << "No customers found.\n";
    return;
  }

  std::cout << std::left << std::setw(12) << "Customer ID" << std::setw(18)
            << "Customer Name" << std::setw(15) << "Phone" << std::setw(10)
            << "Room ID" << std::setw(15) << "Room Type" << std::setw(12)
            << "Check-in" << std::setw(12) << "Check-out" << std::setw(10)
            << "Cost" << std::setw(8) << "Paid" << std::setw(12) << "Status"
            << std::endl;
  std::cout << std::string(120, '-') << std::endl;

  for (const auto& customer : customers) {
    auto history = customer->getBookingHistory();

    for (const auto& record : history) {
      std::cout << std::left << std::setw(12) << customer->getID()
                << std::setw(18) << customer->getName() << std::setw(15)
                << customer->getPhone() << std::setw(10) << record.roomID
                << std::setw(15) << record.roomTypeName << std::setw(12)
                << (std::to_string(record.checkin.day) + "/" +
                    std::to_string(record.checkin.month) + "/" +
                    std::to_string(record.checkin.year))
                << std::setw(12)
                << (std::to_string(record.checkout.day) + "/" +
                    std::to_string(record.checkout.month) + "/" +
                    std::to_string(record.checkout.year))
                << std::setw(10) << ("$" + std::to_string(record.totalCost))
                << std::setw(8) << (record.isPaid ? "Yes" : "No")
                << std::setw(12) << record.status << std::endl;
    }

    if (!history.empty()) {
      std::cout << std::string(120, '-') << std::endl;
    }
  }
  std::cout << std::string(120, '=') << std::endl;
}

// Manager tạo báo cáo booking tổng hợp
void manager::generateBookingReport(const std::vector<customer*>& customers) {
  std::cout << "\n=== BOOKING REPORT (Manager) ===\n";
  std::cout << std::string(80, '=') << std::endl;

  int totalBookings = 0;
  int completedBookings = 0;
  int cancelledBookings = 0;
  int currentBookings = 0;
  double totalRevenue = 0;
  double paidRevenue = 0;

  std::map<std::string, int> roomTypeCount;
  std::map<std::string, double> roomTypeRevenue;

  for (const auto& customer : customers) {
    auto history = customer->getBookingHistory();

    for (const auto& record : history) {
      totalBookings++;

      if (record.status == "Completed")
        completedBookings++;
      else if (record.status == "Cancelled")
        cancelledBookings++;
      else if (record.status == "Current")
        currentBookings++;

      totalRevenue += record.totalCost;
      if (record.isPaid) {
        paidRevenue += record.totalCost;
      }

      roomTypeCount[record.roomTypeName]++;
      roomTypeRevenue[record.roomTypeName] += record.totalCost;
    }
  }

  // Tổng quan
  std::cout << "=== GENERAL STATISTICS ===\n";
  std::cout << "Total Customers: " << customers.size() << std::endl;
  std::cout << "Total Bookings: " << totalBookings << std::endl;
  std::cout << "Completed Bookings: " << completedBookings << std::endl;
  std::cout << "Current Bookings: " << currentBookings << std::endl;
  std::cout << "Cancelled Bookings: " << cancelledBookings << std::endl;
  std::cout << "Total Revenue: $" << totalRevenue << std::endl;
  std::cout << "Paid Revenue: $" << paidRevenue << std::endl;
  std::cout << "Unpaid Revenue: $" << (totalRevenue - paidRevenue) << std::endl;

  // Thống kê theo loại phòng
  std::cout << "\n=== ROOM TYPE STATISTICS ===\n";
  std::cout << std::left << std::setw(20) << "Room Type" << std::setw(15)
            << "Bookings" << std::setw(15) << "Revenue" << std::endl;
  std::cout << std::string(50, '-') << std::endl;

  for (const auto& pair : roomTypeCount) {
    std::cout << std::left << std::setw(20) << pair.first << std::setw(15)
              << pair.second << std::setw(15)
              << ("$" + std::to_string((int)roomTypeRevenue[pair.first]))
              << std::endl;
  }

  std::cout << std::string(80, '=') << std::endl;
}

// Manager xem thống kê booking
void manager::viewBookingStatistics(const std::vector<customer*>& customers) {
  std::cout << "\n=== DETAILED BOOKING STATISTICS ===\n";
  std::cout << std::string(80, '=') << std::endl;

  std::map<int, int> monthlyBookings;    // month -> count
  std::map<int, double> monthlyRevenue;  // month -> revenue
  std::map<std::string, int> statusCount;

  for (const auto& customer : customers) {
    auto history = customer->getBookingHistory();

    for (const auto& record : history) {
      monthlyBookings[record.checkin.month]++;
      monthlyRevenue[record.checkin.month] += record.totalCost;
      statusCount[record.status]++;
    }
  }

  // Thống kê theo tháng
  std::cout << "=== MONTHLY STATISTICS ===\n";
  std::cout << std::left << std::setw(10) << "Month" << std::setw(15)
            << "Bookings" << std::setw(15) << "Revenue" << std::endl;
  std::cout << std::string(40, '-') << std::endl;

  for (const auto& pair : monthlyBookings) {
    std::cout << std::left << std::setw(10) << pair.first << std::setw(15)
              << pair.second << std::setw(15)
              << ("$" + std::to_string((int)monthlyRevenue[pair.first]))
              << std::endl;
  }

  // Thống kê theo trạng thái
  std::cout << "\n=== STATUS STATISTICS ===\n";
  for (const auto& pair : statusCount) {
    std::cout << pair.first << ": " << pair.second << " bookings\n";
  }

  std::cout << std::string(80, '=') << std::endl;
}

// Manager xem báo cáo doanh thu
void manager::viewRevenueReport(const std::vector<customer*>& customers) {
  std::cout << "\n=== REVENUE REPORT (Manager) ===\n";
  std::cout << std::string(80, '=') << std::endl;

  double totalRevenue = 0;
  double paidRevenue = 0;
  double unpaidRevenue = 0;

  std::map<std::string, double> customerRevenue;

  for (const auto& customer : customers) {
    auto history = customer->getBookingHistory();
    double custRevenue = 0;

    for (const auto& record : history) {
      totalRevenue += record.totalCost;
      custRevenue += record.totalCost;

      if (record.isPaid) {
        paidRevenue += record.totalCost;
      } else {
        unpaidRevenue += record.totalCost;
      }
    }

    if (custRevenue > 0) {
      customerRevenue[customer->getName() +
                      " (ID:" + std::to_string(customer->getID()) + ")"] =
          custRevenue;
    }
  }

  std::cout << "Total Revenue: $" << totalRevenue << std::endl;
  std::cout << "Paid Revenue: $" << paidRevenue << " ("
            << (paidRevenue / totalRevenue * 100) << "%)\n";
  std::cout << "Unpaid Revenue: $" << unpaidRevenue << " ("
            << (unpaidRevenue / totalRevenue * 100) << "%)\n";

  std::cout << "\n=== TOP CUSTOMERS BY REVENUE ===\n";
  std::cout << std::left << std::setw(30) << "Customer" << std::setw(15)
            << "Total Revenue" << std::endl;
  std::cout << std::string(45, '-') << std::endl;

  // Sort customers by revenue (descending)
  std::vector<std::pair<std::string, double>> sortedCustomers(
      customerRevenue.begin(), customerRevenue.end());
  std::sort(sortedCustomers.begin(), sortedCustomers.end(),
            [](const std::pair<std::string, double>& a,
               const std::pair<std::string, double>& b) {
              return a.second > b.second;
            });
  for (const auto& pair : sortedCustomers) {
    std::cout << std::left << std::setw(30) << pair.first << std::setw(15)
              << ("$" + std::to_string((int)pair.second)) << std::endl;
  }

  std::cout << std::string(80, '=') << std::endl;
}