/*
 * Copyright (C) Rida Bazzi, 2020
 *
 * Do not share this file with anyone
 *
 * Do not post this file or derivatives of
 * of this file online
 *
 */

/*
Alexander Ono
amono1@asu.edu
SID: 1214959876
CSE340 - Dr. Bazzi
Project #1 - Regex Parser
9/24/2022
*/
#include <iostream>
#include <cstdlib>
#include <vector>
#include <map>
#include "parser.h"
#include <unordered_map>

using namespace std;

// Non-EXPR syntax error: triggers when there is a problem w/ token_section syntax (except in expressions).
void Parser::syntax_error()
{
    cout << "SNYTAX ERORR\n";
    exit(1);
}

// EXPR syntax error: should trigger when an EXPRESSION specifically has invalid grammar.
void Parser::expr_error()
{
    cout << "SYNTAX ERROR IN EXPRESSION OF " << id_list.back().name;
    exit(1);
}

// Semantic error: triggers if 2 or more tokens have the same name (ID).
void Parser::semantic_error()
{
    unordered_map <string, int> umap;
    //vector<int> duplicates;   // do I need this?
    bool sem_err = false;
    for(id_obj i : id_list){
        if(umap.find(i.name) == umap.end()){
            umap[i.name] = i.lineno;
        }else{
            cout << "Line " << i.lineno << ": " << i.name << " already declared on line " << umap[i.name];
            cout << "\n";
            sem_err = true;
        }
    }
    if(sem_err){
        exit(1);
    }
}

// Epsilon error: triggers when an expression of a token is able to produce the empty string (epsilon/'_').
void Parser::epsilon_error()
{
    unordered_set <node*> nodeset;
    vector <string> eps_violators;
    for(id_obj i : id_list){
        nodeset.clear();
        if(epsilonWalk(i.reg.start,nodeset)){
            eps_violators.push_back(i.name);
        }

    }
    if(eps_violators.size() > 0){
        cout << "EPSILON IS NOOOOOOOT A TOKEN !!!";
        for(string x : eps_violators){
            cout << " " << x;
        }
        exit(1);
    }
}

// Overloaded partial function version of Parser::expect - used for convenience as expected_type is set to false by default.
Token Parser::expect(TokenType expected_type){
    return expect(expected_type, false);
}

// this function gets a token and checks if it is
// of the expected type. If it is, the token is
// returned, otherwise, synatx_error() is generated
// this function is particularly useful to match
// terminals in a right hand side of a rule.
// Written by Mohsen Zohrevandi
Token Parser::expect(TokenType expected_type, bool isExpr)
{
    Token t = lexer.GetToken();
    if(t.token_type != expected_type and isExpr)
        expr_error();
    if (t.token_type != expected_type)
        syntax_error();
    if(t.token_type == ID){
        // creation of id object
        id_obj new_id;
        new_id.name = t.lexeme;
        new_id.lineno = t.line_no;
        id_list.push_back(new_id);
    }
    if(t.token_type == INPUT_TEXT){
        input_text = t.lexeme;
    }
    return t;
}

// Parses the input section (the start variable of the grammar, essentially).
void Parser::parse_input()
{
    parse_tokens_section();
    expect(INPUT_TEXT);
    expect(END_OF_FILE);
    
    // more error checking 
    semantic_error();
    epsilon_error();
}

// Parses: tokens_section -> token_list HASH
void Parser::parse_tokens_section()
{
    parse_token_list();
    expect(HASH);
}

// Parses: token_list -> token | token COMMA token_list
void Parser::parse_token_list()
{
    parse_token();
    
    Token t = lexer.peek(1);
    if(t.token_type == HASH){
        return; //do not expect(HASH)
    }else if(t.token_type == COMMA){
        expect(COMMA);
        parse_token_list();
    }else{
        syntax_error();
    }
}

// Parses: token -> ID expr
void Parser::parse_token()
{
    regex new_reg;

    // add ID and regex (expr) to id_list
    expect(ID);
    id_list.back().reg = parse_expr(); // add new regular expression to most recent ID in the id list
}

/*
Parses an EXPR (a regular expression):
expr -> CHAR
expr -> LPAREN expr RPAREN DOT LPAREN expr RPAREN
expr -> LPAREN expr RPAREN OR LPAREN expr RPAREN
expr -> LPAREN expr RPAREN STAR
expr -> UNDERSCORE
*/
regex Parser::parse_expr()
{
    Token t = lexer.peek(1);
    regex new_reg;  // why is this able to be modified in descending recursive calls?
    
    if(t.token_type == CHAR) {
        //create regex here
        string a;
        t = expect(CHAR);
        a = t.lexeme;

        new_reg.setchr(a);
        return new_reg;

    }else if(t.token_type == LPAREN) {
        regex newer;

        expect(LPAREN);
        new_reg = parse_expr();
        expect(RPAREN);
        
        t = lexer.peek(1);
        if(t.token_type == DOT){
            expect(DOT);
            expect(LPAREN);
            newer = parse_expr();   // bug - this line overwrites new_reg?
            expect(RPAREN);

            new_reg.concat(newer);
        }else if(t.token_type == OR){
            expect(OR);
            expect(LPAREN);
            newer = parse_expr();
            expect(RPAREN);
            
            new_reg.OR(newer);
        }else if(t.token_type == STAR){
            expect(STAR);
            new_reg.kleene();
        }else{
            expr_error();
        }
        return new_reg;

    }else if(t.token_type == UNDERSCORE){
        expect(UNDERSCORE);
        new_reg.setchr("_");
        return new_reg;
    }else{
        expr_error();
    }
    return new_reg;
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
        t.Print();         	// print token
        t = lexer.GetToken();	// and get another one
    }
        
    // note that you should use END_OF_FILE and not EOF
}

// Main method of the program, start of program execution.
int main()
{
    // note: the parser class has a lexer object instantiated in it (see file
    // parser.h). You should not be declaring a separate lexer object. 
    // You can access the lexer object in the parser functions as shown in 
    // the example  method Parser::readAndPrintAllInput()
    // If you declare another lexer object, lexical analysis will 
    // not work correctly
    Parser parser;
	parser.parse_input();
    parser.analyze(parser.id_list, parser.input_text);
    //parser.destroy_all_memory();
}

// Perform the actual lexical analysis on the input text.
void Parser::analyze(vector<id_obj> id_list, string str){
    string s;
    s = str.substr(1,str.length()-2); // removing the quotation marks from str!!!
    int p = 0;
    int len = s.length()-1;
    while(p < len){
        if(s[p] == ' '){
            p++;
            continue;
        }
        int original = p; // marks original position of p
        id_obj longest;
        int max = -1;
        int result = -1;
        for(id_obj i: id_list){
            result = match(i.reg.start, s, p, p);
            if(result > max){
                max = result;  // this should get the largest pattern match and take care of ties
                longest = i;
            } 
        }
        if(original == max or max == -1) {
            cout << "\nERROR";
            exit(1);
            //break;
        }else{
            p = max;
            cout << "\n" << longest.name << " , ";
            cout << "\"" << s.substr(original,p-original+0) << "\"";
        }
    }
}

// id object constructor
id_obj::id_obj(){
    this->name = "???";
    this->lineno = -1;
}

// Destroy the dynamically-allocated memory of all node pointers in each regular expression.
void Parser::destroy_all_memory(){
    unordered_set <node*> nodeset;
    for(id_obj i : id_list){
        nodeset.clear();
        destroyTraversal(i.reg.start, nodeset);
    }
    return;
}