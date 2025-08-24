#include "customer.h"
#include <iostream>
#include <iomanip>
#include <fstream>

// Default constructor
<<<<<<< Updated upstream
customer::customer() : person() {
  discount = 0;
  bookedRooms.clear();
}
=======
customer::customer() : person() { discount = 0; }
>>>>>>> Stashed changes

// Parameterized constructor
customer::customer(std::string name, std::string phone, std::string email,
                   int id)
    : person(name, phone, email, id) {
  discount = 0;
<<<<<<< Updated upstream
  bookedRooms.clear();
=======
>>>>>>> Stashed changes
}

// Assignment operator
customer &customer::operator=(const customer &other) {
  if (this != &other) {
    person::operator=(other);
    discount = other.discount;
<<<<<<< Updated upstream
    bookedRooms = other.bookedRooms;
=======
    currentBookings = other.currentBookings;
    bookingHistory = other.bookingHistory;
>>>>>>> Stashed changes
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
  std::cout << "Phone: " << phone << std::endl;
  std::cout << "Email: " << email << std::endl;
  std::cout << "Role: Customer" << std::endl;
  std::cout << "Discount: " << discount << "%" << std::endl;
<<<<<<< Updated upstream
  std::cout << "Total Bill: $" << getTotalBill() << std::endl;
  std::cout << "Number of Booked Rooms: " << bookedRooms.size() << std::endl;
=======
  std::cout << "Total Outstanding Bill: $" << getTotalBill() << std::endl;
  std::cout << "Current Active Bookings: " << currentBookings.size()
            << std::endl;
>>>>>>> Stashed changes
  std::cout << "==============================" << std::endl;
}

// Override getName from person class
std::string customer::getName() { return name; }

// Override getID from person class
int customer::getID() const { return id; }

// Book a room - now supports multiple bookings
bool customer::bookRoom(hotel &h, std::string roomID, date checkin_date,
                        date checkout_date) {
  try {
    // Find the room in hotel
    room *selectedRoom = h.findRoomByNumber(roomID);

    if (selectedRoom == nullptr) {
      std::cout << "Room " << roomID << " is invalid." << std::endl;
      return false;
    }

<<<<<<< Updated upstream
    // Check if customer already booked this room
    if (findBookedRoom(roomID) != nullptr) {
      std::cout << "You have already booked room " << roomID << std::endl;
      return false;
    }

    // Check if room is available
    if (!selectedRoom->isAvailable()) {
      std::cout << "Room " << roomID << " is not available for booking."
                << std::endl;
      return false;
    }

    // Calculate nights and bill
    int nights = calculateNightStays(checkin_date, checkout_date);
    if (nights <= 0) {
      std::cout << "Invalid booking dates." << std::endl;
      return false;
    }

    // Calculate bill based on room pricing
    double roomPrice = 100.0;  // Default base price per night

    // Simple pricing logic based on room ID
    if (roomID.find("VIP") != std::string::npos ||
        roomID.find("vip") != std::string::npos) {
      if (roomID.find("Double") != std::string::npos ||
          roomID.find("double") != std::string::npos) {
        roomPrice = 200.0;  // Double VIP
      } else {
        roomPrice = 150.0;  // Single VIP
      }
    } else {
      if (roomID.find("Double") != std::string::npos ||
          roomID.find("double") != std::string::npos) {
        roomPrice = 120.0;  // Double Normal
      } else {
        roomPrice = 80.0;  // Single Normal
      }
    }
=======
  // Book the room
  if (foundRoom->book(name, checkin_date, checkout_date)) {
    // Tạo current booking
    current_booking currentBooking;
    currentBooking.roomID = roomID;
    currentBooking.roomPtr = foundRoom;
    currentBooking.checkin = checkin_date;
    currentBooking.checkout = checkout_date;

    // Tính toán chi phí
    int nights = calculateNightStays(checkin_date, checkout_date);
    currentBooking.bill = nights * foundRoom->checkPrice();

    // Thêm vào danh sách current bookings
    currentBookings.push_back(currentBooking);

    // Tạo booking record mới
    booking_record record;
    record.roomID = roomID;
    record.roomTypeName = foundRoom->getTypeName();
    record.checkin = checkin_date;
    record.checkout = checkout_date;
    record.totalCost = currentBooking.bill;
    record.isPaid = false;
    record.status = "Current";

    // Lấy ngày hiện tại (đơn giản hóa)
    record.bookingDate = {1, 1, 2024};
>>>>>>> Stashed changes

    int bill = static_cast<int>(roomPrice * nights);

    // Apply discount if any
    if (discount > 0) {
      bill = bill - (bill * discount / 100);
    }

    // Create booked room entry
    BookedRoom newBooking;
    newBooking.roomID = roomID;
    newBooking.roomPtr = selectedRoom;
    newBooking.checkin = checkin_date;
    newBooking.checkout = checkout_date;
    newBooking.bill = bill;
    newBooking.nightStays = nights;

    // Add to booked rooms list
    bookedRooms.push_back(newBooking);

    // Lock the room and set guest
    selectedRoom->lockRoom();
    selectedRoom->setGuest(std::to_string(id));

    std::cout << "Room " << roomID << " booked successfully for " << name
              << std::endl;
    std::cout << "Check-in: " << checkin_date.day << "/" << checkin_date.month
              << "/" << checkin_date.year << std::endl;
    std::cout << "Check-out: " << checkout_date.day << "/"
              << checkout_date.month << "/" << checkout_date.year << std::endl;
    std::cout << "Bill for this room: $" << bill << " for " << nights
              << " nights" << std::endl;

    return true;
  } catch (const std::exception &e) {
    std::cout << "Error booking room: " << e.what() << std::endl;
    return false;
  }
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

<<<<<<< Updated upstream
// Cancel room booking - now requires room ID
bool customer::cancelRoom(std::string roomID) {
  try {
    auto it = std::find_if(bookedRooms.begin(), bookedRooms.end(),
                           [&roomID](const BookedRoom &booking) {
                             return booking.roomID == roomID;
                           });

    if (it != bookedRooms.end()) {
      std::cout << "Cancelling room " << roomID << " booking for " << name
                << std::endl;

      // Unlock the room
      it->roomPtr->unlockRoom();

      // Remove from booked rooms list
      bookedRooms.erase(it);

      std::cout << "Room " << roomID << " booking cancelled successfully for "
                << name << std::endl;
      return true;
    } else {
      std::cout << "Room " << roomID << " is not booked by " << name
                << std::endl;
      return false;
    }
  } catch (const std::exception &e) {
    std::cout << "Error cancelling room: " << e.what() << std::endl;
    return false;
  }
=======
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
        std::cout << "Room " << roomID << " cancelled successfully!\n";
        return true;
      }
      break;
    }
  }

  std::cout << "Room " << roomID << " not found in current bookings!\n";
  return false;
>>>>>>> Stashed changes
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
  std::cout << "=== Bills for " << name << " ===" << std::endl;
  std::cout << "Customer ID: " << id << std::endl;

<<<<<<< Updated upstream
  if (bookedRooms.empty()) {
    std::cout << "No rooms booked." << std::endl;
  } else {
    int totalBill = 0;
    for (const auto &booking : bookedRooms) {
      std::cout << "\n--- Room " << booking.roomID << " ---" << std::endl;
      std::cout << "Stay Period: " << booking.checkin.day << "/"
                << booking.checkin.month << "/" << booking.checkin.year;
      std::cout << " to " << booking.checkout.day << "/"
                << booking.checkout.month << "/" << booking.checkout.year
                << std::endl;
      std::cout << "Number of nights: " << booking.nightStays << std::endl;

      if (discount > 0) {
        int originalBill = booking.bill * 100 / (100 - discount);
        std::cout << "Original Amount: $" << originalBill << std::endl;
        std::cout << "Discount applied: " << discount << "%" << std::endl;
        std::cout << "Discount amount: $" << (originalBill - booking.bill)
                  << std::endl;
      }

      std::cout << "Amount for this room: $" << booking.bill << std::endl;
      totalBill += booking.bill;
    }
    std::cout << "\n=== TOTAL BILL: $" << totalBill << " ===" << std::endl;
  }
  std::cout << "================================" << std::endl;
}

