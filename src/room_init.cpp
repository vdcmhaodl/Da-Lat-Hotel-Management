#include "room.h"

room::room(std::string roomNumber, double pricePerNight) {
  this->ID = roomNumber;
  this->pricePerNight = pricePerNight;
  this->locked = false;  // Sử dụng false thay vì 0 cho clarity
  this->current_guest = "";
  this->currentGuestId = "";  // Thêm dòng này

  int type = (int)(this->ID[2] - '0');

  room_director director;
  room_item_director item_director;

  singleNormalRoom construct1;
  doubleNormalRoom construct2;
  singleVipRoom construct3;
  doubleVipRoom construct4;

  singleRoomItem item_construct1;
  doubleRoomItem item_construct2;

  // type nằm trong range [1,8] thì code ở dưới mới chạy đc
  type = (type - 1) % 8 + 1;

  // *** QUAN TRỌNG: GÁN typeNum ***
  this->typeNum = type;  // THIẾU DÒNG NÀY!

  if (type % 2)
    View = city;
  else
    View = nature;

  switch (type) {
    case 1:
    case 2:
      director.construct(&construct1);
      item_director.construct(&item_construct1);
      if (type == 1)
        this->typeName = "Single normal room with city view";
      else
        this->typeName = "Single normal room with nature view";
      this->roomType = director.getResult(&construct1);
      this->item = item_director.getResult(&item_construct1);
      break;
    case 3:
    case 4:
      director.construct(&construct2);
      item_director.construct(&item_construct2);
      if (type == 3)
        this->typeName = "Double normal room with city view";
      else
        this->typeName = "Double normal room with nature view";
      this->roomType = director.getResult(&construct2);
      this->item = item_director.getResult(&item_construct2);
      break;

    case 5:
    case 6:
      director.construct(&construct3);
      item_director.construct(&item_construct2);
      if (type == 5)
        this->typeName = "Single VIP room with city view";
      else
        this->typeName = "Single VIP room with nature view";
      this->roomType = director.getResult(&construct3);
      this->item = item_director.getResult(&item_construct2);
      break;

    case 7:
    case 8:
      director.construct(&construct4);
      item_director.construct(&item_construct1);
      // *** SỬA LỖI Ở ĐÂY ***
      if (type == 7)  // Đã sửa: từ type == 6 thành type == 7
        this->typeName = "Double VIP room with city view";
      else
        this->typeName = "Double VIP room with nature view";
      this->roomType = director.getResult(&construct4);
      this->item = item_director.getResult(&item_construct1);
      break;
    default:
      // Thêm xử lý default case
      std::cout << "Warning: Invalid room type " << type << " for room " << ID
                << std::endl;
      this->typeNum = 1;  // Fallback to type 1
      this->typeName = "Single normal room with city view";
      director.construct(&construct1);
      item_director.construct(&item_construct1);
      this->roomType = director.getResult(&construct1);
      this->item = item_director.getResult(&item_construct1);
      break;
  }
}

room::room(const room& a) {
  this->ID = a.ID;
  this->typeNum = a.typeNum;  // Đã có - OK
  this->currentGuestId = a.currentGuestId;

  // Deep copy roomType
  if (a.roomType) {
    roomType = new room_basic;
    roomType->setSingle_beds(a.roomType->getSingle_beds());
    roomType->setLarge_beds(a.roomType->getLarge_beds());
    roomType->setBathrooms(a.roomType->getBathrooms());
    roomType->setBath(a.roomType->getBath());
    roomType->setTV(a.roomType->getTV());
    roomType->setBalcol(a.roomType->getBalcol());
    roomType->setLoving_chair(a.roomType->getLoving_chair());
    roomType->setFridge(a.roomType->getFridge());
    roomType->setRooms(a.roomType->getRooms());
  } else {
    roomType = nullptr;
  }

  // Deep copy item
  if (a.item) {
    item = new room_item;
    item->setTowel(a.item->getTowel());
    item->setHair_dryer(a.item->getHair_dryer());
    item->setSandals(a.item->getSandals());
    item->setSleep_dress(a.item->getSleep_dress());
  } else {
    item = nullptr;
  }

  typeName = a.typeName;
  View = a.View;  // Thêm dòng này
  pricePerNight = a.pricePerNight;
  locked = a.locked;
  current_guest = a.current_guest;
  book_history = a.book_history;
  booking_queue = a.booking_queue;  // Thêm dòng này
  Service = a.Service;
}

