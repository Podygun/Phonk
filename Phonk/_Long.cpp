#include "_Long.h"
#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>
#include <cctype>
#include <bitset>

using namespace std;

const string _Long::ClearBinary(const int decimalDigit) const {
	bitset<32> binary(decimalDigit);
	string final = binary.to_string();
	final = final.erase(0, final.find('1'));
	return final;
}

_Long::_Long() {}
_Long::_Long(const string binaryValue)
{
	for (size_t i = 0; i < binaryValue.length(); i++)
	{
		InsertLast(binaryValue[i]);
	}
}
// основа
void _Long::InsertLast(unsigned char symbol)
{
	InsertByPos(length, symbol);
}
void _Long::InsertFirst(unsigned char symbol)
{
	InsertByPos(0, symbol);
}
void _Long::InsertByPos(unsigned int pos, unsigned char symbol)
{
	if (symbol != 49 && symbol != 48) {
		cout << "ќшибка ввода" << endl;
		return;
	}
	if (pos > length || pos < 0) { cout << "¬ыход за пределы списка" << endl; return; }

	//if first head
	if (head == nullptr) {
		CreateHead(symbol);
		length++;
		return;
	}

	//if insert head
	if (pos == 0) {
		Node* newNode = new Node;
		newNode->symbol = symbol;
		newNode->next = head;
		newNode->prev = nullptr;
		head->prev = newNode;
		head = newNode;
		length++;
		return;
	}

	//if insert tail
	if (pos == length) {
		Node* newNode = new Node;
		newNode->symbol = symbol;
		newNode->prev = tail;
		tail->next = newNode;
		tail = newNode;
		length++;
		return;
	}

	Node* newNode = new Node;
	Node* currentNode = GetElementByPos(pos);

	newNode->symbol = symbol;
	newNode->prev = currentNode->prev;
	newNode->next = currentNode;
	currentNode->prev->next = newNode;
	currentNode->next->prev = newNode;

	length++;

}


void _Long::RemoveLast()
{
	Remove(length - 1);
}
void _Long::RemoveFirst()
{
	Remove(0);
}
void _Long::Remove(const unsigned int pos)
{
	if (pos >= length || pos < 0) {
		cout << "¬ыход за пределы списка" << endl;
		return;
	}
	//if delete head element
	if (pos == 0) {

		Node* currentNode = new Node;
		currentNode = GetElementByPos(pos);
		if (currentNode->next != nullptr) {
			currentNode->next->prev = nullptr;
			head = currentNode->next;
		}
		else {
			head = nullptr;
			tail = nullptr;
		}
		delete currentNode;
		length--;
		return;
	}

	//if delete tail element
	if (pos == length - 1) {
		Node* currentNode = new Node;
		currentNode = GetElementByPos(pos);
		currentNode->prev->next = nullptr;
		tail = currentNode->prev;
		delete currentNode;
		length--;
		return;
	}

	Node* currentNode = new Node;
	currentNode = GetElementByPos(pos);
	currentNode->prev->next = currentNode->next;
	currentNode->next->prev = currentNode->prev;
	delete currentNode;
	length--;
}

void _Long::Clear() {
	Node* it = head;
	while (it->next != nullptr) {
		Node* temp = it;
		it = it->next;
		delete temp;
		length--;
	}
	delete it;
	head = nullptr;
	tail = nullptr;
}


string _Long::GetFull() const
{
	if (head == nullptr) {
		return "0";
	}
	string digit = "";
	Node* iterator = head;

	do
	{
		digit += iterator->symbol;
		iterator = iterator->next;
		if (iterator == nullptr) break;
		if (iterator->next == nullptr)
		{
			digit += iterator->symbol;
			break;
		}
		if (iterator == iterator->next) break;
	} while (true);
	return digit;
}

void _Long::CreateHead(unsigned char symbol)
{
	Node* newNode = new Node;
	newNode->symbol = symbol;
	newNode->next = nullptr;
	newNode->prev = nullptr;
	head = newNode;
	tail = newNode;
}

const int _Long::StrToBin(const string binaryStr) const
{
	int test = stoi(binaryStr, nullptr, 2);
	return test;
}

unsigned int _Long::Count() const
{
	return this->length;
}

