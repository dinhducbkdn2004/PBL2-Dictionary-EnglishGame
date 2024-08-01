#include "LinkedList.h"
#include <fstream>
#include <locale>
#include <codecvt>

LinkedList::LinkedList() {
	this->head = NULL;
}

LinkedList::~LinkedList() {
	Node* temp = NULL;
	while (this->head) {
		temp = this->head;
		this->head = this->head->next;
		free(temp);
	}
}

void LinkedList::insertWord(const Word& newWord) {
	Node* newNode = new Node();
	newNode->data = newWord;

	// If the list is empty or the new word should be the new head
	if (head == nullptr || newWord < head->data) {
		newNode->next = head;
		head = newNode;
		return;
	}

	// Find the correct position to insert the new node
	Node* current = head;
	while (current->next != nullptr && !(newWord < current->next->data)) {
		current = current->next;
	}

	// Insert the new node in the middle or at the end of the list
	newNode->next = current->next;
	current->next = newNode;
}

Word LinkedList::get_Node(int position) {
	int k = 0;
	Node* temp = this->head;
	while (k != position && temp != NULL) {
		temp = temp->next;
		++k;
	}

	return temp->data;
}

bool LinkedList::delete_Node(std::wstring deletedWord) {
	int position = this->find_Node(deletedWord);
	int k = 0;
	Node* temp = this->head;

	if (head == NULL || position == -1) {
		return false;
	}
	if (this->head->next == NULL || position == 0) {
		this->head = this->head->next;
	}
	else {
		while (temp != NULL && k != position - 1)
		{
			temp = temp->next;
			++k;
		}
		temp->next = temp->next->next;
	}
	return true;
}

bool LinkedList::isEmpty() {
	if (this->head == NULL)
		return true;
	return false;
}

bool LinkedList::add_Node(Word newWord) {
	if (this->isEmpty() || this->find_Node(newWord.eWord) == -1) {	// If word hasn't already in list => to add
		Node* temp = new Node();
		temp->data = newWord;
		temp->next = this->head;
		head = temp;

		return true;
	}
	else {
		return false;	// If word hasn already in list => return false
	}
}

int LinkedList::length_Of_List() {
	int lenght = 0;
	Node* temp = this->head;
	for (temp; temp != NULL; temp = temp->next)
	{
		++lenght;
	}
	return lenght;
}

int LinkedList::find_Node(std::wstring eWord) {
	Node* temp = this->head;
	int position = 0;
	for (temp; temp != NULL; temp = temp->next) {
		if (temp->data.eWord == eWord)
		{
			return position;
		}
		++position;
	}
	return -1;
}

void LinkedList::print_List()
{
	Node* temp = this->head;
	for (temp; temp != NULL; temp = temp->next) {
		std::wcout << temp->data << L" --> ";
	}
}

void LinkedList::save_List_to_File() {
	Node* temp = this->head;
	Word tempWord;

	std::wfstream input;
	input.open(L"./data/input.txt", std::ios::app);	//New data will be added to the file without overwriting existing content
	std::locale location(std::locale(), new std::codecvt_utf8<wchar_t>);
	input.imbue(location);

	for (temp; temp != NULL; temp = temp->next) {
		tempWord = temp->data;
		input << tempWord.eWord << L" " << tempWord.pronunciation << L" " << tempWord.type << "\n";
		input << tempWord.vnMeaning << "\n";
	}
}

void LinkedList::insertionSort() {
	if (head == nullptr || head->next == nullptr) {
		return;
	}

	Node* sortedList = nullptr;
	Node* current = head;

	while (current != nullptr) {
		Node* nextNode = current->next;

		if (sortedList == nullptr || current->data.eWord < sortedList->data.eWord) {
			current->next = sortedList;
			sortedList = current;
		}
		else {
			Node* temp = sortedList;
			while (temp->next != nullptr && current->data.eWord < temp->next->data.eWord) {
				temp = temp->next;
			}
			current->next = temp->next;
			temp->next = current;
		}

		current = nextNode;
	}

	head = sortedList;
}

void LinkedList::swap(Node* a, Node* b) {
	Word temp = a->data;
	a->data = b->data;
	b->data = temp;
}