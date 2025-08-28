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

class CustomerWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit CustomerWindow(HotelManagementSystem *hotelSystem, customer *customer, QWidget *parent = nullptr);
    ~CustomerWindow();

private slots:
    void onLogout();
    void onRefreshData();
    void onViewAllRooms();
    void onBookRoom();
    void onCancelRoom();
    void onViewBookingHistory();
    void onViewCurrentBookings();
    void onShowBill();
    void onPayBill();
    void onViewPersonalInfo();

private:
    void setupUI();
    void setupMenuBar();
    void setupStatusBar();
    void setupDashboard();
    void setupBookingSection();
    void setupMyBookingsSection();
    void setupBillingSection();
    void setupPersonalInfoSection();
    void setupStyles();
    void connectSignals();
    void updateDashboard();
    void refreshRoomTable();
    void refreshBookingsTable();
    void loadPersonalInfoSafely();
    
    // UI Components
    QWidget *m_centralWidget;
    QTabWidget *m_tabWidget;
    
    // Dashboard
    QWidget *m_dashboardWidget;
    QLabel *m_welcomeLabel;
    QLabel *m_currentBookingsLabel;
    QLabel *m_totalBillLabel;
    QLabel *m_discountLabel;
    
    // Booking section
    QWidget *m_bookingWidget;
    QTableWidget *m_roomTable;
    QLineEdit *m_roomIdEdit;
    QDateEdit *m_checkinDateEdit;
    QDateEdit *m_checkoutDateEdit;
    QPushButton *m_bookRoomBtn;
    
    // My bookings section
    QWidget *m_myBookingsWidget;
    QTableWidget *m_bookingsTable;
    QPushButton *m_cancelBookingBtn;
    QPushButton *m_viewHistoryBtn;
    
    // Billing section
    QWidget *m_billingWidget;
    QTextEdit *m_billTextEdit;
    QLineEdit *m_payRoomIdEdit;
    QPushButton *m_showBillBtn;
    QPushButton *m_payBillBtn;
    
    // Personal info
    QWidget *m_personalInfoWidget;
    QTextEdit *m_personalInfoText;
    
    // Menu and status
    QMenuBar *m_menuBar;
    QStatusBar *m_statusBar;
    
    // Hotel system reference and customer info
    HotelManagementSystem *m_hotelSystem;
    customer *m_customer;
};
