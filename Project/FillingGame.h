#ifndef FILLINGGAME_H
#define FILLINGGAME_H
#include "Question.h"
#include "Format.h"
#include <iostream>
#include <string>
#include <fstream>
#include <random>
#include <iomanip>
#include <io.h>
#include <fcntl.h>
#include <locale>
#include <codecvt>
#define MAX 512
std::string globalUsername_2;

class Find : public Question {
protected:
    std::string inputString; // Hello
    int correctAnswer;       // e
    std::string ques;        // H_llo
    std::string mean;
    int overlap[MAX];
    int score;
    int offset;
    int num;
    void Setup();
    std::string* removeDupWord(std::string str, int n);
    int RandomNumber(double, double);
    std::string upper(std::string);

public:
    Find();
    Find(const Find&);
    ~Find();
    int Show();
    void SetOffset(int, int, int, const std::string& username);
};

Find::Find() {}

Find::Find(const Find& a) {}

Find::~Find() {}


int Find::RandomNumber(double a, double b)
{
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_real_distribution<double> dist(a, b);
    return dist(mt);
}

std::string* Find::removeDupWord(std::string str, int n)
{
    std::string word = "";
    std::string* res = new std::string[n];
    int i = 0;
    for (char x : str) { // Sửa thành 'char x' để duyệt từng ký tự trong chuỗi 'str'.
        if ((x == ' ' || x == '\t') && !word.empty() && i < n - 1) {
            res[i] = word;
            i++;
            word = "";
        }
        else if (x != ' ' && x != '\t') {
            word += x;
        }
    }
    if (!word.empty() && i < n) {
        res[i] = word;
    }
    return res;
}

std::string Find::upper(std::string a)
{
    std::string temp = a;
    for (int i = 0; i < a.length(); i++) {
        if (a[i] >= 'a' && a[i] <= 'z') { // Sửa thành so sánh với ký tự thường.
            temp[i] = char(a[i] - 32);
        }
    }
    return temp;
}

void Find::Setup()
{
    std::fstream f;
    // Get data for question from gamedata.txt
    std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
    f.open("./data/GameData/" + globalUsername_2 + "_overlap.txt");
    int r1;
    f >> r1;
    r1++;
    f.close();

    f.open("./data/GameData/" + globalUsername_2 + "_overlap.txt", std::ios::out);
    f << r1;
    f.close();

    f.open("./data/GameData/" + globalUsername_2 + ".txt");
    char temp[MAX];
    for (int i = 0; i < r1 - 1; i++)
    {
        f.getline(temp, MAX);
    }
    f.getline(temp, MAX);
    std::string input = temp;
    std::string* input_list = removeDupWord(input, 4);
    inputString = input_list[0];
    mean = input_list[3];
    int k = inputString.length();
    int r2 = RandomNumber(0, k);
    ques = inputString;
    ques = upper(ques);
    correctAnswer = ques[r2];
    ques.replace(r2, 1, "_");

    f.close();
    return;
}

void Find::SetOffset(int offset, int num, int score, const std::string& username)
{
    this->offset = offset;
    this->num = num;
    this->score = score;
    globalUsername_2 = username;
}

int Find::Show()
{
    this->Setup();
    std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
    wchar_t answer;
    std::wstring blank = L"\t";
    int w = 40;
    int wp = w - 1;
    std::wcout << std::endl;
    std::wcout << std::endl << std::setw(41) << std::right << blank << L"||" << std::setfill(L' ') << std::setw(w / 2 + 2) << converter.from_bytes(ques) << std::setw(w / 2 - 2) << L"||" << L"   " << L"Score: " << score << std::endl;
    std::wcout << std::endl << std::setw(55) << L"Your answer: ";
    std::wcin >> answer;
    if (answer == char(correctAnswer) || answer == char(correctAnswer + 32)) {
        set_Color(0, 2);
        std::wcout << std::setw(65) << L"Hurray! Correct answer!" << std::endl;
        set_Color(0, 7);
        std::wcout << std::setw(62) << L"Vietnamese meaning: " << converter.from_bytes(mean) << std::endl;
        return 10;
    }

    else {
        set_Color(0, 4);
        std::wcout << std::setw(59) << L"Oh! Wrong answer!" << std::endl;
        set_Color(0, 7);
        std::wcout << std::setw(61) << L"Correct answer is: " << converter.from_bytes(inputString) << std::endl;
        std::wcout << std::setw(62) << L"Vietnamese meaning: " << converter.from_bytes(mean) << std::endl;
        return 0;
    }

}

#endif // !FILLINGGAME_H