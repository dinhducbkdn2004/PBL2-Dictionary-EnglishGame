#include "Dictionary.h"
#include "Format.h"
#include <algorithm>
#include <fstream>
#include <locale>
#include <codecvt>
#include <string>
#include <iomanip>
#include <conio.h>

int pickMenu2() {
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

std::wstring toLowerCase(std::wstring eWord) {
    std::transform(eWord.begin(), eWord.end(), eWord.begin(), ::towlower);
    return eWord;
}

Dictionary::Dictionary() {}

void Dictionary::searchWordInDictionary() {
    system("cls");
    Word result;
    Word empty;
    std::wstring inputWord;

    std::wcout << std::setw(93) << std::endl << std::endl << L"<<===== SEARCHING =====>>" << std::endl;
    std::wcout << std::setw(95) << std::endl << L"Enter the word you want to search: ";

    //std::wcin.ignore(std::numeric_limits<std::streamsize>::max(), L'\n');

    std::getline(std::wcin, inputWord);

    inputWord = toLowerCase(inputWord);

    result = this->appDict.find_In_Table(inputWord);
    // Check if result is an empty word (that means the word isn't in the dictionary)
    if (result == empty) {
        set_Color(0, 4);
        std::wcout << std::endl << std::setw(86) << L"FAILED   " << std::endl;
        set_Color(0, 7);
        std::wcout << std::setw(105) << std::endl << L"o------------------------------------------------o" << std::endl;
        set_Color(0, 4);
        std::wcout << std::setw(101) << std::endl << L"Fail! This word isn't in the dictionary!" << std::endl;
        set_Color(0, 7);
        std::wcout << std::setw(105) << std::endl << L"o------------------------------------------------o" << std::endl;
    }
    else { // Print out searched word
        set_Color(0, 2);
        std::wcout << std::endl << std::setw(87) << L"SUCCESS   " << std::endl;
        set_Color(0, 7);
        std::wcout << result;
    }
}

void Dictionary::addNewWordToDictionary() {
    system("cls");
    Word temp;
    std::wcout << std::setw(91) << std::endl << std::endl << L"<<===== ADDING =====>>" << std::endl;
    //std::wcin.ignore(std::numeric_limits<std::streamsize>::max(), L'\n');
    std::wcin >> temp;
    temp.eWord = toLowerCase(temp.eWord);

    if (this->appDict.add_To_Table(temp)) {
        std::wcout << std::setw(105) << std::endl << L"o------------------------------------------------o" << std::endl;
        set_Color(0, 2);
        std::wcout << std::endl << std::setw(91) << L"Successfully added!" << std::endl;
        set_Color(0, 7);
        std::wcout << std::setw(105) << std::endl << L"o------------------------------------------------o" << std::endl;
    }
    else {
        set_Color(0, 4);
        std::wcout << std::endl << std::setw(87) << L"FAILED   " << std::endl;
        set_Color(0, 7);
        std::wcout << std::setw(105) << std::endl << L"o------------------------------------------------o" << std::endl;
        set_Color(0, 4);
        std::wcout << std::setw(102) << std::endl << L"Fail! This word is already in the dictionary" << std::endl;
        set_Color(0, 7);
        std::wcout << std::setw(105) << std::endl << L"o------------------------------------------------o" << std::endl;
    }
}

void Dictionary::delWordFromDictionary() {
    system("cls");
    std::wstring inputWord;
    std::wcout << std::setw(92) << std::endl << std::endl << L"<<===== DELETING =====>>" << std::endl;
    std::wcout << std::setw(93) << std::endl << std::endl << L"Enter the word you want to delete: ";
    //std::wcin.ignore(std::numeric_limits<std::streamsize>::max(), L'\n');
    std::getline(std::wcin, inputWord);
    inputWord = toLowerCase(inputWord);
    std::wcout << std::endl << std::setw(86) << L"Deleting..." << std::endl;

    if (this->appDict.delete_From_Table(inputWord)) {
        std::wcout << std::setw(105) << std::endl << L"o------------------------------------------------o" << std::endl;
        set_Color(0, 2);
        std::wcout << std::endl << std::setw(91) << L"Successfully deleted!" << std::endl;
        set_Color(0, 7);
        std::wcout << std::setw(105) << std::endl << L"o------------------------------------------------o" << std::endl;
    }
    else {
        set_Color(0, 4);
        std::wcout << std::endl << std::setw(85) << L"FAILED   " << std::endl;
        set_Color(0, 7);
        std::wcout << std::setw(105) << std::endl << L"o------------------------------------------------o" << std::endl;
        set_Color(0, 4);
        std::wcout << std::setw(101) << std::endl << L"Fail! This word isn't in the dictionary" << std::endl;
        set_Color(0, 7);
        std::wcout << std::setw(105) << std::endl << L"o------------------------------------------------o" << std::endl;
    }
}

void Dictionary::editWordInDictionary() {
    system("cls");
    Word result;
    Word empty;
    std::wstring inputWord;

    std::wcout << std::setw(92) << std::endl << std::endl << L"<<===== EDITING =====>>" << std::endl;
    std::wcout << std::setw(93) << std::endl << std::endl << L"Enter the word you want to edit: ";
    //::wcin.ignore(std::numeric_limits<std::streamsize>::max(), L'\n');
    std::getline(std::wcin, inputWord);
    inputWord = toLowerCase(inputWord);

    // Check if the edited word is currently in the table or not
    result = this->appDict.find_In_Table(inputWord);
    if (result == empty) {
        set_Color(0, 4);
        std::wcout << std::endl << std::setw(86) << L"FAILED   " << std::endl;
        set_Color(0, 7);
        std::wcout << std::setw(105) << std::endl << L"o------------------------------------------------o" << std::endl;
        set_Color(0, 4);
        std::wcout << std::setw(101) << std::endl << L"Fail! This word isn't in the dictionary!" << std::endl;
        set_Color(0, 7);
        std::wcout << std::setw(105) << std::endl << L"o------------------------------------------------o" << std::endl;
        return;
    }
    else {
        std::wcout << result;
    }

    int userChoice;
    std::wcout << std::endl;
    set_Color(0, 3);
    std::wcout << std::setw(120) << L"\t________________________________________________________________________\n";
    std::wcout << std::setw(120) << L"\to----------------------------------------------------------------------o\n";
    std::wcout << std::setw(120) << L"\t|                       Choose your editing option                     |\n";
    std::wcout << std::setw(120) << L"\to----------------------------------------------------------------------o\n";
    std::wcout << std::setw(120) << L"\t|                                                                      |\n";
    std::wcout << std::setw(120) << L"\t|                         1. Edit English word                         |\n";
    std::wcout << std::setw(120) << L"\t|                         2. Edit word's pronunciation                 |\n";
    std::wcout << std::setw(120) << L"\t|                         3. Edit word's type                          |\n";
    std::wcout << std::setw(120) << L"\t|                         4. Edit Vietnamese meaning                   |\n";
    std::wcout << std::setw(120) << L"\t|                         5. Return                                    |\n";
    std::wcout << std::setw(117) << L"\t|                                                                      |\n";
    std::wcout << std::setw(120) << L"\to----------------------------------------------------------------------o\n";
    set_Color(0, 7);
    // Validate choices
    bool isSelected = false;
    int selection;
    do {
        int a;
        //std::wcout << L"\n==>> Select one function: ";
        fflush(stdin);
        //std::wcin >> temp;
        a = pickMenu2();
        selection = a;
        if (selection == 1 || selection == 2 || selection == 3 ||
            selection == 4 || selection == 5) {
            isSelected = true;
        }
        else {
            set_Color(0, 4);
            std::wcout << std::endl << std::setw(91) << L"Fail! Invalid choice!" << std::endl;
            set_Color(0, 7);
        }
    } while (!isSelected);

    this->appDict.edit_In_Table(inputWord, selection);
}

void Dictionary::updateToFile() {
    Word temp;
    std::wfstream input;
    input.open(L"./data/input.txt", std::ios::out);
    std::locale loc(std::locale(), new std::codecvt_utf8<wchar_t>);
    input.imbue(loc);
    input.close();

    for (int i = 0; i < this->appDict.size_Of_Table; i++) {
        if (this->appDict.table[i].isEmpty())
            continue;
        this->appDict.table[i].save_List_to_File();
    }
}

Dictionary::~Dictionary() {
    system("cls");
    set_Color(0, 2);
    std::wcout << std::setw(90) << L"Waiting for cleaning memory..." << std::endl;
    std::wcout << std::setw(74) << L"Cleaning done!" << std::endl;
    set_Color(0, 7);
}
