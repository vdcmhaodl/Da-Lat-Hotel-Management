#include "customer.h"
#include <iostream>
#include <iomanip>
#include <fstream>

// Default constructor
customer::customer() : person() { discount = 0; }

// Parameterized constructor
customer::customer(std::string name, std::string phone, std::string email,
                   int id, bool gender)
    : person(name, phone, email, id, gender) {
  discount = 0;
}

// Assignment operator
customer &customer::operator=(const customer &other) {
  if (this != &other) {
    person::operator=(other);
    discount = other.discount;
    currentBookings = other.currentBookings;
    bookingHistory = other.bookingHistory;
  }
  return *this;
}

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

int customer::calculateNightStays(date checkin, date checkout) {
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
  std::cout << "Gender " << (gender ? "Male\n" : "Female\n");
  std::cout << "Phone: " << phone << std::endl;
  std::cout << "Email: " << email << std::endl;
  std::cout << "Role: Customer" << std::endl;
  std::cout << "Discount: " << discount << "%" << std::endl;
  std::cout << "Total Outstanding Bill: $" << getTotalBill() << std::endl;
  std::cout << "Current Active Bookings: " << currentBookings.size()
            << std::endl;
  std::cout << "Pass: (DEBUG)" << password << std::endl;
  std::cout << "==============================" << std::endl;
}

// Override getName from person class
std::string customer::getName() { return name; }

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
    // LOCK THE ROOM when booking
    foundRoom->lockRoom();

    // Create current booking
    current_booking currentBooking;
    currentBooking.roomID = roomID;
    currentBooking.roomPtr = foundRoom;
    currentBooking.checkin = checkin_date;
    currentBooking.checkout = checkout_date;

    // Calculate cost
    int nights = calculateNightStays(checkin_date, checkout_date);
    currentBooking.bill = nights * foundRoom->checkPrice();

    // Add to current bookings list
    currentBookings.push_back(currentBooking);

    // Create booking record
    booking_record record;
    record.roomID = roomID;
    record.roomTypeName = foundRoom->getTypeName();
    record.checkin = checkin_date;
    record.checkout = checkout_date;
    record.totalCost = currentBooking.bill;
    record.isPaid = false;
    record.status = "Current";

    // Set booking date (simplified)
    record.bookingDate = {1, 1, 2024};

    // Add to history
    addBookingRecord(record);

    std::cout << "Room booked and locked successfully!\n";
    return true;
  }

  return false;
}

// View available rooms in the hotel
void customer::viewAllRooms(hotel &h) {
  std::cout << "=== All Rooms ===" << std::endl;

  try {
    h.displayAllRooms();
  } catch (const std::exception &e) {
    std::cout << "Error displaying available rooms: " << e.what() << std::endl;
  }

  std::cout << "======================" << std::endl;
}

// Cancel room booking by roomID
bool customer::cancelRoom(std::string roomID) {
  for (auto it = currentBookings.begin(); it != currentBookings.end(); ++it) {
    if (it->roomID == roomID) {
      // Cập nhật trạng thái trong lịch sử
      updateBookingStatus(roomID, it->checkin, "Cancelled");

      // Cancel room
      if (it->roomPtr->cancel(name)) {
        // Remove from current bookings
        currentBookings.erase(it);
        it->roomPtr->unlockRoom();  // Unlock the room
        std::cout << "Room " << roomID << " cancelled successfully!\n";
        return true;
      }
      break;
    }
  }

  std::cout << "Room " << roomID << " not found in current bookings!\n";
  return false;
}

void customer::showCurrentBookings() {
  std::cout << "\n=== CURRENT BOOKINGS FOR " << name << " ===\n";
  std::cout << std::string(70, '=') << std::endl;

  if (currentBookings.empty()) {
    std::cout << "No current bookings found.\n";
    return;
  }

  std::cout << std::left << std::setw(10) << "Room ID" << std::setw(12)
            << "Check-in" << std::setw(12) << "Check-out" << std::setw(10)
            << "Bill" << std::endl;
  std::cout << std::string(70, '-') << std::endl;

  for (const auto &booking : currentBookings) {
    std::cout << std::left << std::setw(10) << booking.roomID << std::setw(12)
              << (std::to_string(booking.checkin.day) + "/" +
                  std::to_string(booking.checkin.month) + "/" +
                  std::to_string(booking.checkin.year))
              << std::setw(12)
              << (std::to_string(booking.checkout.day) + "/" +
                  std::to_string(booking.checkout.month) + "/" +
                  std::to_string(booking.checkout.year))
              << std::setw(10) << ("$" + std::to_string(booking.bill))
              << std::endl;
  }
  std::cout << std::string(70, '=') << std::endl;
  std::cout << "Total Bill: $" << getTotalBill() << std::endl;
}