_Long* _Long::Sum (const _Long& other) {

	_Long newLong;

	Node* iterator1 = this->GetTail();	//  итератор первого списка с хвоста
	Node* iterator2 = other.GetTail();	//  итератор второго списка с хвоста
	int dopSymbol = 0;

	while (iterator1 != nullptr || iterator2 != nullptr) {
		int digit1 = (iterator1 != nullptr) ? iterator1->symbol - '0' : 0;
		int digit2 = (iterator2 != nullptr) ? iterator2->symbol - '0' : 0;
		int sum = digit1 + digit2 + dopSymbol;
		newLong.InsertFirst(to_string(sum % 2)[0]);	//добавление цифры в начало нового списка
		dopSymbol = sum / 2;
		iterator1 = (iterator1 != nullptr) ? iterator1->prev : nullptr;
		iterator2 = (iterator2 != nullptr) ? iterator2->prev : nullptr;
	}
	if (dopSymbol) newLong.InsertFirst('1');	//добавление цифры в начало нового списка

	return &newLong;	//возврат нового списка
}

_Long* _Long::Diff (const _Long& other) {

	_Long newLong;

	Node* iterator1 = this->GetTail();	//  итератор первого списка с хвоста
	Node* iterator2 = other.GetTail();	//  итератор второго списка с хвоста
	bool dolg = false;

	while (iterator1 != nullptr || iterator2 != nullptr) {
		int digit1 = (iterator1 != nullptr) ? iterator1->symbol - '0' : 0;
		int digit2 = (iterator2 != nullptr) ? iterator2->symbol - '0' : 0;
		int diff = digit1 - digit2;

		if (diff < 0) 
		{
			dolg = true;
			diff = 1;
		}
		else 
			dolg = false;

		newLong.InsertFirst( to_string(diff)[0]);

		iterator1 = (iterator1 != nullptr) ? iterator1->prev : nullptr;
		iterator2 = (iterator2 != nullptr) ? iterator2->prev : nullptr;
	}

	//удаление нулей из начала списка
	for (Node* it = newLong.GetHead(); it->symbol != '1';)
	{
		it = it->next;
		newLong.RemoveFirst();
	}

	return &newLong;	//возврат нового списка
}

_Long* _Long::Multiply(const _Long& other) {

	
	int len1 = this->Count(),
		len2 = other.Count();

	string result(len1 + len2, '0');	//строка выступающа€ в качестве буфера при считании
										//столбиком произведени€

	Node* iterator1 = this->GetTail();  //  элемент первого списка, начина€ с хвоста

	int i = len1 - 1;
	while (iterator1 != nullptr)
	{
		int digit1 = iterator1->symbol - '0';
		int carry = 0;

		Node* iterator2 = other.GetTail();  //  элемент второго списка, начина€ с хвоста

		int j = len2 - 1;
		while (iterator2 != nullptr)
		{
			int digit2 = iterator2->symbol - '0';
			int product = digit1 * digit2 + carry + (result[i + j + 1] - '0');
			carry = product / 2;
			result[i + j + 1] = (product % 2) + '0';
			j--;
			iterator2 = iterator2->prev;
		}
		result[i] = carry + '0';

		iterator1 = iterator1->prev;
		i--;
	}
	_Long newLong(result);

	//удаление нулей из начала списка
	for (Node* it = newLong.GetHead(); it->symbol != '1';)
	{
		it = it->next;
		newLong.RemoveFirst();
	}



	return &newLong;
}


_Long* _Long::Division(const _Long& other) {

	/*if (this->GetFull() == "0" || other.GetFull() == "0") {
		cout << "ƒеление на ноль" << endl;
		return new _Long("");
	}*/
	int final = this->StrToBin(this->GetFull())
		/ other.StrToBin(other.GetFull());
	string value = ClearBinary(final);


	_Long newLong(value);
	
	return &newLong;
}

int _Long::GetDecimal() const {
	int decimal = 0;
	for (int i = 0; i < this->Count(); i++) {
		int digit = this->GetFull()[i] - '0';
		int weight = pow(2, this->Count() - 1 - i);
		decimal += digit * weight;
	}
	return decimal;
}

Node* _Long::GetElementByPos(const unsigned int pos) const {
	Node* it = new Node;
	it = head;
	for (unsigned int i = 0; i < pos; i++) it = it->next;
	return it;
}

Node* _Long::GetTail() const
{
	return this->tail;
}

Node* _Long::GetHead() const
{
	return this->head;
}