bool customer::payBill(std::string roomID) {
  BookedRoom *booking = findBookedRoom(roomID);

  if (booking == nullptr) {
    std::cout << "Room " << roomID << " is not booked by " << name << std::endl;
    return false;
  }

  if (booking->bill <= 0) {
    std::cout << "No outstanding bill for room " << roomID << std::endl;
    return false;
  }

  std::cout << "Processing payment of $" << booking->bill << " for room "
            << roomID << " (" << name << ")" << std::endl;

  char confirm;
  std::cout << "Confirm payment? (y/n): ";
  std::cin >> confirm;

  if (confirm == 'y' || confirm == 'Y') {
    std::cout << "Payment successful!" << std::endl;
    std::cout << "Receipt generated for $" << booking->bill << std::endl;

    std::cout << "\n=== PAYMENT RECEIPT ===" << std::endl;
    std::cout << "Customer: " << name << std::endl;
    std::cout << "Customer ID: " << id << std::endl;
    std::cout << "Room: " << roomID << std::endl;
    std::cout << "Amount Paid: $" << booking->bill << std::endl;
    std::cout << "Payment Date: " << __DATE__ << std::endl;
    std::cout << "Status: PAID" << std::endl;
    std::cout << "======================" << std::endl;

    // Unlock the room
    booking->roomPtr->unlockRoom();

    // Remove the room from booked rooms list
    auto it = std::find_if(
        bookedRooms.begin(), bookedRooms.end(),
        [&roomID](const BookedRoom &b) { return b.roomID == roomID; });
    if (it != bookedRooms.end()) {
      bookedRooms.erase(it);
    }

    return true;
  } else {
    std::cout << "Payment cancelled." << std::endl;
    return false;
  }
=======
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
>>>>>>> Stashed changes
}

