#include "room_booking_dialog.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFormLayout>
#include <QMessageBox>
#include <QDate>

RoomBookingDialog::RoomBookingDialog(Hotel* hotel, QWidget *parent)
    : QDialog(parent), hotel(hotel) {
    setWindowTitle("Đặt Phòng");
    setModal(true);
    setFixedSize(400, 350);
    
    setupUI();
    connectSignals();
    loadRoomTypes();
}

void RoomBookingDialog::setupUI() {
    QVBoxLayout* mainLayout = new QVBoxLayout(this);
    
    // Form layout
    QFormLayout* formLayout = new QFormLayout();
    
    // Customer ID
    customerIdEdit = new QLineEdit();
    customerIdEdit->setPlaceholderText("Nhập ID khách hàng");
    formLayout->addRow("ID Khách hàng:", customerIdEdit);
    
    // Room type
    roomTypeCombo = new QComboBox();
    formLayout->addRow("Loại phòng:", roomTypeCombo);
    
    // Check-in date
    checkInDate = new QDateEdit();
    checkInDate->setDate(QDate::currentDate());
    checkInDate->setCalendarPopup(true);
    formLayout->addRow("Ngày nhận phòng:", checkInDate);
    
    // Check-out date
    checkOutDate = new QDateEdit();
    checkOutDate->setDate(QDate::currentDate().addDays(1));
    checkOutDate->setCalendarPopup(true);
    formLayout->addRow("Ngày trả phòng:", checkOutDate);
    
    // Number of guests
    guestsSpinBox = new QSpinBox();
    guestsSpinBox->setRange(1, 10);
    guestsSpinBox->setValue(1);
    formLayout->addRow("Số khách:", guestsSpinBox);
    
    // Special requests
    specialRequestsEdit = new QTextEdit();
    specialRequestsEdit->setMaximumHeight(80);
    specialRequestsEdit->setPlaceholderText("Yêu cầu đặc biệt (tùy chọn)");
    formLayout->addRow("Yêu cầu đặc biệt:", specialRequestsEdit);
    
    mainLayout->addLayout(formLayout);
    
    // Buttons
    QHBoxLayout* buttonLayout = new QHBoxLayout();
    bookButton = new QPushButton("Đặt Phòng");
    cancelButton = new QPushButton("Hủy");
    
    bookButton->setStyleSheet("QPushButton { background-color: #4CAF50; color: white; font-weight: bold; padding: 8px; }");
    cancelButton->setStyleSheet("QPushButton { background-color: #f44336; color: white; font-weight: bold; padding: 8px; }");
    
    buttonLayout->addWidget(bookButton);
    buttonLayout->addWidget(cancelButton);
    
    mainLayout->addLayout(buttonLayout);
}

void RoomBookingDialog::connectSignals() {
    connect(bookButton, &QPushButton::clicked, this, &RoomBookingDialog::onBookRoom);
    connect(cancelButton, &QPushButton::clicked, this, &QDialog::reject);
    connect(checkInDate, &QDateEdit::dateChanged, this, &RoomBookingDialog::onDateChanged);
    connect(checkOutDate, &QDateEdit::dateChanged, this, &RoomBookingDialog::onDateChanged);
}

void RoomBookingDialog::loadRoomTypes() {
    roomTypeCombo->addItem("Standard Room", "STANDARD");
    roomTypeCombo->addItem("Deluxe Room", "DELUXE");
    roomTypeCombo->addItem("Suite Room", "SUITE");
    roomTypeCombo->addItem("Presidential Suite", "PRESIDENTIAL");
}

void RoomBookingDialog::onDateChanged() {
    // Ensure check-out date is after check-in date
    if (checkOutDate->date() <= checkInDate->date()) {
        checkOutDate->setDate(checkInDate->date().addDays(1));
    }
}

void RoomBookingDialog::onBookRoom() {
    // Validate input
    if (customerIdEdit->text().isEmpty()) {
        QMessageBox::warning(this, "Lỗi", "Vui lòng nhập ID khách hàng!");
        return;
    }
    
    if (checkOutDate->date() <= checkInDate->date()) {
        QMessageBox::warning(this, "Lỗi", "Ngày trả phòng phải sau ngày nhận phòng!");
        return;
    }
    
    // Get booking information
    BookingInfo booking;
    booking.customerId = customerIdEdit->text();
    booking.roomType = roomTypeCombo->currentData().toString();
    booking.checkInDate = checkInDate->date();
    booking.checkOutDate = checkOutDate->date();
    booking.numberOfGuests = guestsSpinBox->value();
    booking.specialRequests = specialRequestsEdit->toPlainText();
    
    // Calculate total days and cost
    int totalDays = booking.checkInDate.daysTo(booking.checkOutDate);
    double dailyRate = getRoomPrice(booking.roomType);
    double totalCost = totalDays * dailyRate;
    
    // Show confirmation
    QString message = QString("Thông tin đặt phòng:\n\n"
                            "ID Khách hàng: %1\n"
                            "Loại phòng: %2\n"
                            "Từ: %3\n"
                            "Đến: %4\n"
                            "Số ngày: %5\n"
                            "Số khách: %6\n"
                            "Tổng tiền: %7 VND\n\n"
                            "Bạn có muốn xác nhận đặt phòng?")
                    .arg(booking.customerId)
                    .arg(roomTypeCombo->currentText())
                    .arg(booking.checkInDate.toString("dd/MM/yyyy"))
                    .arg(booking.checkOutDate.toString("dd/MM/yyyy"))
                    .arg(totalDays)
                    .arg(booking.numberOfGuests)
                    .arg(QString::number(totalCost, 'f', 0));
    
    int ret = QMessageBox::question(this, "Xác nhận đặt phòng", message,
                                   QMessageBox::Yes | QMessageBox::No);
    
    if (ret == QMessageBox::Yes) {
        // Process booking (you can integrate with your hotel system here)
        processBooking(booking);
        accept();
    }
}

double RoomBookingDialog::getRoomPrice(const QString& roomType) {
    if (roomType == "STANDARD") return 500000;
    if (roomType == "DELUXE") return 800000;
    if (roomType == "SUITE") return 1200000;
    if (roomType == "PRESIDENTIAL") return 2000000;
    return 500000;
}

void RoomBookingDialog::processBooking(const BookingInfo& booking) {
    // Here you would integrate with your hotel management system
    // For now, just show a success message
    QMessageBox::information(this, "Thành công", 
                           "Đặt phòng thành công!\n"
                           "Mã đặt phòng: " + generateBookingId());
}

QString RoomBookingDialog::generateBookingId() {
    // Generate a simple booking ID
    return QString("BK%1%2")
           .arg(QDate::currentDate().toString("yyyyMMdd"))
           .arg(QTime::currentTime().toString("hhmmss"));
}
