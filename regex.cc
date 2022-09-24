#include "regex.h"
#include <iostream>
using namespace std;
/*
1. Determine the longest possible substring of s @ position p,
    that matches r.
2. Indicate if there is no match.
3. Does not return a substr - return to position p' 
    corresponding to the position after the lexeme 
    (b/w p and p').
*/
int match(node *r, string s, int p){
    int a = p;
    int b = p;
    string c = s.substr(p,1);
    
    //check if r is an accepting node (has no neighbors)
    if(r->first_neighbor == NULL and r->second_neighbor == NULL)
        return p;

    //check for label transitions matching s[p] - take one if it matches
    //check for possible epsilon transitions - take them if they exist
    //if there no possible paths to take, then set var as -1
    //note: If you have time compress these two ifs down into one function vvv
    if(r->first_neighbor != NULL){
        if(r->first_label == c){
            a = match(r->first_neighbor, s, p+1); 
        }else if(r->first_label == "_"){
            a = match(r->first_neighbor, s, p); 
        }else{
            a = -1;
        }
    }
    if(r->second_neighbor != NULL){
        if(r->second_label == c){
            b = match(r->second_neighbor, s, p+1); 
        }else if(r->second_label == "_"){
            b = match(r->second_neighbor, s, p); 
        }else{
            b = -1;
        }
    }else{
        b = -1;
    }
    
    if(a > b){
        return a;
    }else{
        return b;
    }
}


/*
1. call match(r,s,p) for each regex in L
2. for each regex in r, records the longest matching prefix obtained from the match() call 
3. Returns the token for which match(r,s,p) returns the longest amongst all the prefixes obtained in step 2, and advance the position
    to reflect that the input is consumed
4. If there is a tie, return the token listed first in the list.
*/
//id_obj my_getToken(vector<id_obj> L, string s, int p){ }

node::node(){
    std::string fl;
    std::string sl;
    this->first_label = fl;
    this->second_label = sl;
    this->first_neighbor = nullptr;
    this->second_neighbor = nullptr;
}

regex::regex(){
    this->start = new node;
    this->accept = new node;
}

// given an empty regex object, set it equivalent to expr of 'a'
void regex::setchr(std::string a){
    this->start->first_label = a;
    this->start->first_neighbor = this->accept;
    this->start->second_neighbor = nullptr;

    this->accept->first_label = "_";
    this->accept->first_neighbor = nullptr;
    this->accept->second_neighbor = nullptr;
}


// Given regex a and regex b, return a regex concatenation of a and b.
void regex::concat(regex b){
    this->accept->first_label = "_";
    this->accept->first_neighbor = b.start;
    this->accept = b.accept;
}

// Given a regex x, return x*
void regex::kleene(){
    node *newstart = new node;
    node *newaccept = new node;
    
    newstart->first_neighbor = this->start;
    newstart->first_label = "_";
    newstart->second_neighbor = newaccept;
    newstart->second_label = "_";
    
    this->accept->second_neighbor = this->start;
    this->accept->second_label = "_";

    newaccept->first_neighbor = nullptr;    // does newaccept need eps transitions??
    newaccept->second_neighbor = nullptr;
    
    this->start = newstart;
    this->accept = newaccept;
}

// Given regex a and regex b, return a regex which is [a | b] (which is: a or b).
void regex::OR(regex b){
    node *newstart = new node;
    node *newaccept = new node;

    newstart->first_label = "_";
    newstart->second_label = "_";
    newstart->first_neighbor = this->start;
    newstart->second_neighbor = b.start;
    this->start = newstart;
    
    this->accept->first_neighbor = newaccept;
    b.accept->first_neighbor = newaccept;
    this->accept->first_label = "_";
    b.accept->first_label = "_";
    this->accept = newaccept;
}





// depreciated
regex::regex(std::string a){
    node one;
    node two;
    one.first_label = a;
    one.first_neighbor = &two;
    one.second_neighbor = NULL;

    two.first_label = '_';    // should this be null?
    two.first_neighbor = NULL;
    two.second_neighbor = NULL;
    this->start = &one;
    this->accept = &two;
}