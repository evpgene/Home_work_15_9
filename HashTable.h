#pragma once
#pragma once

#include <string.h>

#define LOGINLENGTH 10  // �����c����� ����� �����

typedef char Login[LOGINLENGTH]; // ��� ��� ������

class HashTable { // ��� �������
public:

    HashTable();
    HashTable(const HashTable& other);

    HashTable& operator = (HashTable& other);

    ~HashTable();
    void add(Login login, int hash);

    void del(Login login);
    int find(Login login) const; // ���������� hash
    void resize();
    void clean();

private:

    enum enPairStatus {
        free,
        engaged,
        deleted
    };

    struct AuthData { // ���� ����-��������
        AuthData() :
            login(""),
            pass_sha1_hash(-1),
            status(enPairStatus::free)
        {}
        AuthData(Login login, int pass) :
            pass_sha1_hash(pass),
            status(enPairStatus::engaged) {
            memcpy(this->login, login, LOGINLENGTH);
        }
        AuthData& operator = (const AuthData& other) {
            pass_sha1_hash = other.pass_sha1_hash;
            memcpy(login, other.login, LOGINLENGTH);
            status = other.status;

            return *this;
        }

        bool operator == (const AuthData& other) {
            return  status == other.status &&
                (status != enPairStatus::engaged || (pass_sha1_hash == other.pass_sha1_hash && !strcmp(login, other.login)));
        }

        Login login;
        int pass_sha1_hash;
        enPairStatus status;
    };

    int hash_func(Login login, int offset) const;

    AuthData* data;
    int mem_size;
    int count;
};
