#ifndef __FUNC_H__
#define __FUNC_H__

#include <iostream>
#include <string>

using namespace std;

int findSpace(const string *Text);
int get_index(const char sym, const char *alphabet);

string table_encryption(const string *word, const string *keys, const char filler='x');
string table_decryption(const string *word, const string *keys);

string vig_encryption(const string *str, const string *key, const char *alphabet, int sz_alphbt);
string vig_decryption(const string *str, const string *key, const char *alphabet, int sz_alphbt);

string salat_encryption(const string *str, int key=0);
string salat_decryption(const string *str, int key=0);

inline namespace en {
    enum {sz_alphbt=26};
    inline const char *alphabet = "abcdefghijklmnopqrstuvwxyz";
};

#endif
