#pragma once
#include "Node.h"
#include <iostream>

using namespace std;



class _Long
{
private:
	Node* head = nullptr;
	Node* tail = nullptr;
	unsigned int length = 0;
public:
	const string ClearBinary(const int decimalDigit) const;
	_Long();
	_Long(string hexValue);

	void InsertLast(unsigned char data);
	void InsertFirst(unsigned char symbol);
	void InsertByPos(unsigned int pos, unsigned char symbol);

	void RemoveLast();
	void RemoveFirst();
	void Remove(const unsigned int pos);

	void Clear();

	string GetFull() const;
	void CreateHead(unsigned char symbol);
	const int StrToBin(const string hexString) const;
	unsigned int Count() const;

	_Long* Sum(const _Long& other);
	_Long* Diff(const _Long& other);
	_Long* Multiply(const _Long& other);
	_Long* Division(const _Long& other);

	int GetDecimal() const;

	Node* GetElementByPos(const unsigned int pos) const;
	Node* GetTail() const;
	Node* GetHead() const;

	bool operator == (const _Long& other) const {
		return this->GetDecimal() == other.GetDecimal();
	};
	bool operator != (const _Long& other) const {
		return this->GetDecimal() != other.GetDecimal();
	};
	bool operator <	 (const _Long& other) const {
		return this->GetDecimal() < other.GetDecimal();
	};
	bool operator >	 (const _Long& other) const {
		return this->GetDecimal() > other.GetDecimal();
	};
	bool operator <= (const _Long& other) const {
		return this->GetDecimal() <= other.GetDecimal();
	};
	bool operator >= (const _Long& other) const {
		return this->GetDecimal() >= other.GetDecimal();
	};
};