void customer::showBill() {
  std::cout << "=== Bill for " << name << " ===" << std::endl;
  std::cout << "Customer ID: " << id << std::endl;

  if (currentBookings.empty()) {
    std::cout << "No current bookings found.\n";
    std::cout << "Total Amount: $0" << std::endl;
    std::cout << "=========================" << std::endl;
    return;
  }

  std::cout << "\nCurrent Bookings:\n";
  for (const auto &booking : currentBookings) {
    std::cout << "Room " << booking.roomID << ": ";
    std::cout << booking.checkin.day << "/" << booking.checkin.month << "/"
              << booking.checkin.year;
    std::cout << " to " << booking.checkout.day << "/" << booking.checkout.month
              << "/" << booking.checkout.year;
    std::cout << " - $" << booking.bill << std::endl;
  }

  int totalBill = getTotalBill();
  if (discount > 0) {
    int originalBill = totalBill * 100 / (100 - discount);
    std::cout << "\nOriginal Amount: $" << originalBill << std::endl;
    std::cout << "Discount applied: " << discount << "%" << std::endl;
    std::cout << "Discount amount: $" << (originalBill - totalBill)
              << std::endl;
  }

  std::cout << "\nTotal Amount: $" << totalBill << std::endl;
  std::cout << "=========================" << std::endl;
}

