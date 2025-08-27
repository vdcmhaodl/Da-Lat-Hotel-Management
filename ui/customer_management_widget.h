#pragma once
#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QComboBox>
#include <QSpinBox>
#include <QGroupBox>
#include <QMessageBox>
#include <QInputDialog>
#include <QHeaderView>
#include <QTextEdit>
#include <QDialog>
#include "../include/HotelManagement.h"

class CustomerManagementWidget : public QWidget
{
    Q_OBJECT

public:
    explicit CustomerManagementWidget(HotelManagementSystem *hotelSystem, QWidget *parent = nullptr);
    
public slots:
    void refreshData();

private slots:
    void onAddCustomer();
    void onRemoveCustomer();
    void onViewCustomerDetails();
    void onViewBookingHistory();
    void onGiveDiscount();
    void onSearchCustomer();
    void onFilterCustomers();
    void onCustomerSelectionChanged();

private:
    void setupUI();
    void setupCustomerTable();
    void setupControls();
    void setupSearchAndFilter();
    void setupStyles();
    void connectSignals();
    void populateCustomerTable();
    
    // UI Components
    QVBoxLayout *m_mainLayout;
    
    // Customer table
    QTableWidget *m_customerTable;
    QLabel *m_customerCountLabel;
    
    // Controls
    QGroupBox *m_controlsGroup;
    QPushButton *m_addCustomerBtn;
    QPushButton *m_removeCustomerBtn;
    QPushButton *m_viewDetailsBtn;
    QPushButton *m_viewHistoryBtn;
    QPushButton *m_giveDiscountBtn;
    QPushButton *m_refreshBtn;
    
    // Search and filter
    QGroupBox *m_searchGroup;
    QLineEdit *m_searchLineEdit;
    QComboBox *m_filterCombo;
    QPushButton *m_searchBtn;
    QPushButton *m_clearFilterBtn;
    
    // Hotel system reference
    HotelManagementSystem *m_hotelSystem;
};
