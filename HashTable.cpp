
#include "hashtable.h"

#include <iostream>
#include <string.h>

HashTable::HashTable() {
	count = 0;
	mem_size = 8;
	data = new AuthData[mem_size];
}

HashTable::HashTable(const HashTable& other)
{

	mem_size = other.mem_size;
	count = other.count;
	data = new AuthData[mem_size];
	for (size_t i = 0; i < mem_size; i++)
	{
		data[i] = other.data[i];
	}
}
HashTable& HashTable::operator=(HashTable& other)
{
	if (this != &other) // protection against copy into self
	{
		mem_size = other.mem_size;
		count = other.count;
		data = new AuthData[mem_size];
		for (size_t i = 0; i < mem_size; i++)
		{
			data[i] = other.data[i];
		}
	}
	return *this;
}
;



HashTable::~HashTable() {
	delete[] data;
}



int HashTable::hash_func(Login login, int offset) const {
	int sum = 0, i = 0;
	for (; i < LOGINLENGTH; i++) {
		sum += login[i];
	}
	const double A = 0.7;
	const int M = mem_size;
	return (int(M * (A * sum - int(A * sum))) + offset * offset) % M; //������������ ������������
}

void HashTable::del(Login login) {
	// ����� ����� �� ���� i �� 0 �� ������� �������
	for (int i = 0; i < mem_size; i++) {
		int index = hash_func(login, i);
		if (!strcmp(data[index].login, login) && data[index].status == enPairStatus::engaged) {
			// ������� ��������������� ��������
			data[index].status = enPairStatus::deleted;
			count--;
			return;
		}
		else if (data[index].status == enPairStatus::free) {
			return;
		}
	}
	return;
}
int HashTable::find(Login login) const {
	// ����� ����� �� ���� i �� 0 �� ������� �������
	for (int i = 0; i < mem_size; i++) {
		int index = hash_func(login, i);
		if (!strcmp(data[index].login, login) && data[index].status == enPairStatus::engaged) {
			// ������� ��������������� ��������
			return data[index].pass_sha1_hash;
		}
		else if (data[index].status == enPairStatus::free) {
			return -1;
		}
	}
	return -1;
}

void HashTable::resize() {
	AuthData* save_array = data; // ���������� ������ ������
	int oldSize = mem_size;

	mem_size *= 2;  // ����������� ������ � ��� ����  
	count = 0; // �������� ���������� ���������
	data = new AuthData[mem_size]; // �������� ����� ������
	for (int i = 0; i < mem_size; i++) {
		data[i].status = enPairStatus::free;
	}

	for (int i = 0; i < oldSize; i++) {
		// ������������� ���� � ��������� � ����� ������
		if (save_array[i].status == enPairStatus::engaged)
			add(save_array[i].login, save_array[i].pass_sha1_hash);
	}
	delete[] save_array;
}


void HashTable::clean() {
	AuthData* save_array = data; // ���������� ������ ������

	count = 0; // �������� ���������� ���������
	data = new AuthData[mem_size]; // �������� ����� ������
	for (int i = 0; i < mem_size; i++) {
		data[i].status = enPairStatus::free;
	}

	for (int i = 0; i < mem_size; i++) {
		// ������������� ���� � ��������� � ����� ������
		if (save_array[i].status == enPairStatus::engaged)
			add(save_array[i].login, save_array[i].pass_sha1_hash);
	}
	delete[] save_array;
}


void HashTable::add(Login login, int hash) {
	bool found_free{ false };
	int index = -1;
	do
	{
		int i = 0;
		// ����� ����� �� ���� i �� 0 �� ������� �������
		for (; i < mem_size; i++) {
			index = hash_func(login, i);
			if (data[index].status == enPairStatus::free) {
				// ������� ������ ������, �������� ��
				found_free = true;
				break;
			}
		}
		if (i >= mem_size && !found_free)
		{
			resize(); // ��� ���������, ��� �����
			std::cout << "resize" << std::endl;
			std::cout << mem_size << std::endl;
		}
	} while (!found_free);


	// ������ � ��������� ������ ����
	data[index] = AuthData(login, hash);
	count++;
}
