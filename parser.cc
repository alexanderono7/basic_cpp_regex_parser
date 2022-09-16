/*
 * Copyright (C) Rida Bazzi, 2020
 *
 * Do not share this file with anyone
 *
 * Do not post this file or derivatives of
 * of this file online
 *
 */
#include <iostream>
#include <cstdlib>
#include <vector>
#include "parser.h"

using namespace std;

string translate(int x){
    switch(x){
        case 0: return "END_OF_FILE";
        case 1: return "LPAREN";
        case 2: return "RPAREN";
        case 3: return "HASH";
        case 4: return "ID";
        case 5: return "COMMA";
        case 6: return "DOT";
        case 7: return "STAR";
        case 8: return "OR";
        case 9: return "UNDERSCORE";
        case 10: return "SYMBOL";
        case 11: return "CHAR";
        case 12: return "INPUT_TXT";
        case 13: return "ERROR";
    }
}

void Parser::syntax_error()
{
    cout << "SYNTAX ERROR\n";
    exit(1);
}

// this function gets a token and checks if it is
// of the expected type. If it is, the token is
// returned, otherwise, synatx_error() is generated
// this function is particularly useful to match
// terminals in a right hand side of a rule.
// Written by Mohsen Zohrevandi
Token Parser::expect(TokenType expected_type)
{
    Token t = lexer.GetToken();
    if (t.token_type != expected_type)
        syntax_error();
    return t;
}

void Parser::parse_input()
{
    for(Token i: vect)
        cout << translate(i.token_type) << ' ';
    //parse tokens_section
    //expect(INPUT_TEXT)
}

void Parser::parse_tokens_section()
{
    /*
    parse token_list
    expect(HASH)    
    */
}

void Parser::parse_token_list()
{
    /*
    
    */

}

void Parser::parse_token()
{
   
}

void Parser::parse_expr()
{
    //expect
}


// This function simply reads and prints all tokens
// I included it as an example. You should compile the provided code
// as it is and then run ./a.out < tests/test0.txt to see what this function does

void Parser::readAndPrintAllInput()
{
    Token t;

    // get a token
    t = lexer.GetToken();

    // while end of input is not reached
    // Print the contents of input token list
    while (t.token_type != END_OF_FILE) 
    {
        vect.push_back(t);
        t.Print();         	// print token
        t = lexer.GetToken();	// and get another one
    }
        
    // note that you should use END_OF_FILE and not EOF
}

int main()
{
    // note: the parser class has a lexer object instantiated in it (see file
    // parser.h). You should not be declaring a separate lexer object. 
    // You can access the lexer object in the parser functions as shown in 
    // the example  method Parser::readAndPrintAllInput()
    // If you declare another lexer object, lexical analysis will 
    // not work correctly
    Parser parser;

    parser.readAndPrintAllInput(); // This existed by default - I believe I'm supposed to remove it
	parser.parse_input();
}
