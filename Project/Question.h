#ifndef QUESTION_H
#define QUESTION_H
#include <iostream>

class Question {
protected:
    int score;

public:
    Question();
    Question(int);
    Question(const Question& a);
    virtual void Setup() = 0;
    virtual ~Question();
    virtual int Show() = 0;
};

Question::Question() {}

Question::Question(int score) {
    this->score = score;
}

Question::Question(const Question& a) {
    score = a.score;
}

Question::~Question() {}

#endif // !QUESTION_H
