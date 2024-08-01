#ifndef LINKEDLIST_H
#define LINKEDLIST_H
#include <iostream>
#include "Word.h"

class Node {
private:
	Word data;
	Node* next;
public:
	Node() {
		next = NULL;
	}
	friend class LinkedList;
};

class LinkedList {
private:
	Node* head;
public:
	LinkedList();
	~LinkedList();

	void insertWord(const Word& newWord);
	int length_Of_List();
	Word get_Node(int position);
	bool delete_Node(std::wstring deletedWord);
	bool add_Node(Word newWord);
	bool isEmpty();
	int find_Node(std::wstring eWord);
	void print_List();
	void save_List_to_File();
	void insertionSort();
	void swap(Node* a, Node* b);
};



#endif // !LINKEDLIST_H
