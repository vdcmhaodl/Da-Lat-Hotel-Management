#include "HotelManagement.h"
#include <fstream>

HotelManagementSystem::~HotelManagementSystem()
{
  for (customer *cust : listOfCustormer)
  {
    delete cust; // Free the memory for each customer object
  }
}
void HotelManagementSystem::hireEmployee()
{
  std::string name, phone, email, pass;
  std::cin.ignore();

  std::cout << "Enter employee's name: ";
  std::getline(std::cin, name);

  std::cout << "Enter employee's password (important): ";
  std::cin >> pass;

  std::cout << "Enter employee's phone: ";
  std::cin >> phone;

  std::cout << "Enter employee's email: ";
  std::cin >> email;

  bool gender;
  std::cout << "Enter employee's gender (1 for male, 0 for female): ";
  std::cin >> gender;
  employee *A = new employee(name, phone, email, ++nextEmployeeId, gender, 0);
  m.add(A);
  A->setPassword(pass);
  std::cout << "Hire employee successfully\n";
}
void HotelManagementSystem::fireEmployee(int id) { m.remove(id); }

bool HotelManagementSystem::addEmployee(const std::string &name, const std::string &phone,
                                        const std::string &email, bool gender, double salary,
                                        const std::string &position, const std::string &password)
{
  try
  {
    // Create new employee with auto-generated ID
    int newId = 2000 + (int)(rand() % 1000); // Generate ID between 2000-2999
    employee *newEmployee = new employee(name, phone, email, newId, gender, salary);

    // Set password
    newEmployee->setPassword(password);

    // Add to manager's employee list
    m.add(newEmployee);

    // Update position through manager (since updatePosition is protected)
    m.updateEmployeePosition(newId, position);

    return true;
  }
  catch (const std::exception &e)
  {
    return false;
  }
}

void HotelManagementSystem::viewEmployees() { m.viewEmployeeList(); }
void HotelManagementSystem::addRoom(int flr, int type) { h.addRoom(flr, type); }
customer *HotelManagementSystem::addCustomer()
{
  std::string name, phone, email, password;
  bool gender;

  std::cin.ignore();

  std::cout << "Enter customer's name: ";
  std::getline(std::cin, name);

  std::cout << "Enter customer's password (IMPORTANT): ";
  std::cin >> password;

  std::cout << "Enter customer's phone: ";
  std::cin >> phone;

  std::cout << "Enter customer's gender (1 for male, 0 for female): ";
  std::cin >> gender;

  std::cout << "Enter customer's email: ";
  std::cin >> email;

  // Create a new customer object with a unique ID
  customer *newCustomer =
      new customer(name, phone, email, ++nextCustomerId, gender);
  listOfCustormer.push_back(newCustomer);

  newCustomer->setPassword(password);

  std::cout << "Customer " << newCustomer->getName() << " added with ID "
            << newCustomer->getID() << "." << std::endl;
  return newCustomer;
}

bool HotelManagementSystem::addCustomer(const std::string &name, const std::string &phone,
                                        const std::string &email, bool gender, const std::string &password)
{
  try
  {
    // Create a new customer object with a unique ID
    customer *newCustomer = new customer(name, phone, email, ++nextCustomerId, gender);
    listOfCustormer.push_back(newCustomer);
    newCustomer->setPassword(password);

    return true;
  }
  catch (const std::exception &e)
  {
    return false;
  }
}

void HotelManagementSystem::removeCustomer(int id)
{
  for (auto it = listOfCustormer.begin(); it != listOfCustormer.end(); ++it)
  {
    if ((*it)->getID() == id)
    {
      std::cout << "Removing customer: " << (*it)->getName()
                << " (ID: " << (*it)->getID() << ")." << std::endl;
      delete *it;                // Free the memory of the customer object
      listOfCustormer.erase(it); // Remove the pointer from the vector
      return;                    // Exit the function after finding and removing the customer
    }
  }
  std::cout << "Error: Customer with ID " << id << " not found." << std::endl;
}

