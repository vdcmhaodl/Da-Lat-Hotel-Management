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
#include <QDoubleSpinBox>
#include "../include/HotelManagement.h"

class EmployeeManagementWidget : public QWidget
{
    Q_OBJECT

public:
    explicit EmployeeManagementWidget(HotelManagementSystem *hotelSystem, QWidget *parent = nullptr);
    
public slots:
    void refreshData();

private slots:
    void onHireEmployee();
    void onFireEmployee();
    void onViewEmployeeDetails();
    void onSearchEmployee();
    void onFilterEmployees();
    void onEmployeeSelectionChanged();

private:
    void setupUI();
    void setupEmployeeTable();
    void setupControls();
    void setupSearchAndFilter();
    void setupHireEmployeeSection();
    void setupStyles();
    void connectSignals();
    void populateEmployeeTable();
    
    // UI Components
    QVBoxLayout *m_mainLayout;
    
    // Employee table
    QTableWidget *m_employeeTable;
    QLabel *m_employeeCountLabel;
    
    // Controls
    QGroupBox *m_controlsGroup;
    QPushButton *m_hireEmployeeBtn;
    QPushButton *m_fireEmployeeBtn;
    QPushButton *m_viewDetailsBtn;
    QPushButton *m_refreshBtn;
    
    // Hire employee controls
    QGroupBox *m_hireEmployeeGroup;
    QLineEdit *m_nameLineEdit;
    QLineEdit *m_phoneLineEdit;
    QLineEdit *m_emailLineEdit;
    QComboBox *m_genderCombo;
    QDoubleSpinBox *m_salarySpinBox;
    QLineEdit *m_positionLineEdit;
    QPushButton *m_confirmHireBtn;
    
    // Search and filter
    QGroupBox *m_searchGroup;
    QLineEdit *m_searchLineEdit;
    QComboBox *m_filterCombo;
    QPushButton *m_searchBtn;
    QPushButton *m_clearFilterBtn;
    
    // Hotel system reference
    HotelManagementSystem *m_hotelSystem;
};