void customer::viewBookedRooms() {
  std::cout << "=== Booked Rooms for " << name << " ===" << std::endl;

  if (bookedRooms.empty()) {
    std::cout << "No rooms currently booked." << std::endl;
  } else {
    for (const auto &booking : bookedRooms) {
      std::cout << "Room ID: " << booking.roomID << std::endl;
      std::cout << "Check-in: " << booking.checkin.day << "/"
                << booking.checkin.month << "/" << booking.checkin.year
                << std::endl;
      std::cout << "Check-out: " << booking.checkout.day << "/"
                << booking.checkout.month << "/" << booking.checkout.year
                << std::endl;
      std::cout << "Nights: " << booking.nightStays << std::endl;
      std::cout << "Bill: $" << booking.bill << std::endl;
      std::cout << "-------------------" << std::endl;
    }
  }
  std::cout << "=================================" << std::endl;
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
<<<<<<< Updated upstream
  for (const auto &booking : bookedRooms) {
    total += booking.bill;
  }
  return total;
=======
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
>>>>>>> Stashed changes
}

BookedRoom *customer::findBookedRoom(std::string roomID) {
  auto it = std::find_if(bookedRooms.begin(), bookedRooms.end(),
                         [&roomID](const BookedRoom &booking) {
                           return booking.roomID == roomID;
                         });

  return (it != bookedRooms.end()) ? &(*it) : nullptr;
}

// Updated save/load functions
void customer::saveToFile(std::ofstream &out) {
  out << name << "," << phone << "," << email << "," << id << "," << discount
<<<<<<< Updated upstream
      << "," << bookedRooms.size() << ",";

  // Save each booked room
  for (const auto &booking : bookedRooms) {
    out << booking.roomID << "," << booking.checkin.day << ","
        << booking.checkin.month << "," << booking.checkin.year << ","
        << booking.checkout.day << "," << booking.checkout.month << ","
        << booking.checkout.year << "," << booking.bill << ","
        << booking.nightStays << ",";
  }
=======
      << ",";

  // Save number of current bookings
  out << currentBookings.size() << ",";

  // Save each current booking
  for (const auto &booking : currentBookings) {
    out << booking.roomID << "," << booking.checkin.day << ","
        << booking.checkin.month << "," << booking.checkin.year << ","
        << booking.checkout.day << "," << booking.checkout.month << ","
        << booking.checkout.year << "," << booking.bill << ",";
  }

>>>>>>> Stashed changes
  out << "\n";
}

