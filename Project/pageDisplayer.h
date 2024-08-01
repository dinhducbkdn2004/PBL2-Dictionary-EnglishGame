#ifndef PAGEDISPLAYER_H
#define PAGEDISPLAYER_H
#include <iostream>
#include <fstream>
#include <locale>
#include "Format.h"

// Hàm hiển thị trang bắt đầu
void startPage() {
    set_Color(0, 3);
    std::wifstream file(L"./data/startPage.txt");
    std::wcout << file.rdbuf();
    set_Color(0, 7);
}

// Hàm hiển thị trang đăng ký
void registerPage() {
    set_Color(0, 3);
    std::wifstream file(L"./data/registerPage.txt");
    std::wcout << file.rdbuf();
    set_Color(0, 7);
}

// Hàm hiển thị trang thông báo lỗi
void errorPage() {
    set_Color(0, 3);
    std::wifstream file(L"./data/errorPage.txt");
    std::wcout << file.rdbuf();
    set_Color(0, 7);
}

// Hàm hiển thị trang đăng nhập
void loginPage() {
    set_Color(0, 3);
    std::wifstream file(L"./data/loginPage.txt");
    std::wcout << file.rdbuf();
    set_Color(0, 7);
}

// Hàm hiển thị trang đăng nhập của admin
void loginAdmPage() {
    set_Color(0, 3);
    std::wifstream file(L"./data/loginAdmPage.txt");
    std::wcout << file.rdbuf();
    set_Color(0, 7);
}

// Hàm hiển thị trang "About"
void aboutPage() {
    set_Color(0, 3);
    std::wifstream file(L"./data/aboutPage.txt");
    std::wcout << file.rdbuf();
    set_Color(0, 7);
}

void userSelection_1() {
    set_Color(0, 3);
    std::wifstream file(L"./data/userSelection_1.txt");
    std::wcout << file.rdbuf();
    set_Color(0, 7);
}

void userSelection_2() {
    set_Color(0, 3);
    std::wifstream file(L"./data/userSelection_2.txt");
    std::wcout << file.rdbuf();
    set_Color(0, 7);
}

void userSelection_3() {
    set_Color(0, 3);
    std::wifstream file(L"./data/userSelection_3.txt");
    std::wcout << file.rdbuf();
    set_Color(0, 7);
}

void userSelection_4() {
    set_Color(0, 3);
    std::wifstream file(L"./data/userSelection_4.txt");
    std::wcout << file.rdbuf();
    set_Color(0, 7);
}

void registerAccount() {
    set_Color(0, 3);
    std::wifstream file(L"./data/registerAccount.txt");
    std::wcout << file.rdbuf();
    set_Color(0, 7);
}

void editAccount() {
    set_Color(0, 3);
    std::wifstream file(L"./data/editAccount.txt");
    std::wcout << file.rdbuf();
    set_Color(0, 7);
}

void loginAccount() {
    set_Color(0, 3);
    std::wifstream file(L"./data/loginAccount.txt");
    std::wcout << file.rdbuf();
    set_Color(0, 7);
}

void loginAdmin() {
    set_Color(0, 3);
    std::wifstream file(L"./data/loginAdmin.txt");
    std::wcout << file.rdbuf();
    set_Color(0, 7);
}

void frame() {
    set_Color(0, 3);
    std::wifstream file(L"./data/toContinue.txt");
    std::wcout << file.rdbuf();
    set_Color(0, 7);
}

#endif // !PAGEDISPLAYER_H
