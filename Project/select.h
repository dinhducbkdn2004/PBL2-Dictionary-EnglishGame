#ifndef SELECT_H
#define SELECT_H
#include "SelectGame.h"
#include "Format.h"
#include <random>
#include <iomanip>
#include <io.h>
#include <fcntl.h>
#include <string>
#include <locale>
#include <codecvt>
#define MAX 512
using namespace std;

// Question: English -> Answer: Vietnamese
class Select1 : public Select {
    int correctAnswer;
    void Setup();

public:
    Select1();
    Select1(int);
    Select1(const Select1&);
    ~Select1();
    int Show();
};

Select1::Select1() {}

Select1::Select1(const Select1& a) {}

Select1::Select1(int a) {
    correctAnswer = a;
}

Select1::~Select1() {}

void Select1::Setup() {
    Select::Setup();
    correctAnswer = RandomNumber(0, 4);
}

// Question: Tieng Anh, Answer: Tieng Viet
int Select1::Show() {
    this->Setup();
    wstring_convert<codecvt_utf8_utf16<wchar_t>> converter;

    wstring blank = L"\t";
    int w = 35;
    int wp = w - 1;

    string ques = inputtt[correctAnswer][0];
    string ans0 = inputtt[0][3];
    string ans1 = inputtt[1][3];
    string ans2 = inputtt[2][3];
    string ans3 = inputtt[3][3];

    wstring q = converter.from_bytes(ques);
    wstring a0 = converter.from_bytes(ans0);
    wstring a1 = converter.from_bytes(ans1);
    wstring a2 = converter.from_bytes(ans2);
    wstring a3 = converter.from_bytes(ans3);
    wcout << setfill(L' ') << left << setw(w) << q + L" mean:.....?" << right << setw(10) << L"Score: " << score << endl;
    wcout << endl;
    wcout << setw(40) << setfill(L' ') << L" /" << setw(35) << setfill(L'=') << L"\\" << blank << blank << " /" << setw(35) << setfill(L'=') << L"\\" << endl;
    wcout << setw(40) << setfill(L' ') << L"||" << setfill(L' ') << left << setw(wp) << L"   1. " + a0 << L"||" << blank << blank;
    wcout << L"||" << setfill(L' ') << left << setw(wp) << L"   2. " + a1 << L"||" << endl;
    wcout << setw(40) << right << setfill(L' ') << L" \\" << setw(35) << setfill(L'=') << L"/" << blank << blank << L" \\" << setw(35) << L"/" << endl;
    wcout << endl;
    wcout << setw(40) << setfill(L' ') << L" /" << setw(35) << setfill(L'=') << L"\\" << blank << blank << " /" << setw(35) << setfill(L'=') << L"\\" << endl;
    wcout << setw(40) << setfill(L' ') << L"||" << setfill(L' ') << left << setw(wp) << L"   3. " + a2 << L"||" << blank << blank;
    wcout << L"||" << setfill(L' ') << left << setw(wp) << L"   4. " + a3 << L"||" << endl;
    wcout << setw(40) << right << setfill(L' ') << L" \\" << setw(35) << setfill(L'=') << L"/" << blank << blank << L" \\" << setw(35) << L"/" << endl;
    wcout << endl;
    wstring answer;
    wcout << endl;
    wcout << setw(52) << setfill(L' ') << L"Your answer: ";
    wcin >> answer;

    if (int(answer[0]) == 49 + correctAnswer || answer == converter.from_bytes(inputtt[correctAnswer][2])) {
        set_Color(0, 2);
        wcout << setw(62) << setfill(L' ') << L"Hurray! Correct answer!" << endl;
        set_Color(0, 7);
        return 10;
    }
    else {
        set_Color(0, 4);
        wcout << setw(56) << setfill(L' ') << L"Oh! Wrong answer!" << endl;
        set_Color(0, 7);
        wcout << setw(58) << setfill(L' ') << L"Correct answer is: " << converter.from_bytes(inputtt[correctAnswer][3]) << endl;
        return 0;
    }
}


