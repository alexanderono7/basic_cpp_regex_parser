#ifndef __REGEX_H__
#define __REGEX_H__


#include <string>
#include <vector>
#include "lexer.h"


class node{
    public:
        node *first_neighbor;
        node *second_neighbor;
        std::string first_label;
        std::string second_label;
    private:
};

class regex{
    public:
        regex(std::string a);
        regex();
        void regor();
        void kleene();
        node *start;
        node *accept;
    private:
};


int match(regex r, std::string s, int p);
Token my_getToken(std::vector<Token> L, std::string s, int p);
regex regex_or(regex a, regex b);
regex regex_KLEENE(regex r);
#endif