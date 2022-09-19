#include "regex.h"

/*
1. Determine the longest possible substring of s @ position p,
    that matches r.
2. Indicate if there is no match.
3. Does not return a substr - return to position p' 
    corresponding to the position after the lexeme 
    (b/w p and p').
*/
int match(regex r, std::string s, int p){
    return 0;
}


/*
1. call match(r,s,p) for each regex in L
2. for each regex in r, records the longest matching prefix obtained from the match() call 
3. Returns the token for which match(r,s,p) returns the longest amongst all the prefixes obtained in step 2, and advance the position
    to reflect that the input is consumed
4. If there is a tie, return the token listed first in the list.
*/
Token my_getToken(std::vector<Token> L, std::string s, int p){

}