#pragma once

#include "sha1.h"
//#include "test.h"
#include "string.h"
#include "HashTable.h"

typedef char Login[LOGINLENGTH]; // тип имя фрукта

class Chat {
public:
    Chat();
    ~Chat();
    void reg(char _login[LOGINLENGTH], char _pass[], int pass_length);
    bool login(char _login[LOGINLENGTH], char _pass[], int pass_length);

private:
    HashTable hashTable;
};

