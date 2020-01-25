/*
 The goal of this exercise is to convert a string to a new string where each character
 in the new string is "(" if that character appears only once in the original string,
 or ")" if that character appears more than once in the original string. 
 Ignore capitalization when determining if a character is a duplicate.

    Examples

    "din"      =>  "((("
    "recede"   =>  "()()()"
    "Success"  =>  ")())())"
    "(( @"     =>  "))((" 

 */
#include <string>
#include <iostream>
#include <map>
#include <assert.h>

using namespace std;

/*
 * Use a map to keep track of the character count
 */
string duplicate_encoder(const string& word)
{
    map<char, int> charCounts;
    for(const auto c : word)
    {
        charCounts[tolower(c)]++;
    }

    string outStr;
    for(const auto c : word)
    {
        outStr += charCounts[tolower(c)] == 1 ? "(" : ")";
    }

    return outStr;
}


int main()
{
    assert(")())())" == duplicate_encoder("Success"));

    return 0;
}


