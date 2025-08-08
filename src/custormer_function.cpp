#include "customer.h"
#include <iostream>
#include <iomanip>
#include <fstream> 

// Default constructor
customer::customer() : person()
{
  discount = 0;
  bill = 0;
  // Initialize dates to default values (assuming date has day, month, year)
  checkin = {0, 0, 0};
  checkout = {0, 0, 0};
}

// Parameterized constructor
customer::customer(std::string name, std::string phone, std::string email,
                   int id)
    : person(name, phone, email, id)
{
  discount = 0;
  bill = 0;
  // Initialize dates to default values
  checkin = {0, 0, 0};
  checkout = {0, 0, 0};
}

// Assignment operator
customer &customer::operator=(const customer &other)
{
  if (this != &other)
  {
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

bool isLeap(int year)
{
  return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

int daysInMonth(int month, int year)
{
  static const int days[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
  if (month == 2 && isLeap(year))
    return 29;
  return days[month - 1];
}

// Helper function to count total days since 01/01/0000
int countDays(const date &d)
{
  int days = d.day;

  for (int m = 1; m < d.month; ++m)
    days += daysInMonth(m, d.year);

  for (int y = 0; y < d.year; ++y)
    days += isLeap(y) ? 366 : 365;

  return days;
}

int customer::calculateNightStays()
{
  int checkinDays = countDays(checkin);
  int checkoutDays = countDays(checkout);

  if (checkoutDays <= checkinDays)
    return 0;

  return checkoutDays - checkinDays;
  return 0;
}

// Override showInfo from person class
void customer::showInfo()
{
  std::cout << "=== Customer Information ===" << std::endl;
  std::cout << "ID: " << id << std::endl;
  std::cout << "Name: " << name << std::endl;
  std::cout << "Phone: " << phone << std::endl;
  std::cout << "Email: " << email << std::endl;
  std::cout << "Role: Customer" << std::endl;
  std::cout << "Discount: " << discount << "%" << std::endl;
  std::cout << "Current Bill: $" << bill << std::endl;

  if (checkin.day != 0)
  {
    std::cout << "Check-in Date: " << checkin.day << "/" << checkin.month << "/"
              << checkin.year << std::endl;
  }
  if (checkout.day != 0)
  {
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

// Book a room
bool customer::bookRoom(hotel &h, std::string roomID, date checkin_date,
                        date checkout_date)
{
  try
  {
    // Find the room in hotel
    room &selectedRoom = h.findRoomByNumber(roomID);

    // Check if room is available
    if (!selectedRoom.isAvailable())
    {
      std::cout << "Room " << roomID << " is not available for booking."
                << std::endl;
      return false;
    }

    // Set booking dates
    setCheckinDate(checkin_date);
    setCheckoutDate(checkout_date);

    // Calculate nights and bill
    int nights = calculateNightStays();
    if (nights <= 0)
    {
      std::cout << "Invalid booking dates." << std::endl;
      return false;
    }

    // Calculate bill based on estimated room price and nights
    // Since we can't access room price directly, use estimated pricing
    double roomPrice = 100.0; // Default base price per night

    // Simple pricing logic - you can adjust based on room naming convention
    if (roomID.find("VIP") != std::string::npos ||
        roomID.find("vip") != std::string::npos)
    {
      if (roomID.find("Double") != std::string::npos ||
          roomID.find("double") != std::string::npos)
      {
        roomPrice = 200.0; // Double VIP
      }
      else
      {
        roomPrice = 150.0; // Single VIP
      }
    }
    else
    {
      if (roomID.find("Double") != std::string::npos ||
          roomID.find("double") != std::string::npos)
      {
        roomPrice = 120.0; // Double Normal
      }
      else
      {
        roomPrice = 80.0; // Single Normal
      }
    }

    bill = static_cast<int>(roomPrice * nights);

    // Apply discount if any
    if (discount > 0)
    {
      bill = bill - (bill * discount / 100);
    }

    std::cout << "Room " << roomID << " booked successfully for " << name
              << std::endl;
    std::cout << "Check-in: " << checkin_date.day << "/" << checkin_date.month
              << "/" << checkin_date.year << std::endl;
    std::cout << "Check-out: " << checkout_date.day << "/"
              << checkout_date.month << "/" << checkout_date.year << std::endl;
    std::cout << "Total bill: $" << bill << " for " << nights << " nights"
              << std::endl;
    roomStay = &selectedRoom;
    selectedRoom.lockRoom();
    return true;
  }
  catch (const std::exception &e)
  {
    std::cout << "Error booking room: " << e.what() << std::endl;
    return false;
  }
}

// View available rooms in the hotel
void customer::viewAvailableRooms(hotel &h)
{
  std::cout << "=== Available Rooms ===" << std::endl;

  try
  {
    h.displayAllAvailableRooms();
  }
  catch (const std::exception &e)
  {
    std::cout << "Error displaying available rooms: " << e.what() << std::endl;
  }

  std::cout << "======================" << std::endl;
}

// Cancel room booking
bool customer::cancelRoom()
{
  try
  {
    // Find the room

    std::cout << "Cancelling room " << roomStay->getID() << " booking for " << name
              << std::endl;

    checkin = {0, 0, 0};
    checkout = {0, 0, 0};
    bill = 0;

    std::cout << "Room " << roomStay->getID() << " booking cancelled successfully for "
              << name << std::endl;
    roomStay = nullptr;
    return true;
  }
  catch (const std::exception &e)
  {
    std::cout << "Error cancelling room: " << e.what() << std::endl;
    return false;
  }
}

void customer::showBill()
{
  std::cout << "=== Bill for " << name << " ===" << std::endl;
  std::cout << "Customer ID: " << id << std::endl;

  if (checkin.day != 0 && checkout.day != 0)
  {
    std::cout << "Stay Period: " << checkin.day << "/" << checkin.month << "/"
              << checkin.year;
    std::cout << " to " << checkout.day << "/" << checkout.month << "/"
              << checkout.year << std::endl;
    std::cout << "Number of nights: " << calculateNightStays() << std::endl;
  }

  if (discount > 0)
  {
    int originalBill = bill;
    if (discount < 100)
      originalBill = bill * 100 / (100 - discount);
    std::cout << "Original Amount: $" << originalBill << std::endl;
    std::cout << "Discount applied: " << discount << "%" << std::endl;
    std::cout << "Discount amount: $" << (originalBill - bill) << std::endl;
  }

  std::cout << "Total Amount: $" << bill << std::endl;
  std::cout << "=========================" << std::endl;
}

bool customer::payBill()
{
  if (bill <= 0)
  {
    std::cout << "No outstanding bill to pay." << std::endl;
    return false;
  }

  std::cout << "Processing payment of $" << bill << " for " << name
            << std::endl;

  char confirm;
  std::cout << "Confirm payment? (y/n): ";
  std::cin >> confirm;

  if (confirm == 'y' || confirm == 'Y')
  {
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
  }
  else
  {
    std::cout << "Payment cancelled." << std::endl;
    return false;
  }
}

int customer::getDiscount() const { return discount; }

void customer::setDiscount(int new_discount)
{
  if (new_discount >= 0 && new_discount <= 100)
  {
    discount = new_discount;
    std::cout << "Discount set to " << discount << "% for customer " << name
              << std::endl;
  }
  else
  {
    std::cout << "Invalid discount percentage. Must be between 0-100."
              << std::endl;
  }
}

int customer::getBill() const { return bill; }

void customer::setBill(int amount)
{
  if (amount >= 0)
  {
    bill = amount;
  }
  else
  {
    std::cout << "Invalid bill amount." << std::endl;
  }
}

// customer.cpp
void customer::saveToFile(std::ofstream& out) {
    out << name << " " << phone << " " << email << " " << id << " "
        << discount << " " << bill << " "
        << checkin.day << " " << checkin.month << " " << checkin.year << " "
        << checkout.day << " " << checkout.month << " " << checkout.year << " "
        << "None" << "\n";
    // include later, it is the room information
   // out << (roomStay ? roomStay->getID() : "None") << "\n";
}

void customer::loadFromFile(std::ifstream& in, hotel& h) {
    std::string roomID;
    in >> name >> phone >> email >> id >> discount >> bill;
    in >> checkin.day >> checkin.month >> checkin.year;
    in >> checkout.day >> checkout.month >> checkout.year;
    in >> roomID;

    if (roomID != "None") {
        try {
            roomStay = &h.findRoomByNumber(roomID);
        } catch (...) {
            roomStay = nullptr;
        }
    }
}
