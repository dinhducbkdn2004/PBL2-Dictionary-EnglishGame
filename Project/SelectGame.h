#ifndef SELECTGAME_H
#define SELECTGAME_H
#include "Question.h"
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

std::string globalUsername_1;
std::fstream f;

class Select : public Question {
protected:
    std::string** inputtt;
    int offset;
    int num;
    int score;
    void Setup();
    std::string* removeDupWord(std::string str, int n);
    int RandomNumber(double, double);

public:
    Select();
    Select(int, int);
    Select(const Select& a);
    ~Select();
    int Show();
    void SetOffset(int, int, int, const std::string& username);
};

Select::Select() : Question() {}

Select::Select(int score, int sodapan) : Question(score) {}

Select::Select(const Select& a) : Question(a.score) {}

Select::~Select() {
    for (int i = 0; i < 3; i++)
    {
        delete[] inputtt[i];
    }
    delete[] inputtt;
}

// Using C++11 random features
int Select::RandomNumber(double a, double b) {
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_real_distribution<double> dist(a, b);
    return dist(mt);
}

// Split str to n components
std::string* Select::removeDupWord(std::string str, int n) {
    std::string word = "";
    std::string* res = new std::string[n];
    int i = 0;
    for (auto x : str) {
        if ((x == '\t' || x == ' ') && i < n - 1) {
            res[i] = word;
            i++;
            word = "";
        }
        else {
            word = word + x;
        }
    }
    res[i] = word;
    return res;
}

void Select::Setup() {
    // Get data for question from gamedata.txt
    f.open("./data/GameData/" + globalUsername_1 + ".txt");
    int r1, r2, r3, r4;
    if (offset == 0) {
        r1 = RandomNumber(0, num - 3);
        r2 = RandomNumber(r1 + 1, num - 2);
        r3 = RandomNumber(r2 + 1, num - 1);
        r4 = RandomNumber(r3 + 1, num);
    }
    else {
        r1 = RandomNumber(0, offset - 1);
        r2 = RandomNumber(r1 + 1, offset);
        r3 = RandomNumber(offset + 1, num - 1);
        r4 = RandomNumber(r3 + 1, num);
    }

    int k = 0;
    inputtt = new std::string * [4];
    for (int i = 0; i <= r4; i++) {
        char temp[MAX];
        f.getline(temp, MAX);
        if (i == r1 || i == r2 || i == r3 || i == r4) {
            std::string input = temp;
            std::string* input_list = removeDupWord(input, 4);
            inputtt[k] = input_list;
            k++;
        }
    }
    f.close();
    return;
}

void Select::SetOffset(int offset, int num, int score, const std::string& username) {
    this->offset = offset;
    this->num = num;
    this->score = score;
    globalUsername_1 = username;
}

int Select::Show() {
    Setup();
    return 0;
}

#endif // !SELECTGAME_H
