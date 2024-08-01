#include "Game.h"
#include <string>
#include <fstream>
#include <random>
#include <conio.h>
#include <codecvt>
#include <locale>
#include "SelectGame.h"
#include "select.h"
#include "FillingGame.h"
#include "Format.h"
#include "Word.h"

std::string globalUsername;

Game::Game() : Score(0), NumOfQues(5), n(5), Level(1), currentQuestionCount(0) {}

Game::Game(int score, int num, int level) : Score(score), NumOfQues(num), n(5), Level(level) {}

Game::Game(const Game& a) : Score(a.Score), NumOfQues(a.NumOfQues), n(5), Level(a.Level) {}

Game::~Game() {}

bool compareWords(const Word& a, const Word& b) {
    return a.eWord < b.eWord;
}

void organizeVocabulary(const std::string& inputFileName, const std::string& outputFileName) {
    std::wifstream inputFile(inputFileName);
    Word vocabularies[MAX_VOCABULARIES];
    int vocabularyCount = 0;

    while (!inputFile.eof() && vocabularyCount < MAX_VOCABULARIES) {
        vocabularies[vocabularyCount].readFromFile(inputFile);
        vocabularyCount++;
    }

    inputFile.close();

    // Sort vocabulary
    std::sort(vocabularies, vocabularies + vocabularyCount, compareWords);

    // Write sorted vocabulary to output file
    std::wofstream outputFile(outputFileName);

    for (int i = 0; i < vocabularyCount; ++i) {
        vocabularies[i].writeToFile(outputFile);
    }

    outputFile.close();
}

void Game::setPasswordReference(const std::string& username) {
    globalUsername = username;

}

void Game::Start(const std::string& username) {
    setPasswordReference(username);
    GetIndex();
    GetBest();
    system("cls");
    fflush(stdin);
    set_Color(0, 3);
    std::wcout << std::setw(120) << L"\t                                                                                \n";
    std::wcout << std::setw(120) << L"\t________________________________________________________________________\n";
    std::wcout << std::setw(120) << L"\to----------------------------------------------------------------------o\n";
    std::wcout << std::setw(120) << L"\t|                            PRACTICING GAME                           |\n";
    std::wcout << std::setw(120) << L"\to----------------------------------------------------------------------o\n";
    std::wcout << std::setw(120) << L"\t|                                                                      |\n";
    std::wcout << std::setw(120) << L"\t|                              1. Play                                 |\n";
    std::wcout << std::setw(120) << L"\t|                              2. Practice                             |\n";
    std::wcout << std::setw(120) << L"\t|                              3. Reset                                |\n";
    std::wcout << std::setw(120) << L"\t|                              4. Logout                               |\n";
    std::wcout << std::setw(120) << L"\t|                                                                      |\n";
    std::wcout << std::setw(120) << L"\to----------------------------------------------------------------------o\n";
    set_Color(0, 7);
    int a;
    a = pickMenu1();
    if (a == 1) {
        GameSelect();
    }
    else if (a == 2) {
        Practice();
    }
    else if (a == 3) {
        ResetGameData();
    }
    else {
        return;
    }
}

void Game::GetIndex() {
    std::ifstream f("./data/GameData/" + globalUsername + "_index.txt");
    f >> index;
    f.close();
}

void Game::GetOverlap() {
    std::ofstream f("./data/GameData/" + globalUsername + "_overlap.txt");
    f << currentQuestionCount;
    f.close();
}

void Game::GetBest() {
    std::ifstream f("./data/best_score.txt");
    f >> best_score;
    f.close();
}

