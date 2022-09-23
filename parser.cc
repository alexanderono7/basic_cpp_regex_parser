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
#include <map>
#include "parser.h"

using namespace std;

string int2str(int x){
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
    return "WHAT";
}

// triggers when there is a problem w/ token_section
void Parser::syntax_error()
{
    cout << "SNYTAX ERORR\n";
    exit(1);
}

// should trigger when INPUT_TEXT has an area which does not fit any given regex
void Parser::expr_error()
{
    cout << "EXPR ERROR (PLACEHOLDER)\n";
    exit(1);
}

void Parser::semantic_error()
{
    cout << "SEMANTIC ERROR (PLACEHOLDER)\n";
    exit(1);
}

void Parser::epsilon_error()
{
    cout << "EPSILON ERROR (PLACEHOLDER)\n";
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
    if(t.token_type == ID){
        id_obj new_id;
        new_id.name = t.lexeme;
        id_list.push_back(new_id);
        ids.push_back(t);   // probably unnecessary 
    }
    if(t.token_type == INPUT_TEXT){
        input_text = t.lexeme;
    }
    vect.push_back(t);
    return t;
}

void Parser::parse_input()
{
    parse_tokens_section();
    expect(INPUT_TEXT);
    expect(END_OF_FILE);
}

void Parser::parse_tokens_section()
{
    parse_token_list();
    expect(HASH);
}

void Parser::parse_token_list()
{
    parse_token();
    
    Token t = lexer.peek(1);
    // POSSIBLE PROBLEM HERE vvv
    if(t.token_type == HASH){
        return; //do not expect(HASH)
    }else if(t.token_type == COMMA){
        expect(COMMA);
        parse_token_list();
    }else{
        syntax_error();
    }
}

void Parser::parse_token()
{
    regex reg;

    // I believe this is where you would add ID and expr's to add dictionary/list.
    expect(ID);
    reg = parse_expr();
}

regex Parser::parse_expr()
{
    Token t = lexer.peek(1);
    regex new_reg;
    
    if(t.token_type == CHAR) {
        //create regex here?
        Token t;
        t = expect(CHAR);
        string a = t.lexeme;

        new_reg = regex(a);
        //regs.push_back(new_reg);
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
            newer = parse_expr();
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
            syntax_error();
        }
        return new_reg;
    }else if(t.token_type == UNDERSCORE){
        new_reg = regex("_"); // predicting a problem here.
        expect(UNDERSCORE);
        return new_reg;
    }else{
        syntax_error();
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
        vect.push_back(t);
        t.Print();         	// print token
        t = lexer.GetToken();	// and get another one
    }
        
    // note that you should use END_OF_FILE and not EOF
}

//void Parser::printAll(){ }

int main()
{
    // note: the parser class has a lexer object instantiated in it (see file
    // parser.h). You should not be declaring a separate lexer object. 
    // You can access the lexer object in the parser functions as shown in 
    // the example  method Parser::readAndPrintAllInput()
    // If you declare another lexer object, lexical analysis will 
    // not work correctly
    Parser parser;

    //parser.readAndPrintAllInput(); // This existed by default - I believe I'm supposed to remove it
	parser.parse_input();

    // REMOVE ALL BELOW LATER
    cout << "\nTokens:\n";
    for(Token i: parser.vect){
        i.Print(); // remove later...
    }
    cout << "\n\n";
    cout << "IDs:\n";
    for(Token i: parser.ids){
        i.Print(); // remove later...
    }
    cout << "\n\n";
    for(regex i: parser.regs){
        cout << i.start->first_label; // remove later...
    }
    cout << "\n\nmy id_list: \n";
    for(id_obj i: parser.id_list){
        cout << i.name; // remove later...
    }
    
    cout << "\n\n";
    cout << parser.input_text;
    cout << "\n";
}
