/*
 * Copyright (C) Rida Bazzi, 2019
 *
 * Do not share this file with anyone
 */
#ifndef __PARSER_H__
#define __PARSER_H__

#include <string>
#include <vector>
#include "lexer.h"
#include "regex.h"

class id_obj {
  public:
    std::string name;
    regex *reg;
  private:
};

class Parser {
  public:
    void parse_input();
    void readAndPrintAllInput();
    std::vector<Token> vect;      //contains ALL tokens of the input
    std::vector<Token> ids;       //possibly temp - contains list of IDs (token names)
    std::vector<Token> patterns;  //possibly temp - contains list of expressions (regexes)?
    std::vector<regex> regs;      //possibly temp - contains list of regex objects
    std::vector<id_obj> id_list;
    std::string input_text;       //possibly temp - contains input text to be matched on
  private:
    LexicalAnalyzer lexer;
    void syntax_error();
    void expr_error();
    void semantic_error();
    void epsilon_error();
    Token expect(TokenType expected_type);
    Token expect_input_text();
    void parse_tokens_section();
    void parse_token_list();
    void parse_token();
    regex parse_expr();
};

#endif

