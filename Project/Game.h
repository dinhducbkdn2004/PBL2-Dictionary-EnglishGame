#ifndef GAME_H
#define GAME_H
#include <iostream>
const int MAX_VOCABULARIES = 512;

class Game {
protected:
    int Score;
    int NumOfQues;
    int Level;
    int best_score;
    int n;
    std::string* input;
    int index;
    int currentQuestionCount;

public:
    Game();
    Game(int, int, int);
    Game(const Game& a);
    ~Game();

    int RandomNumber();
    std::string* removeDupWord(std::string, int);

    void GetBest();
    void GetIndex();
    void GetData();
    void GetOverlap();

    void SaveBest();
    void SaveIndex();
    void SaveData();

    void Start(const std::string& username);
    void GameSelect();
    void RunFill();
    void RunSelect();
    void Practice();
    void ResetGameData();
    void playGame(const std::string& username);
    void setPasswordReference(const std::string& username);
};

#endif // !GAME_H