/*
Alexander Ono
amono1@asu.edu
SID: 1214959876
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
        bool marked;
};

class regex{
    public:
        node *start;
        node *accept;

        regex();
        void setchr(std::string a);
        void OR(regex b);
        void kleene();
        void concat(regex b);
};

int match(node *r, std::string s, int p, int orig);
bool epsilonWalk(node *r, std::unordered_set<node*> nodeset);
void destroyTraversal(node *r, std::unordered_set<node*> nodeset);
#endif