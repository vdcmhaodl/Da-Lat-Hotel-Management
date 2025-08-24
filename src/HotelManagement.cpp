#include "HotelManagement.h"
#include <fstream>

HotelManagementSystem::~HotelManagementSystem() {
  for (customer *cust : listOfCustormer) {
    delete cust;  // Free the memory for each customer object
  }
}
void HotelManagementSystem::hireEmployee() {
  std::string name, phone, email;

  std::cin.ignore();

  std::cout << "Enter employee's name: ";
  std::getline(std::cin, name);

  std::cout << "Enter employee's phone: ";
  std::cin >> phone;

  std::cout << "Enter employee's email: ";
  std::cin >> email;
  m.add(new employee(name, phone, email, 1, ++nextEmployeeId));
  std::cout << "Hire employee successfully\n";
}
void HotelManagementSystem::fireEmployee(int id) { m.remove(id); }
void HotelManagementSystem::viewEmployees() { m.viewEmployeeList(); }
void HotelManagementSystem::addRoom(int flr, int type) { h.addRoom(flr, type); }
customer *HotelManagementSystem::addCustomer() {
  std::string name, phone, email;

  std::cin.ignore();

  std::cout << "Enter customer's name: ";
  std::getline(std::cin, name);

  std::cout << "Enter customer's phone: ";
  std::cin >> phone;

  std::cout << "Enter customer's email: ";
  std::cin >> email;

  // Create a new customer object with a unique ID
  customer *newCustomer = new customer(name, phone, email, ++nextCustomerId);
  listOfCustormer.push_back(newCustomer);

  std::cout << "Customer " << newCustomer->getName() << " added with ID "
            << newCustomer->getID() << "." << std::endl;
  return newCustomer;
}
void HotelManagementSystem::removeCustomer(int id) {
  for (auto it = listOfCustormer.begin(); it != listOfCustormer.end(); ++it) {
    if ((*it)->getID() == id) {
      std::cout << "Removing customer: " << (*it)->getName()
                << " (ID: " << (*it)->getID() << ")." << std::endl;
      delete *it;                 // Free the memory of the customer object
      listOfCustormer.erase(it);  // Remove the pointer from the vector
      return;  // Exit the function after finding and removing the customer
    }
  }
  std::cout << "Error: Customer with ID " << id << " not found." << std::endl;
}

void HotelManagementSystem::showCustomer() {
  for (auto it : listOfCustormer) {
    it->showInfo();
  }
}

void HotelManagementSystem::bookRoom(customer *cus) {
  if (!cus) {
    std::cout << "Invalid customer!\n";
    return;
  }

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

  // Tìm phòng
  room *foundRoom = h.findRoomByNumber(roomId);
  if (!foundRoom) {
    std::cout << "Room not found!\n";
    return;
  }

  if (!foundRoom->isAvailable()) {
    std::cout << "Room is not available!\n";
    return;
  }

  // Đặt phòng
  if (cus->bookRoom(h, roomId, checkin, checkout)) {
    std::cout << "Room booked successfully!\n";

    // Tạo booking record (đã được thêm vào trong customer::bookRoom)
    std::cout << "Booking record added to customer history.\n";
  } else {
    std::cout << "Failed to book room!\n";
  }
}

void HotelManagementSystem::showRoom() { h.displayAllRooms(); }

void HotelManagementSystem::removeRoom() {
  int fl;
  std::string id;
  std::cout << "Enter floor: \n";
  std::cin >> fl;
  std::cout << "Enter id room in that floor: \n";
  std::cin >> id;
  h.removeRoom(fl, id);
  std::cout << "Remove room with" << id << "successfully\n";
}

manager &HotelManagementSystem::getManager() { return m; }

hotel &HotelManagementSystem::getHotel() { return h; }

bool HotelManagementSystem::isEmployee(int id) {
  // Let manager check his employee list
  return m.hasEmployee(id);  // You need to implement this in `manager`
}

customer *HotelManagementSystem::getCustomerById(int id) {
  for (auto *c : listOfCustormer) {
    if (c->getID() == id) return c;
  }
  return nullptr;
}

void HotelManagementSystem::giveDiscountToCustomer(int custId, int percent) {
  customer *c = getCustomerById(custId);
  if (c != nullptr) {
    c->setDiscount(percent);
    std::cout << "Discount applied.\n";
  } else {
    std::cout << "Customer not found.\n";
  }
}

