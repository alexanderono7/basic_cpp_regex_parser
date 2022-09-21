#include "regex.h"
using namespace std;
/*
1. Determine the longest possible substring of s @ position p,
    that matches r.
2. Indicate if there is no match.
3. Does not return a substr - return to position p' 
    corresponding to the position after the lexeme 
    (b/w p and p').
*/
int match(regex r, string s, int p){
    return 0;
}


/*
1. call match(r,s,p) for each regex in L
2. for each regex in r, records the longest matching prefix obtained from the match() call 
3. Returns the token for which match(r,s,p) returns the longest amongst all the prefixes obtained in step 2, and advance the position
    to reflect that the input is consumed
4. If there is a tie, return the token listed first in the list.
*/
Token my_getToken(vector<Token> L, string s, int p){
    Token t;  return t; // remove later (placeholder to stop warnings)
}

regex::regex(){
    this->start = NULL;
    this->accept = NULL;
}

regex::regex(std::string a){
    node one;
    node two;
    one.first_label = a;
    one.first_neighbor = &two;
    one.second_neighbor = NULL;

    two.first_label = '_';
    two.first_neighbor = NULL;
    two.second_neighbor = NULL;
    start = &one;
    accept = &two;
}

// Given a regex x, return x*
void regex::kleene(){
    node newstart;
    node newaccept;
    
    newstart.first_neighbor = start;
    newaccept.second_neighbor = start;
    
    newstart.first_label = '_';
    newstart.second_label = '_';
    newaccept.first_neighbor = NULL;
    newaccept.second_neighbor = NULL;
    
    start = &newstart;
    accept = &newaccept;
}

// Given regex a and regex b, return a regex which is [a | b] (which is: a or b).
regex regex_or(regex a, regex b){
    regex result;
    node newstart;
    node newaccept;

    newstart.first_label = '_';
    newstart.second_label = '_';
    newstart.first_neighbor = a.start;
    newstart.second_neighbor = b.start;
    
    a.accept->first_neighbor = &newaccept;
    a.accept->first_label = '_';
    b.accept->first_neighbor = &newaccept;
    b.accept->first_label = '_';

    return result;
}

// Given regex a and regex b, return a regex concatenation of a and b.
regex regex_dot(regex a, regex b){
    
}