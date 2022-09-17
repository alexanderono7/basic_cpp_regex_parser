#ifndef __REGEX_H__
#define __REGEX_H__

#include <string>
#include <vector>
class regexer{
    public:
    private:
};

class regex{
    public:
    private:
        std::string id;
        std::string expr;
        node start;
        node end;
};

class node{
    public:
    private:
        std::vector<node> exits;
};
#endif