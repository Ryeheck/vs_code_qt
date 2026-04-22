#include "func.hpp"

#include <iostream>
#include <cstring>
#include <string>

#define MAX_KEYS    10
#define MAX_WORD    50

using namespace std;

int get_index(const char sym, const char *alphabet) 
{
    for(int i = 0; alphabet[i] != '\0'; ++i)
        if(alphabet[i] == sym)
            return i;
    
    return -1;
}

int findSpace(const string *Text)
{
    int count {};
    for(int i = Text->length(); i > 0; --i)
        if((*Text)[i] == ' ')
            count++;
            
    return count;
}

/*                                                        Salat                                                                                     */

string salat_encryption(const string *str, int key)
{
    string res;

    for(char sym : *str) {
        int indx_alphbt = get_index(sym, en::alphabet);
        
        if(indx_alphbt != -1) {
            int indx_sym = (indx_alphbt + key) % sz_alphbt;

            res += en::alphabet[indx_sym];
        }
        else
            res += sym;
    }
    return res;
}

string salat_decryption(const string *str, int key)
{
    string res;
    
    for(char sym : *str) {
        int indx_alphbt = get_index(sym, en::alphabet);

        if(indx_alphbt != -1) {
            int indx_sym = (indx_alphbt - key + sz_alphbt) % sz_alphbt;

            res += alphabet[indx_sym];
        }
        else
            res += sym;
    }
    return res;
}

/*                                                        TABLE                                                                                     */

string table_encryption(const string *word, const string *keys, const char filler)
{
    string res;

    int cols = 0;
    for(char sym : *keys)  if(isdigit(sym))  cols++;

    if(cols == 0)   return res;
    
    int word_len = word->length();
    int rows = (word_len + cols - 1) / cols;

    char matrix[cols][rows];

    int count {};
    for(int i = 0; i < rows; ++i) 
        for(int j = 0; j < cols; ++j) {
            if(count < word_len)
                matrix[j][i] = (*word)[count++];
            else
                matrix[j][i] = filler;
        }
    
    int space = findSpace(keys);

    char cur_col = '1';
    for(int i = 1; i <= cols; ++i) {
        count = 0;

        for(int num_key = 0; num_key < cols + space; ++num_key)  
        {
            if((*keys)[num_key] == ' ')  count++;
            else if((*keys)[num_key] == cur_col) 
            {
                for(int j = 0; j < rows; ++j)
                    res += matrix[num_key - count][j];
                cur_col++;

                break;
            }
        }
    }
    return res;
}

string table_decryption(const string *word, const string *keys)
{
    string res;

    int cols = 0;
    for(char sym : *keys)  if(isdigit(sym))  cols++;

    if(cols == 0)   return res;
    if(cols > 0 && word->length() % cols != 0)  return res;

    int word_len = word->length();
    int rows = (word_len + cols - 1) / cols;

    int count = 0;
    for(int i = 0; i < rows; ++i) {
        for(char j : *keys) 
            if(j != ' ') {
                int key = ((j - '0') - 1) * rows;

                res += (*word)[key + i];
            }
    }
    return res;
}


/*                                                        VIG                                                                                       */

string vig_encryption(const string *str, const string *key,
                    const char *alphabet, int sz_alphbt)
{
    string res;

    int count {};
    int len_key = key->length();

    for(char sym : *str) {
        int indx_str = get_index(sym, alphabet);
        int indx_key = get_index((*key)[count % len_key], alphabet);

        if(indx_str != -1 && indx_key != -1) {
            int sym = (indx_key + indx_str) % sz_alphbt;

            res += alphabet[sym];
        }
        else
            res += sym;
            
        count++;
    }
    return res;
}

string vig_decryption(const string *str, const string *key,
                    const char *alphabet, int sz_alphbt)
{
    string res;

    int count{};
    int len_key = key->length();
    
    for(char sym : *str) {
        int indx_str = get_index(sym, alphabet);
        int indx_key = get_index((*key)[count % len_key], alphabet);

        if(indx_str != -1 && indx_key != -1) {
            int sym = (indx_str - indx_key + sz_alphbt) % sz_alphbt;

            res += alphabet[sym];
            count++;
        }
        else {
            res += sym;
            count++;
        }
    }
    return res;     
}
