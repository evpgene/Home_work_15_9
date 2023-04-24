#include "Chat.h"
#include "iostream"
#include "string.h"

Chat::Chat() {

}
Chat::~Chat() {

}

void Chat::reg(char _login[LOGINLENGTH], char _pass[], int pass_length) {
    hashTable.add(_login, *sha1(_pass, pass_length));
}
bool Chat::login(char _login[LOGINLENGTH], char _pass[], int pass_length) {
    if (!(hashTable.find(_login) ^ *sha1(_pass, pass_length))) {
        return true; // успешно
    }
    return false;
}
