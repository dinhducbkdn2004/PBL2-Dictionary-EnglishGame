#include "Word.h"
#include <string>
#include <iostream>
#include <fstream>
#include <iomanip>

void Word::readFromFile(std::wistream& input) {
	input >> eWord >> pronunciation >> type;
	std::getline(input, vnMeaning);

	// Remove leading and trailing whitespaces from meaning
	vnMeaning.erase(0, vnMeaning.find_first_not_of(L" \t"));
	vnMeaning.erase(vnMeaning.find_last_not_of(L" \t") + 1);
}

void Word::writeToFile(std::wostream& output) const {
	output << eWord << " " << pronunciation << " " << type << " " << vnMeaning << "\n";
}

Word::Word() {
	this->eWord = L"";
	this->type = L"";
	this->pronunciation = L"";
	this->vnMeaning = L"";
}

Word::Word(const Word& a) {
	this->eWord = a.eWord;
	this->type = a.type;
	this->pronunciation = a.pronunciation;
	this->vnMeaning = a.vnMeaning;
}

Word::~Word() {};

const Word& Word::operator=(const Word& x) {
	this->eWord = x.eWord;
	this->vnMeaning = x.vnMeaning;
	this->type = x.type;
	this->pronunciation = x.pronunciation;
	return *this;
}

std::wistream& operator>>(std::wistream& in, Word& a)
{
	std::wcout << std::endl;
	std::wcout << std::setw(91) << L"Enter English word: ";
	fflush(stdin);
	std::getline(std::wcin, a.eWord);

	std::wcout << std::setw(91) << L"Enter word's pronunciation: ";
	fflush(stdin);
	std::getline(std::wcin, a.pronunciation);

	std::wcout << std::setw(91) << L"Enter word's type: ";
	fflush(stdin);
	std::getline(std::wcin, a.type);

	std::wcout << std::setw(91) << L"Enter Vietnamese meaning: ";
	fflush(stdin);
	std::getline(std::wcin, a.vnMeaning);

	return in;
}

std::wostream& operator<<(std::wostream& out, const Word& a) {
	std::wcout << std::endl;
	std::wcout << std::setw(105) << L"o------------------------------------------------o" << std::endl;
	std::wcout << std::setw(86) << L"Searched Word: "; std::wcout << a.eWord << std::endl;
	std::wcout << std::setw(86) << L"Word's pronunciation: "; std::wcout << a.pronunciation << std::endl;
	std::wcout << std::setw(86) << L"Word's type: "; std::wcout << a.type << std::endl;
	std::wcout << std::setw(86) << L"Vietnamese meaning: "; std::wcout << a.vnMeaning << std::endl;
	std::wcout << std::setw(105) << L"o------------------------------------------------o" << std::endl;
	return out;
}

bool Word::operator==(Word a) {
	if (a.eWord != this->eWord)
		return false;
	if (a.vnMeaning != this->vnMeaning)
		return false;
	if (a.type != this->type)
		return false;
	if (a.pronunciation != this->pronunciation)
		return false;
	return true;
}