// Game Select 2
// Question: Vietnamese -> Answer: English
class Select2 : public Select {
    int correctAnswer;
    void Setup();

public:
    Select2();
    Select2(int);
    Select2(const Select2&);
    ~Select2();
    int Show();
};

Select2::Select2() {}

Select2::Select2(const Select2& a) {}

Select2::Select2(int a) {
    correctAnswer = a;
}

Select2::~Select2() {}

void Select2::Setup() {
    Select::Setup();
    correctAnswer = RandomNumber(0, 4);
}

int Select2::Show() {
    this->Setup();
    std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;

    std::wstring blank = L"\t";
    int w = 35;
    int wp = w - 1;
    std::wcout << std::setfill(L' ') << std::left << std::setw(w) << converter.from_bytes(inputtt[correctAnswer][3]) + L" is:.....?" << std::right << std::setw(10) << L"Score: " << score << std::endl;
    std::wcout << std::endl;
    std::wcout << std::setw(40) << std::setfill(L' ') << L" /" << std::setw(35) << std::setfill(L'=') << L"\\" << blank << blank << " /" << std::setw(35) << std::setfill(L'=') << L"\\" << std::endl;
    std::wcout << std::setw(40) << std::setfill(L' ') << L"||" << std::setfill(L' ') << std::left << std::setw(wp) << L"   1. " + converter.from_bytes(inputtt[0][0]) << L"||" << blank << blank;
    std::wcout << L"||" << std::setfill(L' ') << std::left << std::setw(wp) << L"   2. " + converter.from_bytes(inputtt[1][0]) << L"||" << std::endl;
    std::wcout << std::setw(40) << std::right << std::setfill(L' ') << L" \\" << std::setw(35) << std::setfill(L'=') << L"/" << blank << blank << L" \\" << std::setw(35) << L"/" << std::endl;
    std::wcout << std::endl;
    std::wcout << std::setw(40) << std::setfill(L' ') << L" /" << std::setw(35) << std::setfill(L'=') << L"\\" << blank << blank << " /" << std::setw(35) << std::setfill(L'=') << L"\\" << std::endl;
    std::wcout << std::setw(40) << std::setfill(L' ') << L"||" << std::setfill(L' ') << std::left << std::setw(wp) << L"   3. " + converter.from_bytes(inputtt[2][0]) << L"||" << blank << blank;
    std::wcout << L"||" << std::setfill(L' ') << std::left << std::setw(wp) << L"   4. " + converter.from_bytes(inputtt[3][0]) << L"||" << std::endl;
    std::wcout << std::setw(40) << std::right << std::setfill(L' ') << L" \\" << std::setw(35) << std::setfill(L'=') << L"/" << blank << blank << L" \\" << std::setw(35) << L"/" << std::endl;
    std::wcout << std::endl;
    std::wstring answer;
    std::wcout << std::setw(52) << std::setfill(L' ') << L"Your answer: ";
    std::wcin >> answer;

    if (int(answer[0]) == 49 + correctAnswer || answer == converter.from_bytes(inputtt[correctAnswer][3])) {
        set_Color(0, 2);
        std::wcout << std::setw(62) << std::setfill(L' ') << L"Hurray! Correct answer!" << std::endl;
        set_Color(0, 7);
        return 10;
    }
    else {
        set_Color(0, 4);
        std::wcout << std::setw(56) << std::setfill(L' ') << L"Oh! Wrong answer!" << std::endl;
        set_Color(0, 7);
        std::wcout << std::setw(58) << std::setfill(L' ') << L"Correct answer is: " << converter.from_bytes(inputtt[correctAnswer][0]) << std::endl;
        return 0;
    }
}

// Game Select 3
// Question: English -> Answer: Vietnamese
class Select3 : public Select {
    int correctAnswer;
    void Setup();

public:
    Select3();
    Select3(int);
    Select3(const Select3&);
    ~Select3();
    int Show();
};

Select3::Select3() {}

Select3::Select3(const Select3& a) {}

Select3::Select3(int a) {
    correctAnswer = a;
}

Select3::~Select3() {}

void Select3::Setup() {
    Select::Setup();
    correctAnswer = RandomNumber(0, 4);
}

