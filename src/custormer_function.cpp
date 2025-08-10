#include "customer.h"
#include <iostream>
#include <iomanip>
#include <fstream>

// Default constructor
customer::customer() : person() {
  discount = 0;
  bill = 0;
  // Initialize dates to default values (assuming date has day, month, year)
  checkin = {0, 0, 0};
  checkout = {0, 0, 0};
}

// Parameterized constructor
customer::customer(std::string name, std::string phone, std::string email,
                   int id)
    : person(name, phone, email, id) {
  discount = 0;
  bill = 0;
  // Initialize dates to default values
  checkin = {0, 0, 0};
  checkout = {0, 0, 0};
}

// Assignment operator
customer &customer::operator=(const customer &other) {
  if (this != &other) {
    person::operator=(other);
    discount = other.discount;
    bill = other.bill;
    checkin = other.checkin;
    checkout = other.checkout;
  }
  return *this;
}

// Set check-in date
void customer::setCheckinDate(date checkin_date) { checkin = checkin_date; }

// Set check-out date
void customer::setCheckoutDate(date checkout_date) { checkout = checkout_date; }

bool isLeap(int year) {
  return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

int daysInMonth(int month, int year) {
  static const int days[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
  if (month == 2 && isLeap(year)) return 29;
  return days[month - 1];
}

// Helper function to count total days since 01/01/0000
int countDays(const date &d) {
  int days = d.day;

  for (int m = 1; m < d.month; ++m) days += daysInMonth(m, d.year);

  for (int y = 0; y < d.year; ++y) days += isLeap(y) ? 366 : 365;

  return days;
}

int customer::calculateNightStays() {
  int checkinDays = countDays(checkin);
  int checkoutDays = countDays(checkout);

  if (checkoutDays <= checkinDays) return 0;

  return checkoutDays - checkinDays;
}

// Override showInfo from person class
void customer::showInfo() {
  std::cout << "=== Customer Information ===" << std::endl;
  std::cout << "ID: " << id << std::endl;
  std::cout << "Name: " << name << std::endl;
  std::cout << "Phone: " << phone << std::endl;
  std::cout << "Email: " << email << std::endl;
  std::cout << "Role: Customer" << std::endl;
  std::cout << "Discount: " << discount << "%" << std::endl;
  std::cout << "Current Bill: $" << bill << std::endl;

  if (checkin.day != 0) {
    std::cout << "Check-in Date: " << checkin.day << "/" << checkin.month << "/"
              << checkin.year << std::endl;
  }
  if (checkout.day != 0) {
    std::cout << "Check-out Date: " << checkout.day << "/" << checkout.month
              << "/" << checkout.year << std::endl;
  }
  std::cout << "==============================" << std::endl;
}

// Override getName from person class
std::string customer::getName() { return name; }

// Override getPosition from person class
// std::string customer::getPosition() { return "Customer"; }

// Override getID from person class
int customer::getID() const { return id; }

void customer::addBookingRecord(const booking_record &record) {
  bookingHistory.push_back(record);
}

void customer::viewMyBookingHistory() {
  std::cout << "\n=== BOOKING HISTORY FOR " << name << " (ID: " << id
            << ") ===\n";
  std::cout << std::string(80, '=') << std::endl;

  if (bookingHistory.empty()) {
    std::cout << "No booking history found.\n";
    return;
  }

  std::cout << std::left << std::setw(10) << "Room ID" << std::setw(15)
            << "Room Type" << std::setw(12) << "Check-in" << std::setw(12)
            << "Check-out" << std::setw(10) << "Cost" << std::setw(8) << "Paid"
            << std::setw(12) << "Status" << std::endl;
  std::cout << std::string(80, '-') << std::endl;

  for (const auto &record : bookingHistory) {
    std::cout << std::left << std::setw(10) << record.roomID << std::setw(15)
              << record.roomTypeName << std::setw(12)
              << (std::to_string(record.checkin.day) + "/" +
                  std::to_string(record.checkin.month) + "/" +
                  std::to_string(record.checkin.year))
              << std::setw(12)
              << (std::to_string(record.checkout.day) + "/" +
                  std::to_string(record.checkout.month) + "/" +
                  std::to_string(record.checkout.year))
              << std::setw(10) << ("$" + std::to_string(record.totalCost))
              << std::setw(8) << (record.isPaid ? "Yes" : "No") << std::setw(12)
              << record.status << std::endl;
  }
  std::cout << std::string(80, '=') << std::endl;
}

void customer::updateBookingStatus(std::string roomID, date checkin,
                                   std::string newStatus) {
  for (auto &record : bookingHistory) {
    if (record.roomID == roomID && record.checkin.day == checkin.day &&
        record.checkin.month == checkin.month &&
        record.checkin.year == checkin.year) {
      record.status = newStatus;
      break;
    }
  }
}

std::vector<booking_record> customer::getBookingHistory() const {
  return bookingHistory;
}

// Book a room
bool customer::bookRoom(hotel &h, std::string roomID, date checkin_date,
                        date checkout_date) {
  room *foundRoom = h.findRoomByNumber(roomID);
  if (!foundRoom) {
    std::cout << "Room not found!\n";
    return false;
  }

  if (!foundRoom->isAvailable()) {
    std::cout << "Room is not available!\n";
    return false;
  }

  // Book the room
  if (foundRoom->book(name, checkin_date, checkout_date)) {
    roomStay = foundRoom;
    setCheckinDate(checkin_date);
    setCheckoutDate(checkout_date);

    // Tạo booking record mới
    booking_record record;
    record.roomID = roomID;
    record.roomTypeName = foundRoom->getTypeName();
    record.checkin = checkin_date;
    record.checkout = checkout_date;

    // Tính toán chi phí (giả sử có method tính số đêm)
    int nights = calculateNightStays();
    record.totalCost = nights * foundRoom->checkPrice();
    record.isPaid = false;
    record.status = "Current";

    // Lấy ngày hiện tại (đơn giản hóa)
    record.bookingDate = {1, 1, 2024};  // Bạn có thể implement getCurrentDate()

    // Thêm vào lịch sử
    addBookingRecord(record);

    std::cout << "Room booked successfully!\n";
    return true;
  }

  return false;
}
// View available rooms in the hotel
void customer::viewAvailableRooms(hotel &h) {
  std::cout << "=== Available Rooms ===" << std::endl;

  try {
    h.displayAllAvailableRooms();
  } catch (const std::exception &e) {
    std::cout << "Error displaying available rooms: " << e.what() << std::endl;
  }

  std::cout << "======================" << std::endl;
}

// Cancel room booking
bool customer::cancelRoom() {
  if (!roomStay) {
    std::cout << "No room to cancel!\n";
    return false;
  }

  // Cập nhật trạng thái trong lịch sử
  updateBookingStatus(roomStay->getID(), checkin, "Cancelled");

  // Cancel room
  if (roomStay->cancel(name)) {
    roomStay = nullptr;
    std::cout << "Room cancelled successfully!\n";
    return true;
  }

  return false;
}

void customer::showBill() {
  std::cout << "=== Bill for " << name << " ===" << std::endl;
  std::cout << "Customer ID: " << id << std::endl;

  if (checkin.day != 0 && checkout.day != 0) {
    std::cout << "Stay Period: " << checkin.day << "/" << checkin.month << "/"
              << checkin.year;
    std::cout << " to " << checkout.day << "/" << checkout.month << "/"
              << checkout.year << std::endl;
    std::cout << "Number of nights: " << calculateNightStays() << std::endl;
  }

  if (discount > 0) {
    int originalBill = bill;
    if (discount < 100) originalBill = bill * 100 / (100 - discount);
    std::cout << "Original Amount: $" << originalBill << std::endl;
    std::cout << "Discount applied: " << discount << "%" << std::endl;
    std::cout << "Discount amount: $" << (originalBill - bill) << std::endl;
  }

  std::cout << "Total Amount: $" << bill << std::endl;
  std::cout << "=========================" << std::endl;
}

bool customer::payBill() {
  if (bill <= 0) {
    std::cout << "No outstanding bill to pay." << std::endl;
    return false;
  }

  std::cout << "Processing payment of $" << bill << " for " << name
            << std::endl;

  char confirm;
  std::cout << "Confirm payment? (y/n): ";
  std::cin >> confirm;

  if (confirm == 'y' || confirm == 'Y') {
    std::cout << "Payment successful!" << std::endl;
    std::cout << "Receipt generated for $" << bill << std::endl;

    std::cout << "\n=== PAYMENT RECEIPT ===" << std::endl;
    std::cout << "Customer: " << name << std::endl;
    std::cout << "Customer ID: " << id << std::endl;
    std::cout << "Amount Paid: $" << bill << std::endl;
    std::cout << "Payment Date: " << __DATE__ << std::endl;
    std::cout << "Status: PAID" << std::endl;
    std::cout << "======================" << std::endl;

    bill = 0;
    roomStay->unlockRoom();
    roomStay = nullptr;
    return true;
  } else {
    std::cout << "Payment cancelled." << std::endl;
    return false;
  }
}

int customer::getDiscount() const { return discount; }

void customer::setDiscount(int new_discount) {
  if (new_discount >= 0 && new_discount <= 100) {
    discount = new_discount;
    std::cout << "Discount set to " << discount << "% for customer " << name
              << std::endl;
  } else {
    std::cout << "Invalid discount percentage. Must be between 0-100."
              << std::endl;
  }
}

int customer::getBill() const { return bill; }

void customer::setBill(int amount) {
  if (amount >= 0) {
    bill = amount;
  } else {
    std::cout << "Invalid bill amount." << std::endl;
  }
}

// customer.cpp
void customer::saveToFile(std::ofstream &out) {
  out << name << "," << phone << "," << email << "," << id << "," << discount
      << "," << bill << "," << checkin.day << "," << checkin.month << ","
      << checkin.year << "," << checkout.day << "," << checkout.month << ","
      << checkout.year << "," << (roomStay ? roomStay->getID() : "None")
      << "\n";
}

void customer::loadFromFile(std::ifstream &in, hotel &h) {
  std::string idStr, discountStr, billStr;
  std::string checkinDay, checkinMonth, checkinYear;
  std::string checkoutDay, checkoutMonth, checkoutYear;
  std::string roomID;

  std::getline(in, name, ',');
  std::getline(in, phone, ',');
  std::getline(in, email, ',');
  std::getline(in, idStr, ',');
  std::getline(in, discountStr, ',');
  std::getline(in, billStr, ',');
  std::getline(in, checkinDay, ',');
  std::getline(in, checkinMonth, ',');
  std::getline(in, checkinYear, ',');
  std::getline(in, checkoutDay, ',');
  std::getline(in, checkoutMonth, ',');
  std::getline(in, checkoutYear, ',');
  std::getline(in, roomID);

  id = std::stoi(idStr);
  discount = std::stoi(discountStr);
  bill = std::stoi(billStr);
  checkin.day = std::stoi(checkinDay);
  checkin.month = std::stoi(checkinMonth);
  checkin.year = std::stoi(checkinYear);
  checkout.day = std::stoi(checkoutDay);
  checkout.month = std::stoi(checkoutMonth);
  checkout.year = std::stoi(checkoutYear);

  if (roomID != "None") {
    try {
      roomStay = h.findRoomByNumber(roomID);
    } catch (...) {
      roomStay = nullptr;
    }
  } else {
    roomStay = nullptr;
  }
}
