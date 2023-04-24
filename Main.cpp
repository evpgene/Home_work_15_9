#pragma once
#include <iostream>
#include "Chat.h"
#include "HashTable.h"

int main()
{
	char logn[LOGINLENGTH]{ 't', 'w', 'i' };
	char* pas = new char[4] {'b', 'l', 'b', 'l'};
	Chat chat;
	chat.reg(logn, pas, 4);

    char logn1[LOGINLENGTH]{ 't', 'w', 'i' };
    char* pas1 = new char[4] {'b', 'l', 'b', 'l'};

    if (chat.login(logn1, pas1, 4))
        std::cout << "Logged in" << std::endl;
    else
        std::cout << "Incorrect login or password" << std::endl;


    delete[] pas, pas1;
	return 0;
};