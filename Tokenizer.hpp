/*************************************************/
/*   (C) 2023 Dyuthi Nair                        */
/*                                               */
/*                                               */
/*************************************************/
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

#pragma once

class Tokenizer
{
    string& line;
    std::string::iterator currentChar;
    std::string::iterator lastTokenEnd;
    string Trim(std::string& str);

    public:
        Tokenizer(string& line);
        bool HasMore();
        string GetToken(vector<char> delimeters);
};