void HotelManagementSystem::showCustomer()
{
  for (auto it : listOfCustormer)
  {
    it->showInfo();
  }
}

void HotelManagementSystem::bookRoom(customer *cus)
{
  if (!cus)
  {
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
  if (!foundRoom)
  {
    std::cout << "Room not found!\n";
    return;
  }

  if (!foundRoom->isAvailable())
  {
    std::cout << "Room is not available!\n";
    return;
  }

  // Đặt phòng
  if (cus->bookRoom(h, roomId, checkin, checkout))
  {
    std::cout << "Room booked successfully!\n";

    // Tạo booking record (đã được thêm vào trong customer::bookRoom)
    std::cout << "Booking record added to customer history.\n";
  }
  else
  {
    std::cout << "Failed to book room!\n";
  }
}

void HotelManagementSystem::showRoom() { h.displayAllRooms(); }

void HotelManagementSystem::showRoomByID(std::string ID)
{
  room *temp = h.findRoomByNumber(ID);
  if (temp == nullptr)
    return;
  std::cout << "Room Type: " << temp->getTypeName() << '\n';
  temp->displayFurniture();
  temp->displayItem();
}

void HotelManagementSystem::removeRoom()
{
  int fl;
  std::string id;
  std::cout << "Enter floor: \n";
  std::cin >> fl;
  std::cout << "Enter id room in that floor: \n";
  std::cin >> id;
  h.removeRoom(fl, id);
  std::cout << "Remove room with" << id << "successfully\n";
}

hotel &HotelManagementSystem::getHotel() { return h; }

bool HotelManagementSystem::isEmployee(int id)
{
  return m.hasEmployee(id); // You need to implement this in `manager`
}

bool HotelManagementSystem::checkPassManager(std::string pass)
{
  return m.CheckManagerPass(pass);
}
bool HotelManagementSystem::checkPassEmployee(int id, std::string pass)
{
  return m.CheckEmployeePass(id, pass);
}
bool HotelManagementSystem::checkPassCustomer(int id, std::string pass)
{
  for (auto *c : listOfCustormer)
  {
    if (c->getID() == id && c->checkPass(pass))
      return true;
  }
  return false;
}

customer *HotelManagementSystem::getCustomerById(int id)
{
  for (auto *c : listOfCustormer)
  {
    if (c->getID() == id)
      return c;
  }
  return nullptr;
}

void HotelManagementSystem::giveDiscountToCustomer(int custId, int percent)
{
  customer *c = getCustomerById(custId);
  if (c != nullptr)
  {
    c->setDiscount(percent);
    std::cout << "Discount applied.\n";
  }
  else
  {
    std::cout << "Customer not found.\n";
  }
}
manager &HotelManagementSystem::getManager() { return m; }

customer *HotelManagementSystem::findCustomer(int id)
{
  for (auto it : listOfCustormer)
    if (id == it->getID())
    {
      return it;
    }
  return nullptr;
}

void HotelManagementSystem::saveSystemState()
{
  std::ofstream outFile("./data/hotel_system.dat");
  if (!outFile.is_open())
  {
    std::cout << "Error: Could not open file for saving!\n";
    return;
  }

  try
  {
    // Save manager info
    m.saveToFile(outFile);

    // Save hotel info
    h.saveToFile(outFile);

    // Save employees through manager
    m.saveEmployeesToFile(outFile);

    // Save customers count
    outFile << listOfCustormer.size() << "\n";

    // Save each customer (this already includes their booking history)
    for (const auto &customer : listOfCustormer)
    {
      customer->saveToFile(outFile);
    }

    // Save additional booking history metadata
    outFile << "BOOKING_HISTORY_SECTION\n";

    // Count total booking records across all customers
    int totalBookings = 0;
    for (const auto &customer : listOfCustormer)
    {
      totalBookings += customer->getBookingHistory().size();
    }

    outFile << totalBookings << "\n";

    // Save consolidated booking history with customer references
    for (const auto &customer : listOfCustormer)
    {
      auto history = customer->getBookingHistory();
      for (const auto &record : history)
      {
        // Format:
        // customerID,roomID,roomTypeName,checkin_day,checkin_month,checkin_year,
        //         checkout_day,checkout_month,checkout_year,totalCost,isPaid,status,
        //         booking_day,booking_month,booking_year
        outFile << customer->getID() << "," << record.roomID << ","
                << record.roomTypeName << "," << record.checkin.day << ","
                << record.checkin.month << "," << record.checkin.year << ","
                << record.checkout.day << "," << record.checkout.month << ","
                << record.checkout.year << "," << record.totalCost << ","
                << (record.isPaid ? 1 : 0) << "," << record.status << ","
                << record.bookingDate.day << "," << record.bookingDate.month
                << "," << record.bookingDate.year << "\n";
      }
    }

    // Save next customer ID and employee ID
    outFile << nextCustomerId << "\n";
    outFile << m.getEmployeeList().size() << "\n";

    outFile.close();
    std::cout << "System state saved successfully!\n";
    std::cout << "Total booking records saved: " << totalBookings << "\n";
  }
  catch (const std::exception &e)
  {
    std::cout << "Error saving system state: " << e.what() << std::endl;
  }
}

void HotelManagementSystem::viewAllBookingHistory()
{
  std::cout << "\n=== HOTEL BOOKING HISTORY ===\n";

  if (listOfCustormer.empty())
  {
    std::cout << "No customers found.\n";
    return;
  }

  // Sử dụng manager để xem booking history với quyền cao nhất
  m.viewAllBookingHistory(listOfCustormer);
}

void HotelManagementSystem::viewCustomerBookingHistory(int customerId)
{
  customer *cust = findCustomer(customerId);
  if (!cust)
  {
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

std::vector<customer *> HotelManagementSystem::getAllCustomers() const
{
  return listOfCustormer;
}

// Thêm booking record cho customer
void HotelManagementSystem::addBookingRecord(customer *cust,
                                             const booking_record &record)
{
  if (cust)
  {
    cust->addBookingRecord(record);
  }
}

// Cập nhật trạng thái booking của customer
void HotelManagementSystem::updateCustomerBookingStatus(int customerId,
                                                        std::string roomID,
                                                        date checkin,
                                                        std::string status)
{
  customer *cust = findCustomer(customerId);
  if (cust)
  {
    cust->updateBookingStatus(roomID, checkin, status);
  }
}

void HotelManagementSystem::updateBaseCustomerId(int n)
{
  nextCustomerId += n - 1;
}

void HotelManagementSystem::loadSystemState()
{
  std::ifstream inFile("./data/hotel_system.dat");
  if (!inFile.is_open())
  {
    std::cout << "No existing data file found. Starting with fresh system.\n";
    return;
  }

  try
  {
    std::cout << "Loading system state...\n";

    // Load manager info
    std::cout << "Loading manager info...\n";
    m.loadFromFile(inFile);

    // Load hotel info
    std::cout << "Loading hotel info...\n";
    h.loadFromFile(inFile);

    // Load employees through manager
    std::cout << "Loading employees...\n";
    m.loadEmployeesFromFile(inFile);

    // Clear existing customers
    for (auto &customer : listOfCustormer)
    {
      delete customer;
    }
    listOfCustormer.clear();

    // Load customers count
    size_t customerCount;
    inFile >> customerCount;
    inFile.ignore();

    std::cout << "Loading " << customerCount << " customers...\n";

    // Load each customer (this loads their individual booking history)
    for (size_t i = 0; i < customerCount; ++i)
    {
      customer *newCustomer = new customer();
      newCustomer->loadFromFile(inFile, h);
      listOfCustormer.push_back(newCustomer);
    }

    // Check for additional booking history section
    std::string line;
    if (std::getline(inFile, line) && line == "BOOKING_HISTORY_SECTION")
    {
      std::cout << "Loading consolidated booking history...\n";

      int totalBookings;
      inFile >> totalBookings;
      inFile.ignore();

      std::cout << "Loading " << totalBookings << " booking records...\n";

      // Load consolidated booking history for validation/backup
      for (int i = 0; i < totalBookings; ++i)
      {
        std::string bookingLine;
        std::getline(inFile, bookingLine);

        // Parse booking record
        std::stringstream ss(bookingLine);
        std::string token;
        std::vector<std::string> tokens;

        while (std::getline(ss, token, ','))
        {
          tokens.push_back(token);
        }

        if (tokens.size() >= 15)
        {
          int customerId = std::stoi(tokens[0]);

          // Find customer and verify booking record exists
          customer *cust = findCustomer(customerId);
          if (cust)
          {
            // Verify this booking exists in customer's history
            auto history = cust->getBookingHistory();
            bool found = false;

            for (const auto &record : history)
            {
              if (record.roomID == tokens[1] &&
                  record.checkin.day == std::stoi(tokens[3]) &&
                  record.checkin.month == std::stoi(tokens[4]) &&
                  record.checkin.year == std::stoi(tokens[5]) && record.isPaid && record.checkout.day == std::stoi(tokens[6]) &&
                  record.checkout.month == std::stoi(tokens[7]) &&
                  record.checkout.year == std::stoi(tokens[8]))
              {
                found = true;
                break;
              }
            }

            if (!found)
            {
              std::cout << "Warning: Booking record mismatch for customer "
                        << customerId << ", room " << tokens[1] << "\n";

              // Optionally add missing booking record
              booking_record missingRecord;
              missingRecord.roomID = tokens[1];
              missingRecord.roomTypeName = tokens[2];
              missingRecord.checkin = {std::stoi(tokens[3]),
                                       std::stoi(tokens[4]),
                                       std::stoi(tokens[5])};
              missingRecord.checkout = {std::stoi(tokens[6]),
                                        std::stoi(tokens[7]),
                                        std::stoi(tokens[8])};
              missingRecord.totalCost = std::stod(tokens[9]);
              missingRecord.isPaid = (std::stoi(tokens[10]) == 1);
              missingRecord.status = tokens[11];
              missingRecord.bookingDate = {std::stoi(tokens[12]),
                                           std::stoi(tokens[13]),
                                           std::stoi(tokens[14])};

              cust->addBookingRecord(missingRecord);
              std::cout << "Added missing booking record for customer "
                        << customerId << "\n";
            }
          }
          else
          {
            std::cout << "Warning: Booking record for unknown customer "
                      << customerId << "\n";
          }
        }
      }
    }
    else
    {
      // Old format without consolidated booking history section
      std::cout << "Loading old format without consolidated booking history.\n";
      // Put the line back for next ID reading
      if (!line.empty())
      {
        std::stringstream temp(line);
        temp >> nextCustomerId;
      }
      else
      {
        inFile >> nextCustomerId;
      }
    }

    // Load next customer ID and employee ID (if not already loaded above)
    if (line != "BOOKING_HISTORY_SECTION")
    {
      inFile >> nextEmployeeId;
    }
    else
    {
      inFile >> nextCustomerId;
      inFile >> nextEmployeeId;
    }

    inFile.close();
    std::cout << "System state loaded successfully!\n";
    std::cout << "Loaded: " << customerCount << " customers\n";

    // Count and display total bookings
    int totalLoadedBookings = 0;
    for (const auto &customer : listOfCustormer)
    {
      totalLoadedBookings += customer->getBookingHistory().size();
    }
    std::cout << "Total booking records: " << totalLoadedBookings << "\n";
    std::cout << "Next Customer ID: " << nextCustomerId << "\n";
    std::cout << "Next Employee ID: " << nextEmployeeId << "\n";
  }
  catch (const std::exception &e)
  {
    std::cout << "Error loading system state: " << e.what() << std::endl;

    // Clean up in case of error
    for (auto &customer : listOfCustormer)
    {
      delete customer;
    }
    listOfCustormer.clear();

    // Reset to default values
    nextCustomerId = 1000;
    nextEmployeeId = 0;

    inFile.close();
    std::cout << "Continuing with fresh system...\n";
  }
}