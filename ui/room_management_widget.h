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
#include "../include/HotelManagement.h"

class RoomManagementWidget : public QWidget
{
    Q_OBJECT

public:
    explicit RoomManagementWidget(HotelManagementSystem *hotelSystem, QWidget *parent = nullptr);
    
public slots:
    void refreshData();

private slots:
    void onAddRoom();
    void onRemoveRoom();
    void onViewRoomDetails();
    void onSearchRoom();
    void onFilterRooms();
    void onRoomSelectionChanged();

private:
    void setupUI();
    void setupRoomTable();
    void setupControls();
    void setupSearchAndFilter();
    void setupAddRoomSection();
    void setupStyles();
    void connectSignals();
    void populateRoomTable();
    void updateRoomTable();
    
    // UI Components
    QVBoxLayout *m_mainLayout;
    
    // Room table
    QTableWidget *m_roomTable;
    QLabel *m_roomCountLabel;
    
    // Controls
    QGroupBox *m_controlsGroup;
    QPushButton *m_addRoomBtn;
    QPushButton *m_removeRoomBtn;
    QPushButton *m_viewDetailsBtn;
    QPushButton *m_refreshBtn;
    
    // Add room controls
    QGroupBox *m_addRoomGroup;
    QSpinBox *m_floorSpinBox;
    QComboBox *m_roomTypeCombo;
    QPushButton *m_confirmAddBtn;
    
    // Search and filter
    QGroupBox *m_searchGroup;
    QLineEdit *m_searchLineEdit;
    QComboBox *m_filterCombo;
    QPushButton *m_searchBtn;
    QPushButton *m_clearFilterBtn;
    
    // Hotel system reference
    HotelManagementSystem *m_hotelSystem;
};
