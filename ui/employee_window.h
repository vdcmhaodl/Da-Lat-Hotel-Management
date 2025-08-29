#pragma once
#include <QMainWindow>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QTabWidget>
#include <QLabel>
#include <QPushButton>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QHeaderView>
#include <QMenuBar>
#include <QStatusBar>
#include <QMessageBox>
#include <QInputDialog>
#include <QTextEdit>
#include <QGroupBox>
#include <QComboBox>
#include <QSpinBox>
#include <QLineEdit>
#include <QDateEdit>
#include "../include/HotelManagement.h"

class EmployeeWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit EmployeeWindow(HotelManagementSystem *hotelSystem, int employeeId, QWidget *parent = nullptr);
    ~EmployeeWindow();

private slots:
    void onLogout();
    void onRefreshData();
    void onViewRooms();
    void onBookRoomForCustomer();
    void onLockRoom();
    void onUnlockRoom();
    void onGiveDiscount();
    void onViewBookingHistory();
    void onViewCustomerHistory();
    void onViewRoomHistory();
    void onAvailableRoomSelected();
    void onCustomerSelected();
    void refreshAvailableRooms();
    void onViewAllCustomers();
    void onViewRoomDetails();
    void loadCustomersData();

private:
    void setupUI();
    void setupMenuBar();
    void setupStatusBar();
    void setupDashboard();
    void setupBookingSection();
    void setupRoomView();
    void setupCustomerManagement();
    void setupReports();
    void setupStyles();
    void connectSignals();
    void updateDashboard();
    
    // UI Components
    QWidget *m_centralWidget;
    QTabWidget *m_tabWidget;
    
    // Dashboard
    QWidget *m_dashboardWidget;
    QLabel *m_welcomeLabel;
    QLabel *m_availableRoomsLabel;
    QLabel *m_todayBookingsLabel;
    QLabel *m_totalCustomersLabel;
    QLabel *m_occupiedRoomsLabel;
    
    // Booking section
    QWidget *m_bookingWidget;
    QLineEdit *m_customerIdEdit;
    QLineEdit *m_roomIdEdit;
    QDateEdit *m_checkinDateEdit;
    QDateEdit *m_checkoutDateEdit;
    QPushButton *m_bookRoomBtn;
    QTableWidget *m_availableRoomsTable;
    
    // Room table
    QTableWidget *m_roomTable;
    QLabel *m_roomCountLabel;
    
    // Customer management
    QWidget *m_customerWidget;
    QTableWidget *m_customerTable;
    
    // Reports
    QWidget *m_reportsWidget;
    QTextEdit *m_reportTextEdit;
    
    // Menu and status
    QMenuBar *m_menuBar;
    QStatusBar *m_statusBar;
    
    // Hotel system reference and employee info
    HotelManagementSystem *m_hotelSystem;
    int m_employeeId;
};
