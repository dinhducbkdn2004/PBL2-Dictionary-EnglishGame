#ifndef WORD_H
#define WORD_H
#include <iostream>
#include <algorithm>

class Word {
public:
    std::wstring eWord;
    std::wstring type;
    std::wstring pronunciation;
    std::wstring vnMeaning;

    Word();
    Word(const Word& a);
    ~Word();
    const Word& operator=(const Word& x);
    bool operator==(Word a);
    bool operator<(const Word& other) const {
        return eWord < other.eWord;
    }

    void readFromFile(std::wistream& input);
    void writeToFile(std::wostream& output) const;

    friend std::wistream& operator>>(std::wistream& in, Word& a);
    friend std::wostream& operator<<(std::wostream& out, const Word& a);

    friend class LinkedList;
    friend class HashTable;
    friend class Dictionary;
};

#endif // !WORD_H
