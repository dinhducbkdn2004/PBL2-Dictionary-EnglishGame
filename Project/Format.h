#ifndef FORMAT_H
#define FORMAT_H
#include <iostream>
#include <Windows.h>
#include <conio.h>
#include <fstream>
#include <io.h>
#include <fcntl.h>
#include <iomanip>

inline int pickMenu1() {
    char ch;
    int output;

    while (true) {
        ch = _getch();
        if (ch >= '0' && ch <= '9') {
            output = ch - '0';
            break;
        }
    }
    return output;
}

inline void set_Color(int background_color, int text_color) {
    HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
    int color_code = background_color * 16 + text_color;
    SetConsoleTextAttribute(hStdout, color_code);
}

// Xóa màn hình
inline void clrscr() {
    system("cls");
}

// Tạm dừng chương trình và hiển thị thông báo "Nhấn phím bất kỳ để tiếp tục..."
inline void pause() {
    //set_Color(0, 10);
    //std::cout << "\n\t\t\t\t\t\t\t\tLoading......" << std::endl;
    //set_Color(0, 15);
    system("pause > nul");  // >nul là cú pháp để ẩn thông báo "Nhấn bất kỳ phím để tiếp tục..."
}

// Đặt chế độ nhập/xuất Unicode
inline void set_Mode() {
    _setmode(_fileno(stdin), _O_U16TEXT);
    _setmode(_fileno(stdout), _O_U16TEXT);
}

// Khôi phục chế độ nhập/xuất văn bản thông thường
inline void reset_Mode() {
    _setmode(_fileno(stdin), _O_TEXT);
    _setmode(_fileno(stdout), _O_TEXT);
}

// Hiển thị thông tin về đồ án
inline void get_Infor() {
    int i, j = 42;
    set_Color(0, 9);
    std::wcout << std::endl << std::setw(j) << char(201);
    for (i = 0; i <= 85; i++) std::cout << char(205);
    std::wcout << char(187);
    std::wcout << std::endl << std::setw(j) << char(186) << std::setw(87) << char(186);
    std::wcout << std::endl << std::setw(j) << char(186) << std::setw(54) << "PBL2: DO AN LAP TRINH CO SO" << std::setw(33) << char(186);
    std::wcout << std::endl << std::setw(j) << char(186) << std::setw(69) << "DE TAI: TU DIEN TIENG ANH TICH HOP TRO CHOI TU VUNG" << std::setw(18) << char(186);
    std::wcout << std::endl << std::setw(j) << char(186) << std::setw(87) << char(186);
    std::wcout << std::endl << std::setw(j) << char(186) << std::setw(27) << "Sinh vien thuc hien:" << std::setw(43) << "Giao vien huong dan:" << std::setw(17) << char(186);
    std::wcout << std::endl << std::setw(j) << char(186) << std::setw(12) << char(45) << std::setw(15) << " Truong Xuan Phuc" << std::setw(24) << char(45) << std::setw(18) << " Nguyen Van Hieu " << std::setw(16) << char(186);
    std::wcout << std::endl << std::setw(j) << char(186) << std::setw(12) << char(45) << std::setw(9) << " Dinh Duc" << std::setw(66) << char(186);
    std::wcout << std::endl << std::setw(j) << char(186) << std::setw(87) << char(186);
    std::wcout << std::endl << std::setw(j) << char(200);
    for (i = 0; i <= 85; i++) std::cout << char(205);
    std::wcout << char(188) << std::endl;
    set_Color(0, 3);
    reset_Mode();
    pause();
}

// Hiển thị menu cho người dùng
inline int selectMenu() {
    // Menu

    // Xác nhận lựa chọn
    bool isSelected = false;
    int selection;
    do {
        wchar_t temp;
        std::wcout << L"\n==>> Select one function: ";
        fflush(stdin);
        std::wcin >> temp;
        selection = (int)temp - 48;

        selection = (int)selection;
        if (selection == 1 || selection == 2 || selection == 3 ||
            selection == 4 || selection == 5)
            isSelected = true;
        else
            std::wcout << L"\nFail! Invalid choice!" << std::endl;
    } while (!isSelected);
    return selection;
}

// Kiểm tra người dùng muốn tiếp tục hay không
inline int toContinue()
{
    int selection;
    std::wcout << std::endl << std::endl << std::setw(89) << L"--++----------++--" << std::endl;
    std::wcout << std::setw(89) << std::endl << L"| Press 1 to continue." << std::endl;
    std::wcout << std::setw(93) << L"| Press 2 to back to menu." << std::endl;
    selection = pickMenu1();
    return selection;
}

// Màn hình thoát
inline void exitScreen() {
    clrscr();
    std::wifstream exitFile(L"./data/end.txt");
    wchar_t str[300];
    if (exitFile.fail())
        std::wcout << L"Failed to open data file!" << std::endl;
    else
    {
        while (exitFile)
        {
            exitFile.getline(str, 300);
            if (exitFile)
                std::wcout << str << std::endl;
        }
    }
    exitFile.close();
    pause();
}

#endif // !FORMAT_H