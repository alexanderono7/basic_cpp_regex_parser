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
#ifndef __INPUT_BUFFER__H__
#define __INPUT_BUFFER__H__

#include <string>
#include <vector>

class InputBuffer {
  public:
    void GetChar(char&);
    char UngetChar(char);
    std::string UngetString(std::string);
    bool EndOfInput();

  private:
    std::vector<char> input_buffer;
};

#endif  //__INPUT_BUFFER__H__
