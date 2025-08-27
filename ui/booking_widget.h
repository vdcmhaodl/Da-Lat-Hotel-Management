#pragma once
#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QDateEdit>
#include <QComboBox>
#include <QTableWidget>
#include <QHeaderView>
#include <QGroupBox>
#include <QMessageBox>
#include "../include/HotelManagement.h"

class BookingWidget : public QWidget
{
    Q_OBJECT

public:
    explicit BookingWidget(HotelManagementSystem *hotelSystem, QWidget *parent = nullptr);
    
    void setCustomer(customer *customer);
    void setEmployee(bool isEmployee);

public slots:
    void refreshData();

private slots:
    void onBookRoom();
    void onCancelBooking();
    void onRoomSelectionChanged();

private:
    void setupUI();
    void setupBookingForm();
    void setupAvailableRooms();
    void setupBookingsList();
    void setupStyles();
    void connectSignals();
    void populateAvailableRooms();
    void populateBookingsList();
    
    // UI Components
    QVBoxLayout *m_mainLayout;
    
    // Booking form
    QGroupBox *m_bookingFormGroup;
    QLineEdit *m_customerIdEdit;
    QLineEdit *m_roomIdEdit;
    QDateEdit *m_checkinDateEdit;
    QDateEdit *m_checkoutDateEdit;
    QPushButton *m_bookRoomBtn;
    
    // Available rooms
    QGroupBox *m_availableRoomsGroup;
    QTableWidget *m_roomsTable;
    
    // Current bookings
    QGroupBox *m_bookingsGroup;
    QTableWidget *m_bookingsTable;
    QPushButton *m_cancelBookingBtn;
    
    // Hotel system and user info
    HotelManagementSystem *m_hotelSystem;
    customer *m_customer;
    bool m_isEmployee;
};