void customer::loadFromFile(std::ifstream &in, hotel &h) {
<<<<<<< Updated upstream
  std::string idStr, discountStr, numRoomsStr;
=======
  std::string idStr, discountStr, bookingsCountStr;
>>>>>>> Stashed changes

  std::getline(in, name, ',');
  std::getline(in, phone, ',');
  std::getline(in, email, ',');
  std::getline(in, idStr, ',');
  std::getline(in, discountStr, ',');
<<<<<<< Updated upstream
  std::getline(in, numRoomsStr, ',');

  id = std::stoi(idStr);
  discount = std::stoi(discountStr);
  int numRooms = std::stoi(numRoomsStr);

  // Load each booked room
  for (int i = 0; i < numRooms; i++) {
    BookedRoom booking;
    std::string checkinDay, checkinMonth, checkinYear;
    std::string checkoutDay, checkoutMonth, checkoutYear;
    std::string billStr, nightsStr;

    std::getline(in, booking.roomID, ',');
    std::getline(in, checkinDay, ',');
    std::getline(in, checkinMonth, ',');
    std::getline(in, checkinYear, ',');
    std::getline(in, checkoutDay, ',');
    std::getline(in, checkoutMonth, ',');
    std::getline(in, checkoutYear, ',');
    std::getline(in, billStr, ',');
    std::getline(in, nightsStr, ',');

    booking.checkin.day = std::stoi(checkinDay);
    booking.checkin.month = std::stoi(checkinMonth);
    booking.checkin.year = std::stoi(checkinYear);
    booking.checkout.day = std::stoi(checkoutDay);
    booking.checkout.month = std::stoi(checkoutMonth);
    booking.checkout.year = std::stoi(checkoutYear);
    booking.bill = std::stoi(billStr);
    booking.nightStays = std::stoi(nightsStr);

    try {
      booking.roomPtr = h.findRoomByNumber(booking.roomID);
      if (booking.roomPtr != nullptr) {
        bookedRooms.push_back(booking);
      }
    } catch (...) {
      // Skip this booking if room not found
=======
  std::getline(in, bookingsCountStr, ',');

  id = std::stoi(idStr);
  discount = std::stoi(discountStr);
  int bookingsCount = std::stoi(bookingsCountStr);

  // Load current bookings
  currentBookings.clear();
  for (int i = 0; i < bookingsCount; ++i) {
    std::string roomID, checkinDay, checkinMonth, checkinYear;
    std::string checkoutDay, checkoutMonth, checkoutYear, billStr;

    std::getline(in, roomID, ',');
    std::getline(in, checkinDay, ',');
    std::getline(in, checkinMonth, ',');
    std::getline(in, checkinYear, ',');
    std::getline(in, checkoutDay, ',');
    std::getline(in, checkoutMonth, ',');
    std::getline(in, checkoutYear, ',');

    if (i == bookingsCount - 1) {
      std::getline(in, billStr);  // Last one doesn't have comma
    } else {
      std::getline(in, billStr, ',');
    }

    current_booking booking;
    booking.roomID = roomID;
    booking.checkin = {std::stoi(checkinDay), std::stoi(checkinMonth),
                       std::stoi(checkinYear)};
    booking.checkout = {std::stoi(checkoutDay), std::stoi(checkoutMonth),
                        std::stoi(checkoutYear)};
    booking.bill = std::stoi(billStr);

    try {
      booking.roomPtr = h.findRoomByNumber(roomID);
      if (booking.roomPtr) {
        currentBookings.push_back(booking);
      }
    } catch (...) {
      // Skip if room not found
>>>>>>> Stashed changes
    }
  }
}