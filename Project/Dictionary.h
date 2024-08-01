#ifndef DICTIONARY_H
#define DICTIONARY_H
#include <iostream>
#include "HashTable.h"

class Dictionary {
private:
    HashTable appDict;

public:
    Dictionary();

    void addNewWordToDictionary();
    void delWordFromDictionary();
    void searchWordInDictionary();
    void editWordInDictionary();
    //void playGame(const std::string& username);
    void updateToFile();
    ~Dictionary();
};

#endif // !DICTIONARY_H
