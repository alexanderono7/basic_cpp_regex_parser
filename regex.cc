/*
Alexander Ono
amono1@asu.edu
SID: 1214959876
CSE340 - Dr. Bazzi
Project #1 - Regex Parser
9/24/2022
*/
#include "regex.h"
#include <iostream>
#include <unordered_set>
using namespace std;
/*
1. Determine the longest possible substring of s @ position p,
    that matches r.
2. Indicate if there is no match.
3. Does not return a substr - return to position p' 
    corresponding to the position after the lexeme 
    (b/w p and p').
*/
int match(node *r, string s, int p, int orig){
    int a = orig;
    int b = orig;

    string c;
    int len = s.length()-1;
    if(p > len){
        c = "xx";
    }else{
        c = s.substr(p,1);
    }
    
    //if(r == nullptr) return orig;
    if(r->first_neighbor == NULL and r->second_neighbor == NULL){
        return p;
    }

    if(r->first_label == c){
        a = match(r->first_neighbor, s, p+1, orig); 
    }else if(r->first_label == "_"){
        a = match(r->first_neighbor, s, p, orig); 
    }

    if(r->second_label == c){
        b = match(r->second_neighbor, s, p+1, orig); 
    }else if(r->second_label == "_"){
        b = match(r->second_neighbor, s, p, orig); 
    }
    int result;
    if(a > b){ result = a; }else{ result = b; }
    return result;
}

bool epsilonWalk(node *r, unordered_set <node*> nodeset){
    bool a = false;
    bool b = false;
    if(r == nullptr or nodeset.find(r) != nodeset.end()){ 
        return false; 
    }
    nodeset.insert(r);
    if(r->first_neighbor == nullptr and r->second_neighbor == nullptr){ return true; }
    if(r->first_label == "_"){ a = epsilonWalk(r->first_neighbor, nodeset); }
    if(r->second_label == "_"){ b = epsilonWalk(r->second_neighbor, nodeset); }
    return(a or b);
}

void destroyTraversal(node *r, unordered_set <node*> nodeset){
    if(r == NULL or r->marked){ 
        return; 
    }
    r->marked = true;
    destroyTraversal(r->first_neighbor, nodeset);
    destroyTraversal(r->second_neighbor, nodeset);
    delete r;
    return;
}

node::node(){
    std::string fl;
    std::string sl;
    this->first_label = fl;
    this->second_label = sl;
    this->first_neighbor = nullptr;
    this->second_neighbor = nullptr;
    this->marked = false;
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
    newstart->second_neighbor = newaccept;
    newstart->first_label = "_";
    newstart->second_label = "_";
    
    this->accept->first_neighbor = newaccept;
    this->accept->second_neighbor = this->start;
    this->accept->first_label = "_";
    this->accept->second_label = "_";

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