int Select3::Show() {
    this->Setup();
    std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;

    std::wstring blank = L"\t";
    int w = 35;
    int wp = w - 1;
    std::wcout << std::setfill(L' ') << std::left << std::setw(w) << converter.from_bytes(inputtt[correctAnswer][0]) + L" pronounce :.....?" << std::right << std::setw(10) << L"Score: " << score << std::endl;
    std::wcout << std::endl;
    std::wcout << std::setw(40) << std::setfill(L' ') << L" /" << std::setw(35) << std::setfill(L'=') << L"\\" << blank << blank << " /" << std::setw(35) << std::setfill(L'=') << L"\\" << std::endl;
    std::wcout << std::setw(40) << std::setfill(L' ') << L"||" << std::setfill(L' ') << std::left << std::setw(wp) << L"   1. " + converter.from_bytes(inputtt[0][1]) << L"||" << blank << blank;
    std::wcout << L"||" << std::setfill(L' ') << std::left << std::setw(wp) << L"   2. " + converter.from_bytes(inputtt[1][1]) << L"||" << std::endl;
    std::wcout << std::setw(40) << std::right << std::setfill(L' ') << L" \\" << std::setw(35) << std::setfill(L'=') << L"/" << blank << blank << L" \\" << std::setw(35) << L"/" << std::endl;
    std::wcout << std::endl;
    std::wcout << std::setw(40) << std::setfill(L' ') << L" /" << std::setw(35) << std::setfill(L'=') << L"\\" << blank << blank << " /" << std::setw(35) << std::setfill(L'=') << L"\\" << std::endl;
    std::wcout << std::setw(40) << std::setfill(L' ') << L"||" << std::setfill(L' ') << std::left << std::setw(wp) << L"   3. " + converter.from_bytes(inputtt[2][1]) << L"||" << blank << blank;
    std::wcout << L"||" << std::setfill(L' ') << std::left << std::setw(wp) << L"   4. " + converter.from_bytes(inputtt[3][1]) << L"||" << std::endl;
    std::wcout << std::setw(40) << std::right << std::setfill(L' ') << L" \\" << std::setw(35) << std::setfill(L'=') << L"/" << blank << blank << L" \\" << std::setw(35) << L"/" << std::endl;
    std::wcout << std::endl;
    std::wstring answer;
    std::wcout << std::setw(52) << std::setfill(L' ') << L"Your answer: ";
    std::wcin >> answer;

    if (int(answer[0]) == 49 + correctAnswer || answer == converter.from_bytes(inputtt[correctAnswer][3])) {
        set_Color(0, 2);
        std::wcout << std::setw(62) << std::setfill(L' ') << L"Hurray! Correct answer!" << std::endl;
        set_Color(0, 7);
        return 10;
    }
    else {
        set_Color(0, 4);
        std::wcout << std::setw(56) << std::setfill(L' ') << L"Oh! Wrong answer!" << std::endl;
        set_Color(0, 7);
        std::wcout << std::setw(58) << std::setfill(L' ') << L"Correct answer is: " << converter.from_bytes(inputtt[correctAnswer][1]) << std::endl;
        return 0;
    }
}

// Game Select 4
// Question: English -> Answer: Vietnamese
class Select4 : public Select {
    int correctAnswer;
    void Setup();

public:
    Select4();
    Select4(int);
    Select4(const Select4&);
    ~Select4();
    int Show();
};

Select4::Select4() {}

Select4::Select4(const Select4& a) {}

Select4::Select4(int a) {
    correctAnswer = a;
}

Select4::~Select4() {}

void Select4::Setup() {
    Select::Setup();
    correctAnswer = RandomNumber(0, 4);
}

