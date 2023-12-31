/*************************************************/
/*   (C) 2023 Dyuthi Nair                        */
/*                                               */
/*                                               */
/*************************************************/
#include "Tokenizer.hpp"
#include <algorithm>

using namespace std;

Tokenizer::Tokenizer(string& line)
    : line(line)
{
    currentChar=this->line.begin();
    lastTokenEnd = this->line.begin();
}

bool Tokenizer::HasMore()
{
    return currentChar != line.end();
}

string Tokenizer::GetToken(vector<char> delimeters)
{
    if (!Tokenizer::HasMore())
        throw std::invalid_argument ("No more token");

    bool quoteIndex = false;
    for(; currentChar != line.end(); currentChar++)
    {
        if (*currentChar=='"')
            quoteIndex = !quoteIndex;
        if ((find(delimeters.begin(), delimeters.end(), *currentChar) != delimeters.end()) && !quoteIndex) {
            break;
        }
    }

    string token = std::string(lastTokenEnd, currentChar);
    if (currentChar != line.end())
        currentChar++;
    lastTokenEnd = currentChar;
    Trim(token);
    return token;
}

std::string Tokenizer::Trim(std::string& str)
{
    str.erase(remove(str.begin(), str.end(), '"'), str.end());

    str.erase(str.find_last_not_of(' ')+1);         //suffixing spaces
    str.erase(0, str.find_first_not_of(' '));       //prefixing spaces
    return str;
}