customer *HotelManagementSystem::findCustomer(int id) {
  for (auto it : listOfCustormer)
    if (id == it->getID()) {
      return it;
    }
  return nullptr;
}

void HotelManagementSystem::saveSystemState() {
  std::ofstream outFile("hotel_system.dat");
  if (!outFile.is_open()) {
    std::cout << "Error: Could not open file for saving!\n";
    return;
  }

  try {
    // Save manager info
    m.saveToFile(outFile);

    // Save hotel info
    h.saveToFile(outFile);

    // Save employees through manager
    m.saveEmployeesToFile(outFile);

    // Save customers count
    outFile << listOfCustormer.size() << "\n";

    // Save each customer
    for (const auto &customer : listOfCustormer) {
      customer->saveToFile(outFile);
    }

    // Save next customer ID and employee ID
    outFile << nextCustomerId << "\n";
    outFile << nextEmployeeId << "\n";

    outFile.close();
    std::cout << "System state saved successfully!\n";
  } catch (const std::exception &e) {
    std::cout << "Error saving system state: " << e.what() << std::endl;
  }
}

void HotelManagementSystem::viewAllBookingHistory() {
  std::cout << "\n=== HOTEL BOOKING HISTORY ===\n";

  if (listOfCustormer.empty()) {
    std::cout << "No customers found.\n";
    return;
  }

  // Sử dụng manager để xem booking history với quyền cao nhất
  m.viewAllBookingHistory(listOfCustormer);
}

void HotelManagementSystem::viewCustomerBookingHistory(int customerId) {
  customer *cust = findCustomer(customerId);
  if (!cust) {
    std::cout << "Customer with ID " << customerId << " not found!\n";
    return;
  }

  std::cout << "\n=== CUSTOMER BOOKING HISTORY ===\n";
  std::cout << "Customer: " << cust->getName() << " (ID: " << cust->getID()
            << ")\n";
  std::cout << "Phone: " << cust->getPhone() << std::endl;
  std::cout << "Email: " << cust->getEmail() << std::endl;

  cust->viewMyBookingHistory();
}

std::vector<customer *> HotelManagementSystem::getAllCustomers() const {
  return listOfCustormer;
}

// Thêm booking record cho customer
void HotelManagementSystem::addBookingRecord(customer *cust,
                                             const booking_record &record) {
  if (cust) {
    cust->addBookingRecord(record);
  }
}

// Cập nhật trạng thái booking của customer
void HotelManagementSystem::updateCustomerBookingStatus(int customerId,
                                                        std::string roomID,
                                                        date checkin,
                                                        std::string status) {
  customer *cust = findCustomer(customerId);
  if (cust) {
    cust->updateBookingStatus(roomID, checkin, status);
  }
}

void HotelManagementSystem::updateBaseCustomerId(int n) {
  nextCustomerId += n - 1;
}

void HotelManagementSystem::loadSystemState() {
  std::ifstream inFile("hotel_system.dat");
  if (!inFile.is_open()) {
    std::cout << "Error: Could not open file for loading!\n";
    return;
  }

  try {
    // Load manager info
    m.loadFromFile(inFile);

    // Load hotel info
    h.loadFromFile(inFile);

    // Load employees through manager
    m.loadEmployeesFromFile(inFile);

    // Clear existing customers
    for (auto &customer : listOfCustormer) {
      delete customer;
    }
    listOfCustormer.clear();

    // Load customers count
    size_t customerCount;
    inFile >> customerCount;
    inFile.ignore();

    // Load each customer
    for (size_t i = 0; i < customerCount; ++i) {
      customer *newCustomer = new customer();
      newCustomer->loadFromFile(inFile, h);
      listOfCustormer.push_back(newCustomer);
    }

    // Load next customer ID and employee ID
    inFile >> nextCustomerId;
    inFile >> nextEmployeeId;

    inFile.close();
    std::cout << "System state loaded successfully!\n";
  } catch (const std::exception &e) {
    std::cout << "Error loading system state: " << e.what() << std::endl;

    // Clean up in case of error
    for (auto &customer : listOfCustormer) {
      delete customer;
    }
    listOfCustormer.clear();
  }
}