void Game::GetData() {
    input = new std::string[n];
    int k = 0;
    char temp[MAX];

    std::ifstream f("./data/input.txt");
    for (int i = 0; i < index; i++) {
        f.getline(temp, MAX); // ignore offset
        f.getline(temp, MAX);
    }

    for (int i = 0; i < n; i++) {
        f.getline(temp, MAX);
        input[k] = temp;
        f.getline(temp, MAX);
        input[k] += " ";
        input[k] += temp;
        std::string* inputt = removeDupWord(input[k], 4);
        k++;
    }
    f.close();

    // Ghi data
    std::ofstream out("./data/GameData/" + globalUsername + ".txt", std::ios::app);
    for (int i = 0; i < n; i++) {
        out << input[i] << '\n';
    }
    out.close();

    index = index + n;
    SaveIndex();
}

void Game::SaveIndex() {
    std::ofstream f("./data/GameData/" + globalUsername + "_index.txt", std::ios::out);
    f << index;
    f.close();
}

void Game::SaveBest() {
    std::ofstream f("./data/best_score.txt", std::ios::out);
    f << best_score;
    f.close();
}

void Game::SaveData() {
    SaveIndex();
    SaveBest();
}

std::string* Game::removeDupWord(std::string str, int n) {
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

int Game::RandomNumber() {
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_real_distribution<double> dist(0.0, 100.0);
    return dist(mt);
}

void Game::playGame(const std::string& username) {
    system("cls");
    set_Color(0, 9);
    std::wcout << std::endl;
    std::wcout << std::setw(104) << L"<<===== PLAYING GAME =====>>" << std::endl;
    Game dictGame;
    std::wcout << std::endl << std::setw(98) << L"Loading game..." << std::endl;
    set_Color(0, 7);
    system("pause > nul");
    dictGame.Start(username);
}

void Game::Practice() {
    if (index == 0) {
        system("cls");
        set_Color(0, 4);
        std::wcout << L"Opps! You haven't learnt nothing! Praticing at game first!" << std::endl;
        set_Color(0, 7);
    }
    else {
        std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
        int w = 18;
        std::ifstream f("./data/GameData/" + globalUsername + ".txt");
        system("cls");
        set_Color(0, 2);
        std::wcout << L"\nWoahh! You have already learnt " << index << " word!\n" << std::endl;
        set_Color(0, 7);
        char temp[MAX];
        std::wcout << std::setfill(L' ');
        std::wcout << L"\t|| " << std::setw(w) << L"Word" << std::setw(w)
            << L"||" << std::setw(w) << L"Pronounce" << std::setw(w)
            << L"||" << std::setw(w / 2) << L"Type" << std::setw(w / 2)
            << L"||" << std::setw(w) << L"Mean" << std::setw(w) << L" ||" << std::endl;
        std::wcout << L"\t||" << std::setfill(L'=') << std::setw(7 * w + 1) << L"||" << std::endl;
        std::wcout << std::setfill(L' ');
        for (int i = 0; i < index; i++) {
            f.getline(temp, MAX);
            std::string* a = removeDupWord(temp, 4);
            std::wcout << L"\t|| " << std::left << std::setw(2 * w - 2) << converter.from_bytes(a[0])
                << L"|| " << std::setw(2 * w - 3) << converter.from_bytes(a[1])
                << L"|| " << std::setw(w - 3) << converter.from_bytes(a[2])
                << L"|| " << std::setw(2 * w - 3) << converter.from_bytes(a[3]) << L"||" << std::endl;
        }
        std::wcout << L"\t||" << std::right << std::setfill(L'=') << std::setw(7 * w + 1) << L"||" << std::endl;
        std::wcout << std::setfill(L' ');
        f.close();
        set_Color(0, 14);
        std::wcout << "Do you want to sort and organize vocabulary?\n";
        std::wcout << "Yes(1)/No(0)\n";
        set_Color(0, 7);
        int c;
        c = pickMenu1();
        if (c == 1) {
            std::wofstream outputFile("./data/GameData/" + globalUsername + "_SORT.txt");
            organizeVocabulary("./data/GameData/" + globalUsername + ".txt", "./data/GameData/" + globalUsername + "_SORT.txt");
            std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
            int w = 18;
            std::ifstream f("./data/GameData/" + globalUsername + "_SORT.txt");
            system("cls");
            set_Color(0, 2);
            std::wcout << L"\nWoahh! You have already learnt " << index << " word!\n" << std::endl;
            set_Color(0, 7);
            char temp[MAX];
            std::wcout << std::setfill(L' ');
            std::wcout << L"\t|| " << std::setw(w) << L"Word" << std::setw(w)
                << L"||" << std::setw(w) << L"Pronounce" << std::setw(w)
                << L"||" << std::setw(w / 2) << L"Type" << std::setw(w / 2)
                << L"||" << std::setw(w) << L"Mean" << std::setw(w) << L" ||" << std::endl;
            std::wcout << L"\t||" << std::setfill(L'=') << std::setw(7 * w + 1) << L"||" << std::endl;
            std::wcout << std::setfill(L' ');
            for (int i = 0; i < index + 1; i++) {
                f.getline(temp, MAX);
                std::string* a = removeDupWord(temp, 4);
                std::wcout << L"\t|| " << std::left << std::setw(2 * w - 2) << converter.from_bytes(a[0])
                    << L"|| " << std::setw(2 * w - 3) << converter.from_bytes(a[1])
                    << L"|| " << std::setw(w - 3) << converter.from_bytes(a[2])
                    << L"|| " << std::setw(2 * w - 3) << converter.from_bytes(a[3]) << L"||" << std::endl;
            }
            std::wcout << L"\t||" << std::right << std::setfill(L'=') << std::setw(7 * w + 1) << L"||" << std::endl;
            std::wcout << std::setfill(L' ');
            f.close();
        }
    }
    system("pause");
    Start(globalUsername);
}

void Game::ResetGameData() {
    // clear GameData.txt
    std::ofstream f("./data/GameData/" + globalUsername + ".txt", std::ios::out);
    f.close();

    std::ofstream out("./data/GameData/" + globalUsername + "_index.txt", std::ios::out);
    out << 0;
    out.close();

    std::ofstream outOverlap("./data/GameData/" + globalUsername + "_overlap.txt", std::ios::out);
    outOverlap << 0;
    outOverlap.close();

    std::ofstream outBest("./data/best_score.txt", std::ios::out);
    outBest << 0;
    outBest.close();

    std::wcout << L"Reset data successfully! " << std::endl;
    system("pause");
    Start(globalUsername);
}

void Game::GameSelect() {
    system("cls");
    set_Color(0, 3);
    std::wcout << std::setw(120) << L"\t________________________________________________________________________\n";
    std::wcout << std::setw(120) << L"\to----------------------------------------------------------------------o\n";
    std::wcout << std::setw(120) << L"\t|                            PRACTICING GAME                           |\n";
    std::wcout << std::setw(120) << L"\to----------------------------------------------------------------------o\n";
    std::wcout << std::setw(120) << L"\t|                                                                      |\n";
    std::wcout << std::setw(120) << L"\t|                             1. Filling Game                          |\n";
    std::wcout << std::setw(120) << L"\t|                             2. Selecting Game                        |\n";
    std::wcout << std::setw(120) << L"\t|                             3. Back                                  |\n";
    std::wcout << std::setw(120) << L"\t|                                                                      |\n";
    std::wcout << std::setw(120) << L"\to----------------------------------------------------------------------o\n";
    set_Color(0, 7);
    int a;
    a = pickMenu1();
    if (a == 1) {
        RunFill();
    }
    else if (a == 2) {
        RunSelect();
    }
    else if (a == 3) {
        Start(globalUsername);
    }
    else {
        return;
    }
}

void Game::RunFill()
{
    system("cls");
    system("cls");
    set_Color(0, 3);
    std::wcout << std::setw(120) << L"\t________________________________________________________________________\n";
    std::wcout << std::setw(120) << L"\to----------------------------------------------------------------------o\n";
    std::wcout << std::setw(120) << L"\t|                           SELECT QUESTION PACK                       |\n";
    std::wcout << std::setw(120) << L"\to----------------------------------------------------------------------o\n";
    std::wcout << std::setw(120) << L"\t|                                                                      |\n";
    std::wcout << std::setw(120) << L"\t|                             1. 10 question                           |\n";
    std::wcout << std::setw(120) << L"\t|                             2. 15 question                           |\n";
    std::wcout << std::setw(120) << L"\t|                             3. 20 question                           |\n";
    std::wcout << std::setw(120) << L"\t|                             4. 30 question                           |\n";
    std::wcout << std::setw(120) << L"\t|                             5. Back                                  |\n";
    std::wcout << std::setw(120) << L"\t|                                                                      |\n";
    std::wcout << std::setw(120) << L"\to----------------------------------------------------------------------o\n";
    set_Color(0, 7);
    int a;
    a = pickMenu1();
    if (a == 1)
    {
        this->NumOfQues = 10;
        n = 10;
    }
    else if (a == 2)
    {
        this->NumOfQues = 15;
        n = 15;
    }
    else if (a == 3)
    {
        this->NumOfQues = 20;
        n = 20;
    }
    else if (a == 4)
    {
        this->NumOfQues = 30;
        n = 30;
    }
    else if (a == 5)
        GameSelect();
    else
        return;


    Score = 0;
    GetOverlap();
    GetData();
    system("cls");
    set_Color(0, 9);
    std::wcout << std::setw(60) << L"You have selected " << NumOfQues << " questions pack. Let's started!\n"
        << endl;
    set_Color(0, 7);
    for (int i = 0; i < NumOfQues; i)
    {
        currentQuestionCount++;
        Find* b;
        std::wcout << std::setw(51) << L"                                          >>>-------------------------o0o-------------------------<<<";
        std::wcout << std::endl << std::endl << std::setw(51) << L"Question " << ++i << L": ";
        b = new Find;
        b->SetOffset(index - n, index, Score, globalUsername);
        Score += b->Show();
        std::wcout << std::endl
            << std::endl;
        if (i >= NumOfQues)
            break;
    }

    // Assign & Save best_score
    if (Score > best_score)
    {
        set_Color(0, 2);
        std::wcout << std::setw(74) << L"Hurray! You make new best score!" << std::endl;
        std::wcout << std::setw(60) << L"Your total score: " << Score << std::endl;
        std::wcout << std::setw(60) << L"Best score: " << best_score << std::endl;
        std::wcout << std::setw(73) << L"Let's break the record again!!!" << std::endl;
        set_Color(0, 7);
        best_score = Score;
        SaveBest();
    }
    else
    {
        set_Color(0, 2);
        std::wcout << std::setw(60) << L"Your total score: " << Score << std::endl;
        std::wcout << std::setw(60) << L"Best score: " << best_score << std::endl;
        std::wcout << std::setw(73) << L"Don't worry! Let's try again!!!" << std::endl;
        set_Color(0, 7);
    }

    system("pause");
    Start(globalUsername);
}

void Game::RunSelect()
{
    system("cls");
    system("cls");
    system("cls");
    set_Color(0, 3);
    std::wcout << std::setw(120) << L"\t________________________________________________________________________\n";
    std::wcout << std::setw(120) << L"\to----------------------------------------------------------------------o\n";
    std::wcout << std::setw(120) << L"\t|                           SELECT QUESTION PACK                       |\n";
    std::wcout << std::setw(120) << L"\to----------------------------------------------------------------------o\n";
    std::wcout << std::setw(120) << L"\t|                                                                      |\n";
    std::wcout << std::setw(120) << L"\t|                             1. 10 question                           |\n";
    std::wcout << std::setw(120) << L"\t|                             2. 15 question                           |\n";
    std::wcout << std::setw(120) << L"\t|                             3. 20 question                           |\n";
    std::wcout << std::setw(120) << L"\t|                             4. 30 question                           |\n";
    std::wcout << std::setw(120) << L"\t|                             5. Back                                  |\n";
    std::wcout << std::setw(120) << L"\t|                                                                      |\n";
    std::wcout << std::setw(120) << L"\to----------------------------------------------------------------------o\n";
    set_Color(0, 7);
    int a;
    a = pickMenu1();
    if (a == 1)
    {
        this->NumOfQues = 10;
        n = 10;
    }
    else if (a == 2)
    {
        this->NumOfQues = 15;
        n = 15;
    }
    else if (a == 3)
    {
        this->NumOfQues = 20;
        n = 20;
    }
    else if (a == 4)
    {
        this->NumOfQues = 30;
        n = 30;
    }
    else if (a == 5)
        GameSelect();
    else
        return;

    Score = 0;
    GetOverlap();
    GetData();
    system("cls");
    set_Color(0, 9);
    std::wcout << std::setw(60) << L"You have selected " << NumOfQues << " questions pack. Let's started!\n"
        << std::endl;
    set_Color(0, 7);
    for (int i = 0; i < NumOfQues; i)
    {
        currentQuestionCount++;
        Select* a;

        //===========
        a = new Select1;
        std::wcout << std::setw(111) << L">>>-------------------------o0o-------------------------<<<";
        std::wcout << std::endl << std::endl << std::setw(47) << setfill(L' ') << L"Question " << ++i << L": ";
        a->SetOffset(index - n, index, Score, globalUsername);
        Score += a->Show();
        std::wcout << std::endl
            << std::endl;
        if (i >= NumOfQues)
            break;
        //===========
        std::wcout << std::setw(111) << L">>>-------------------------o0o-------------------------<<<";
        std::wcout << std::endl << std::endl << std::setw(47) << L"Question " << ++i << L": ";
        a = new Select2;
        a->SetOffset(index - n, index, Score, globalUsername);
        Score += a->Show();
        std::wcout << std::endl
            << std::endl;
        if (i >= NumOfQues)
            break;
        //===========
        std::wcout << std::setw(111) << L">>>-------------------------o0o-------------------------<<<";
        std::wcout << std::endl << std::endl << std::setw(47) << L"Question " << ++i << L": ";
        a = new Select3;
        a->SetOffset(index - n, index, Score, globalUsername);
        Score += a->Show();
        std::wcout << std::endl
            << std::endl;
        if (i >= NumOfQues)
            break;
        //===========
        std::wcout << std::setw(111) << L">>>-------------------------o0o-------------------------<<<";
        std::wcout << std::endl << std::endl << std::setw(47) << L"Question " << ++i << L": ";
        a = new Select4;
        a->SetOffset(index - n, index, Score, globalUsername);
        Score += a->Show();
        std::wcout << std::endl
            << std::endl;
        if (i >= NumOfQues)
            break;
    }

    // Assign & Save best_score
    if (Score > best_score)
    {
        set_Color(0, 2);
        std::wcout << std::setw(71) << L"Hurray! You make new best score!" << std::endl;
        std::wcout << std::setw(57) << L"Your total score: " << Score << std::endl;
        std::wcout << std::setw(57) << L"Best score: " << best_score << std::endl;
        std::wcout << std::setw(70) << L"Let's break the record again!!!" << std::endl;
        set_Color(0, 7);
        best_score = Score;
        SaveBest();
    }
    else
    {
        set_Color(0, 2);
        std::wcout << std::setw(57) << L"Your total score: " << Score << std::endl;
        std::wcout << std::setw(57) << L"Best score: " << best_score << std::endl;
        std::wcout << std::setw(70) << L"Don't worry! Let's try again!!!" << std::endl;
        set_Color(0, 7);
    }

    system("pause");
    Start(globalUsername);
}