int Select4::Show() {
    this->Setup();
    std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;

    std::wstring blank = L"\t";
    int w = 35;
    int wp = w - 1;
    std::wcout << std::setfill(L' ') << std::left << std::setw(w) << converter.from_bytes(inputtt[correctAnswer][1]) + L" is :.....?" << std::right << std::setw(10) << L"Score: " << score << std::endl;
    std::wcout << std::endl;
    std::wcout << std::setw(40) << std::setfill(L' ') << L" /" << std::setw(35) << std::setfill(L'=') << L"\\" << blank << blank << " /" << std::setw(35) << std::setfill(L'=') << L"\\" << std::endl;
    std::wcout << std::setw(40) << std::setfill(L' ') << L"||" << std::setfill(L' ') << std::left << std::setw(wp) << L"   1. " + converter.from_bytes(inputtt[0][0]) << L"||" << blank << blank;
    std::wcout << L"||" << std::setfill(L' ') << std::left << std::setw(wp) << L"   2. " + converter.from_bytes(inputtt[1][0]) << L"||" << std::endl;
    std::wcout << std::setw(40) << std::right << std::setfill(L' ') << L" \\" << std::setw(35) << std::setfill(L'=') << L"/" << blank << blank << L" \\" << std::setw(35) << L"/" << std::endl;
    std::wcout << std::endl;
    std::wcout << std::setw(40) << std::setfill(L' ') << L" /" << std::setw(35) << std::setfill(L'=') << L"\\" << blank << blank << " /" << std::setw(35) << std::setfill(L'=') << L"\\" << std::endl;
    std::wcout << std::setw(40) << std::setfill(L' ') << L"||" << std::setfill(L' ') << std::left << std::setw(wp) << L"   3. " + converter.from_bytes(inputtt[2][0]) << L"||" << blank << blank;
    std::wcout << L"||" << std::setfill(L' ') << std::left << std::setw(wp) << L"   4. " + converter.from_bytes(inputtt[3][0]) << L"||" << std::endl;
    std::wcout << std::setw(40) << std::right << std::setfill(L' ') << L" \\" << std::setw(35) << std::setfill(L'=') << L"/" << blank << blank << L" \\" << std::setw(35) << L"/" << std::endl;
    std::wcout << std::endl;
    std::wstring answer;
    std::wcout << std::setw(52) << std::setfill(L' ') << L"Your answer: ";
    std::wcin >> answer;

    /*wcout << setfill(L' ') << left << setw(w) << converter.from_bytes(inputtt[correctAnswer][1]) + L" is:.....?" << right << setw(10) << L"Score: " << score << endl;
    wcout << setfill(L'=') << L" /" << setw(w) << L"\\" << blank << L" /" << setw(w) << L"\\" << endl;
    wcout << L"||" << setfill(L' ') << left << setw(wp) << L"   1. " + converter.from_bytes(inputtt[0][0]) << L"||" << blank;
    wcout << L"||" << setfill(L' ') << left << setw(wp) << L"   2. " + converter.from_bytes(inputtt[1][0]) << L"||" << endl;
    wcout << right << setfill(L'=') << L" \\" << setw(w) << L"/" << blank << L" \\" << setw(w) << L"/" << endl;
    wcout << endl;
    wcout << right << setfill(L'=') << L" /" << setw(w) << L"\\" << blank << L" /" << setw(w) << L"\\" << endl;
    wcout << L"||" << setfill(L' ') << left << setw(wp) << L"   3. " + converter.from_bytes(inputtt[2][0]) << L"||" << blank;
    wcout << L"||" << setfill(L' ') << left << setw(wp) << L"   4. " + converter.from_bytes(inputtt[3][0]) << L"||" << endl;
    wcout << right << setfill(L'=') << L" \\" << setw(w) << L"/" << blank << L" \\" << setw(w) << L"/" << endl;
    wstring answer;
    wcout << L"==>> Your answer: ";
    wcin >> answer;*/

    if (int(answer[0]) == 49 + correctAnswer || answer == converter.from_bytes(inputtt[correctAnswer][3])) {
        set_Color(0, 2);
        std::wcout << setw(62) << setfill(L' ') << L"Hurray! Correct answer!" << std::endl;
        set_Color(0, 7);
        return 10;
    }
    else {
        set_Color(0, 4);
        std::wcout << setw(56) << setfill(L' ') << L"Oh! Wrong answer!" << std::endl;
        set_Color(0, 7);
        std::wcout << setw(58) << setfill(L' ') << L"Correct answer is: " << converter.from_bytes(inputtt[correctAnswer][0]) << std::endl;
        return 0;
    }
}

#endif // !SELECT_H
