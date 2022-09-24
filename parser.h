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
    id_obj();
    std::string name;
    regex reg;
    int lineno;
  private:
};

class Parser {
  public:
    void parse_input();
    void readAndPrintAllInput();
    std::vector<id_obj> id_list;
    std::string input_text;       //possibly temp - contains input text to be matched on
    void analyze(std::vector<id_obj> id_list, std::string str);
    void destroy_all_memory();
  private:
    LexicalAnalyzer lexer;
    void syntax_error();
    void expr_error();
    void semantic_error();
    void epsilon_error();
    Token expect(TokenType expected_type);
    Token expect(TokenType expected_type, bool isExpr);
    Token expect_input_text();
    void parse_tokens_section();
    void parse_token_list();
    void parse_token();
    regex parse_expr();
};

#endif

