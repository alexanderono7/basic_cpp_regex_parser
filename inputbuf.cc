/*
 * Copyright (C) Rida Bazzi, 2017
 *
 * Do not share this file with anyone
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
#include <istream>
#include <vector>
#include <string>
#include <cstdio>

#include "inputbuf.h"

using namespace std;

// Returns true if input buffer is empty
bool InputBuffer::EndOfInput()
{
    if (!input_buffer.empty())
        return false;
    else
        return cin.eof();
}

// Returns given char to the input buffer, and also return same char?
// Useful for peek function, I assume.
char InputBuffer::UngetChar(char c)
{
    if (c != EOF)
        input_buffer.push_back(c);;
    return c;
}

// Writes next char in input_buffer to given char address.
void InputBuffer::GetChar(char& c)
{
    if (!input_buffer.empty()) {
        c = input_buffer.back();
        input_buffer.pop_back();
    } else {
        cin.get(c);
    }
}

// Push given string back on to input buffer - also returns same string?
// Useful for peek function, I assume.
string InputBuffer::UngetString(string s)
{
    for (int i = 0; i < (int)s.size(); i++)
        input_buffer.push_back(s[s.size()-i-1]);
    return s;
}
