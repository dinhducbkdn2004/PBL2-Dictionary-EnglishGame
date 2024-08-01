#ifndef HASHTABLE_H
#define HASTABLE_H
#include <iostream>
#include "LinkedList.h"

class HashTable {
private:
	int size_Of_Table;
	LinkedList* table;
public:
	HashTable(int size = 400);
	~HashTable();

	int hash_Function(std::wstring value);
	bool add_To_Table(Word input);
	bool delete_From_Table(std::wstring inputWord);
	void edit_In_Table(std::wstring inputWord, int select);
	Word find_In_Table(std::wstring inputWord);	//find and return word
	void print_Table();

	friend class Dictionary;
};


#endif // !HASHTABLE_H
