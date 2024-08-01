#include "HashTable.h"
#include "Format.h"
#include <fstream>
#include <locale>
#include <codecvt>
#include <string>
#include <iomanip>

HashTable::HashTable(int size) {
	this->size_Of_Table = size;
	table = new LinkedList[this->size_Of_Table];

	Word temp;
	std::wstring trash;
	std::wifstream input(L"./data/input.txt");
	std::locale location(std::locale(), new std::codecvt_utf8<wchar_t>);

	if (input.fail()) {
		std::wcout << L"Error opening data file failed!\n";
	}
	else {
		input.imbue(location);
		while (!input.eof()) {
			input >> temp.eWord;

			input >> temp.pronunciation;

			input >> temp.type;

			getline(input, trash, L'\n');
			getline(input, temp.vnMeaning, L'\n');

			this->add_To_Table(temp);
		}
	}
	input.close();
}

HashTable::~HashTable() {
	for (int i = 0; i < this->size_Of_Table; i++) {
		table[i].~LinkedList();
	}
	delete[] table;
}

int HashTable::hash_Function(std::wstring value) {
	int i;
	int c = 0;
	unsigned long hash = 5381;
	for (i = 0; i < value.length(); ++i) {
		c = (int)value.at(i);
		hash = ((hash << 5) + hash) + c;
	}
	return hash % this->size_Of_Table;
}

bool HashTable::add_To_Table(Word input) {
	bool check;
	int position = hash_Function(input.eWord);
	check = table[position].add_Node(input);

	return check;
}

bool HashTable::delete_From_Table(std::wstring inputWord) {
	bool check;
	int position = hash_Function(inputWord);
	check = table[position].delete_Node(inputWord);

	return check;
}

void HashTable::edit_In_Table(std::wstring inputWord, int select) {
	/*
   case 1: edit eWord
   case 2: edit type
   case 3: edit pronunciation
   case 4: edit vnMeaning
   case 5: break and return
   */
	switch (select) {
	case 1: {
		Word editedWord = this->find_In_Table(inputWord);
		std::wcout << std::setw(90) << L"Enter edited English word: ";
		//std::wcin.ignore(std::numeric_limits<std::streamsize>::max(), L'\n');
		std::getline(std::wcin, editedWord.eWord);

		if (this->add_To_Table(editedWord)) {
			this->delete_From_Table(inputWord);
		}
		else {
			set_Color(0, 4);
			std::wcout << std::endl << std::setw(107) << L"Fail! The edited word has already in the dictionary!\n";
			set_Color(0, 7);
			return;
		}
		break;
	}
	case 2: {
		Word editedWord = this->find_In_Table(inputWord);
		std::wcout << std::setw(90) << L"Enter edited word's pronunciation: ";
		//std::wcin.ignore(std::numeric_limits<std::streamsize>::max(), L'\n');
		std::getline(std::wcin, editedWord.pronunciation);

		this->delete_From_Table(inputWord);
		this->add_To_Table(editedWord);

		break;
	}
	case 3: {
		Word editedWord = this->find_In_Table(inputWord);
		std::wcout << std::setw(90) << L"Enter edited word's type: ";
		//std::wcin.ignore(std::numeric_limits<std::streamsize>::max(), L'\n');
		std::getline(std::wcin, editedWord.type);

		this->delete_From_Table(inputWord);
		this->add_To_Table(editedWord);

		break;
	}
	case 4: {
		Word editedWord = this->find_In_Table(inputWord);
		std::wcout << std::setw(90) << L"Enter edited Vietnamese meaning: ";
		//std::wcin.ignore(std::numeric_limits<std::streamsize>::max(), L'\n');
		std::getline(std::wcin, editedWord.vnMeaning);

		this->delete_From_Table(inputWord);
		this->add_To_Table(editedWord);

		break;
	}
	case 5: {
		break;
	}
	}
	set_Color(0, 2);
	std::wcout << std::endl << std::setw(90) << L"Successfully edited!" << std::endl;
	set_Color(0, 7);
}

Word HashTable::find_In_Table(std::wstring inputWord) {
	Word tempWord;
	int pos_Of_Hash = hash_Function(inputWord);
	int pos_Of_Table = table[pos_Of_Hash].find_Node(inputWord);

	if (this->table[pos_Of_Hash].isEmpty() || pos_Of_Table == -1) {
		return tempWord;	//return an empty word if can't find inputword
	}
	else {
		tempWord = table[pos_Of_Hash].get_Node(pos_Of_Table);
		return tempWord;	//return searched word
	}
}

void HashTable::print_Table() {
	for (int i = 0; i < this->size_Of_Table; i++) {
		table[i].print_List();
	}
}