bool customer::payBill(std::string roomID) {
  // Find the specific booking
  for (auto it = currentBookings.begin(); it != currentBookings.end(); ++it) {
    if (it->roomID == roomID) {
      int billAmount = it->bill;

      // Apply discount if any
      if (discount > 0) {
        billAmount = billAmount * (100 - discount) / 100;
      }

      std::cout << "Processing payment of $" << billAmount << " for room "
                << roomID << std::endl;

      char confirm;
      std::cout << "Confirm payment? (y/n): ";
      std::cin >> confirm;

      if (confirm == 'y' || confirm == 'Y') {
        std::cout << "Payment successful!" << std::endl;
        std::cout << "Receipt generated for $" << billAmount << std::endl;

        std::cout << "\n=== PAYMENT RECEIPT ===" << std::endl;
        std::cout << "Customer: " << name << std::endl;
        std::cout << "Customer ID: " << id << std::endl;
        std::cout << "Room ID: " << roomID << std::endl;
        std::cout << "Amount Paid: $" << billAmount << std::endl;
        std::cout << "Payment Date: " << __DATE__ << std::endl;
        std::cout << "Status: PAID" << std::endl;
        std::cout << "======================" << std::endl;

        // Update booking history to paid
        for (auto &record : bookingHistory) {
          if (record.roomID == roomID && record.status == "Current") {
            record.isPaid = true;
            record.status = "Completed";
            break;
          }
        }

        // Unlock room and remove from current bookings
        it->roomPtr->unlockRoom();
        currentBookings.erase(it);
        discount = 0;  // Reset discount after payment
        return true;
      } else {
        std::cout << "Payment cancelled." << std::endl;
        return false;
      }
    }
  }

  std::cout << "Room " << roomID << " not found in current bookings!"
            << std::endl;
  return false;
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

int customer::getTotalBill() const {
  int total = 0;
  for (const auto &booking : currentBookings) {
    total += booking.bill;
  }

  // Apply discount if any
  if (discount > 0) {
    total = total * (100 - discount) / 100;
  }

  return total;
}

std::vector<current_booking> customer::getCurrentBookings() const {
  return currentBookings;
}

// customer.cpp - Updated save/load functions to maintain compatibility with
// existing file format
void customer::saveToFile(std::ofstream &out) {
  // Maintain compatibility with original format:
  // name,phone,email,id,discount,bill,checkin_day,checkin_month,checkin_year,checkout_day,checkout_month,checkout_year,roomStay

  // Calculate total bill for backward compatibility
  int totalBill = getTotalBill();

  // Use first booking dates or default (0,0,0) for backward compatibility
  date firstCheckin = {0, 0, 0};
  date firstCheckout = {0, 0, 0};
  std::string firstRoomID = "None";

  if (!currentBookings.empty()) {
    firstCheckin = currentBookings[0].checkin;
    firstCheckout = currentBookings[0].checkout;
    firstRoomID = currentBookings[0].roomID;
  }

  // Write in original format
  out << name << "," << phone << "," << email << "," << id << "," << discount << "," << password
      << "," << totalBill << "," << firstCheckin.day << ","
      << firstCheckin.month << "," << firstCheckin.year << ","
      << firstCheckout.day << "," << firstCheckout.month << ","
      << firstCheckout.year << "," << firstRoomID;

  // Add extended data for multiple bookings (new format extension)
  out << ",EXTENDED," << currentBookings.size();

  for (const auto &booking : currentBookings) {
    out << "," << booking.roomID << "," << booking.checkin.day << ","
        << booking.checkin.month << "," << booking.checkin.year << ","
        << booking.checkout.day << "," << booking.checkout.month << ","
        << booking.checkout.year << "," << booking.bill;
  }

  out << "\n";
}

void customer::loadFromFile(std::ifstream &in, hotel &h) {
  std::string line;
  std::getline(in, line);

  // Parse the line manually to handle both old and new formats
  std::stringstream ss(line);
  std::string token;
  std::vector<std::string> tokens;

  while (std::getline(ss, token, ',')) {
    tokens.push_back(token);
  }

  if (tokens.size() < 14) {
    // Invalid format
    return;
  }

  // Load basic info (same as original format)
  name = tokens[0];
  phone = tokens[1];
  email = tokens[2];
  id = std::stoi(tokens[3]);
  discount = std::stoi(tokens[4]);
  password = tokens[5];
  // tokens[5] is total bill - we'll recalculate this from bookings

  // Clear current bookings
  currentBookings.clear();

  // Check if this is extended format
  bool isExtendedFormat = false;
  size_t extendedIndex = 14;

  if (tokens.size() > 14 && tokens[14] == "EXTENDED") {
    isExtendedFormat = true;
    extendedIndex = 15;
  }

  if (isExtendedFormat && tokens.size() > extendedIndex) {
    // Load multiple bookings from extended format
    int bookingsCount = std::stoi(tokens[extendedIndex]);
    size_t currentIndex = extendedIndex + 1;

    for (int i = 0; i < bookingsCount && currentIndex + 7 < tokens.size();
         ++i) {
      current_booking booking;
      booking.roomID = tokens[currentIndex];
      booking.checkin.day = std::stoi(tokens[currentIndex + 1]);
      booking.checkin.month = std::stoi(tokens[currentIndex + 2]);
      booking.checkin.year = std::stoi(tokens[currentIndex + 3]);
      booking.checkout.day = std::stoi(tokens[currentIndex + 4]);
      booking.checkout.month = std::stoi(tokens[currentIndex + 5]);
      booking.checkout.year = std::stoi(tokens[currentIndex + 6]);
      booking.bill = std::stoi(tokens[currentIndex + 7]);

      try {
        booking.roomPtr = h.findRoomByNumber(booking.roomID);
        if (booking.roomPtr) {
          currentBookings.push_back(booking);
        }
      } catch (...) {
        // Skip if room not found
      }

      currentIndex += 8;
    }
  } else {
    // Load single booking from original format (backward compatibility)
    std::string roomID = tokens[12];

    if (roomID != "None") {
      current_booking booking;
      booking.roomID = roomID;
      booking.checkin.day = std::stoi(tokens[6]);
      booking.checkin.month = std::stoi(tokens[7]);
      booking.checkin.year = std::stoi(tokens[8]);
      booking.checkout.day = std::stoi(tokens[9]);
      booking.checkout.month = std::stoi(tokens[10]);
      booking.checkout.year = std::stoi(tokens[11]);

      try {
        booking.roomPtr = h.findRoomByNumber(roomID);
        if (booking.roomPtr) {
          // Calculate bill for old format
          int nights = calculateNightStays(booking.checkin, booking.checkout);
          booking.bill = nights * booking.roomPtr->checkPrice();
          currentBookings.push_back(booking);
        }
      } catch (...) {
        // Skip if room not found
      }
    }
  }
}