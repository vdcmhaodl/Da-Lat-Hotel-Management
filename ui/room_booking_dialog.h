#ifndef ROOM_BOOKING_DIALOG_H
#define ROOM_BOOKING_DIALOG_H

#include <QDialog>
#include <QLineEdit>
#include <QComboBox>
#include <QDateEdit>
#include <QSpinBox>
#include <QTextEdit>
#include <QPushButton>
#include <QDate>

// Forward declaration
class Hotel;

#include "../include/hotel.h"

struct BookingInfo {
    QString customerId;
    QString roomType;
    QDate checkInDate;
    QDate checkOutDate;
    int numberOfGuests;
    QString specialRequests;
};

class RoomBookingDialog : public QDialog {
    Q_OBJECT

public:
    explicit RoomBookingDialog(Hotel* hotel, QWidget *parent = nullptr);

private slots:
    void onBookRoom();
    void onDateChanged();

private:
    void setupUI();
    void connectSignals();
    void loadRoomTypes();
    double getRoomPrice(const QString& roomType);
    void processBooking(const BookingInfo& booking);
    QString generateBookingId();

    Hotel* hotel;
    
    QLineEdit* customerIdEdit;
    QComboBox* roomTypeCombo;
    QDateEdit* checkInDate;
    QDateEdit* checkOutDate;
    QSpinBox* guestsSpinBox;
    QTextEdit* specialRequestsEdit;
    QPushButton* bookButton;
    QPushButton* cancelButton;
};

#endif // ROOM_BOOKING_DIALOG_H
