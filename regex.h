#ifndef __REGEX_H__
#define __REGEX_H__


#include <string>
#include <vector>
#include "lexer.h"
#include "parser.h"

int match(regex r, std::string s, int p);
Token my_getToken(std::vector<Token> L, std::string s, int p);

class regex{
    public:
        regex();
    private:
        node start;
        node end;
};

class node{
    public:
        node *first_neighbor;
        node *second_neighbor;
        std::string first_label;
        std::string second_label;
    private:
};
#endif