room& room::operator=(const room& a) {
  if (this == &a) return *this;

  this->ID = a.ID;
  this->typeNum = a.typeNum;                // *** THÊM DÒNG NÀY ***
  this->currentGuestId = a.currentGuestId;  // *** THÊM DÒNG NÀY ***

  // Clean up old memory
  delete roomType;
  delete item;

  // Deep copy roomType
  if (a.roomType) {
    roomType = new room_basic;
    roomType->setSingle_beds(a.roomType->getSingle_beds());
    roomType->setLarge_beds(a.roomType->getLarge_beds());
    roomType->setBathrooms(a.roomType->getBathrooms());
    roomType->setBath(a.roomType->getBath());
    roomType->setTV(a.roomType->getTV());
    roomType->setBalcol(a.roomType->getBalcol());
    roomType->setLoving_chair(a.roomType->getLoving_chair());
    roomType->setFridge(a.roomType->getFridge());
    roomType->setRooms(a.roomType->getRooms());
  } else {
    roomType = nullptr;
  }

  // Deep copy item
  if (a.item) {
    item = new room_item;
    item->setTowel(a.item->getTowel());
    item->setHair_dryer(a.item->getHair_dryer());
    item->setSandals(a.item->getSandals());
    item->setSleep_dress(a.item->getSleep_dress());
  } else {
    item = nullptr;
  }

  typeName = a.typeName;
  View = a.View;  // *** THÊM DÒNG NÀY ***
  pricePerNight = a.pricePerNight;
  locked = a.locked;
  current_guest = a.current_guest;
  book_history = a.book_history;
  booking_queue = a.booking_queue;  // *** THÊM DÒNG NÀY ***
  Service = a.Service;
  return *this;
}

room::~room() {
  delete roomType;
  delete item;
}

void room::construct() {
  std::cout << "DEBUG: room::construct() called for room " << ID << "\n";
  std::cout << "DEBUG: Room type number: " << typeNum << "\n";

  // *** KIỂM TRA VALIDATION ***
  if (typeNum < 1 || typeNum > 8) {
    std::cout << "DEBUG: Invalid room type: " << typeNum << "\n";
    std::cout << "DEBUG: Resetting to type 1\n";
    typeNum = 1;  // Reset về giá trị hợp lệ
  }

  try {
    room_director director;
    room_item_director item_director;

    singleNormalRoom construct1;
    doubleNormalRoom construct2;
    singleVipRoom construct3;
    doubleVipRoom construct4;

    singleRoomItem item_construct1;
    doubleRoomItem item_construct2;

    int type = typeNum;

    // Set View based on type
    if (type % 2)
      View = city;
    else
      View = nature;

    switch (type) {
      case 1:
      case 2:
        director.construct(&construct1);
        item_director.construct(&item_construct1);
        if (type == 1)
          this->typeName = "Single normal room with city view";
        else
          this->typeName = "Single normal room with nature view";
        this->roomType = director.getResult(&construct1);
        this->item = item_director.getResult(&item_construct1);
        break;
      case 3:
      case 4:
        director.construct(&construct2);
        item_director.construct(&item_construct2);
        if (type == 3)
          this->typeName = "Double normal room with city view";
        else
          this->typeName = "Double normal room with nature view";
        this->roomType = director.getResult(&construct2);
        this->item = item_director.getResult(&item_construct2);
        break;

      case 5:
      case 6:
        director.construct(&construct3);
        item_director.construct(&item_construct2);
        if (type == 5)
          this->typeName = "Single VIP room with city view";
        else
          this->typeName = "Single VIP room with nature view";
        this->roomType = director.getResult(&construct3);
        this->item = item_director.getResult(&item_construct2);
        break;

      case 7:
      case 8:
        director.construct(&construct4);
        item_director.construct(&item_construct1);
        // *** ĐÃ SỬA LỖI ***
        if (type == 7)  // Trước đó là type == 6 (SAI)
          this->typeName = "Double VIP room with city view";
        else  // type == 8
          this->typeName = "Double VIP room with nature view";
        this->roomType = director.getResult(&construct4);
        this->item = item_director.getResult(&item_construct1);
        break;
      default:
        // Fallback case - không nên xảy ra do đã validate ở trên
        std::cout << "DEBUG: Unexpected default case for type " << type << "\n";
        director.construct(&construct1);
        item_director.construct(&item_construct1);
        this->typeName = "Single normal room with city view";
        this->roomType = director.getResult(&construct1);
        this->item = item_director.getResult(&item_construct1);
        break;
    }
    std::cout << "DEBUG: room::construct() completed successfully\n";
    std::cout << "DEBUG: Room " << ID << " type: " << typeName << "\n";
  } catch (const std::exception& e) {
    std::cout << "DEBUG: Error in room::construct(): " << e.what() << "\n";
    throw;
  }
}

room::room() {
  ID = "";
  roomType = nullptr;
  typeName = "";
  typeNum = 1;  // *** SỬA: Đặt giá trị mặc định hợp lệ (1) thay vì 0 ***
  View = city;
  item = nullptr;
  pricePerNight = 0.0;
  current_guest = "";
  currentGuestId = "";
  locked = false;
}

// *** THÊM METHOD TIỆN ÍCH ***
// Thêm method để tái khởi tạo room type khi cần
void room::reinitializeRoomType() {
  if (typeNum >= 1 && typeNum <= 8) {
    // Cleanup old objects
    delete roomType;
    delete item;
    roomType = nullptr;
    item = nullptr;

    // Reconstruct with current typeNum
    construct();
  } else {
    std::cout << "Cannot reinitialize: Invalid typeNum " << typeNum << "\n";
  }
}