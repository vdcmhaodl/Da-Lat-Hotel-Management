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
#include <QMenuBar>
#include <QStatusBar>
#include <QMessageBox>
#include <QInputDialog>
#include <QTextEdit>
#include <QSplitter>
#include <QGroupBox>
#include <QComboBox>
#include <QSpinBox>
#include <QLineEdit>
#include "../include/HotelManagement.h"

class RoomManagementWidget;
class CustomerManagementWidget;
class EmployeeManagementWidget;
class AddCustomerDialog;
class AddEmployeeDialog;

class ManagerWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit ManagerWindow(HotelManagementSystem *hotelSystem, QWidget *parent = nullptr);
    ~ManagerWindow();

private slots:
    void onLogout();
    void onSaveSystem();
    void onLoadSystem();
    void onGenerateReport();
    void onViewStatistics();
    void onViewRevenue();
    void refreshAllData();

private:
    void setupUI();
    void setupMenuBar();
    void setupStatusBar();
    void setupStyles();
    void connectSignals();
    void setupDashboard();
    void setupReports();
    void updateDashboard();
    
    // UI Components
    QWidget *m_centralWidget;
    QTabWidget *m_tabWidget;
    
    // Dashboard
    QWidget *m_dashboardWidget;
    QLabel *m_totalRoomsLabel;
    QLabel *m_availableRoomsLabel;
    QLabel *m_occupiedRoomsLabel;
    QLabel *m_totalCustomersLabel;
    QLabel *m_totalEmployeesLabel;
    QLabel *m_totalRevenueLabel;
    
    // Management widgets
    RoomManagementWidget *m_roomManagement;
    CustomerManagementWidget *m_customerManagement;
    EmployeeManagementWidget *m_employeeManagement;
    
    // Reports
    QWidget *m_reportsWidget;
    QTextEdit *m_reportTextEdit;
    
    // Menu and status
    QMenuBar *m_menuBar;
    QStatusBar *m_statusBar;
    
    // Hotel system reference
    HotelManagementSystem *m_hotelSystem;
};
