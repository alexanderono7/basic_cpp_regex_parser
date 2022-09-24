/*
Alexander Ono
CSE340 - Dr. Bazzi
Project #1 - Regex Parser
9/24/2022
*/
#ifndef __REGEX_H__
#define __REGEX_H__


#include <string>
#include <vector>
#include "lexer.h"
#include <unordered_set>

class node{
    public:
        node();
        node *first_neighbor;
        node *second_neighbor;
        std::string first_label;
        std::string second_label;
};

class regex{
    public:
        node *start;
        node *accept;

        regex();
        regex(std::string a);
        void setchr(std::string a);
        void OR(regex b);
        void kleene();
        void concat(regex b);
};

int match(node *r, std::string s, int p, int orig);
bool epsilonWalk(node *r, std::unordered_set<node*> nodeset);
void destroyTraversal(node *r, std::unordered_set<node*> nodeset);
regex regex_or(regex a, regex b);
regex regex_KLEENE(regex r);
#endif