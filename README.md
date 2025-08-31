# 🌿 Da-Lat-Hotel-Management 🏩  
A simple **Object-Oriented Programming (OOP)** project to manage a hotel system (rooms, employees, customers, …) inspired by a hotel located in **Da Lat**.  

---
## I. How to build 🛠

### 1. Install MSYS2  
- Download and install MSYS2 from: [https://www.msys2.org](https://www.msys2.org)  
### 2. Install Qt6 and MinGW toolchain  
Open **MSYS2 MinGW 64-bit** terminal and run:  
```bash
pacman -Syu
pacman -S --needed base-devel mingw-w64-x86_64-toolchain
pacman -S mingw-w64-x86_64-qt6
```
### 3. Install Cmake and set PATH Cmake 
---

## 🚀 II. Build and run the project
###  1. Run the build_gui.bat
``` bash
.\build_gui.bat
```
### 2. Run the main executable file in the terminal: 
``` bash
.\build\bin\hotel_management_gui.exe
```
### 3. (Optional) Deploy Qt runtime  
In case you get **missing DLL errors**, run:  
```bash
windeployqt6 build/bin/hotel_management_gui.exe
```

## III. Slides: 
👉 [Link to Slides](https://docs.google.com/presentation/d/1husCOQ6RZ7IZOTgnqQ_fkh6wiutEfyJs/edit?usp=sharing&ouid=104507805070612477779&rtpof=true&sd=true)

## IV. Demo Video:
👉 [Watch Demo Video](https://youtu.be/qGTo75MjVp8)

## V. Contributed by:

- Phạm Tấn Nhật Thịnh - 24127244
- Trịnh Duy Nhân - 24127094
- Huỳnh Thái Hoàng - 24127171
- Trần Minh Tiến - 24127130
- Võ Đình Cao Minh Hào - 24127035


---
✨ *Enjoy managing your hotel system with Da Lat vibes!* 🌸
