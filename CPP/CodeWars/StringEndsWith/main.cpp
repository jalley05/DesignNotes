/*
    Complete the solution so that it returns true if the first argument(string) passed in ends with the 2nd argument (also a string).

    Examples:

    solution('abc', 'bc') // returns true
    solution('abc', 'd') // returns false
 */

#include <iostream>
#include <vector>
#include <assert.h>

using namespace std;

bool solution(string const &str, string const &ending) {
    size_t index = str.find(ending);
    if(index != string::npos)
    {
        return (index == (str.size() - ending.size()));
    }
    return false;
}

int main() {

    assert(solution("abcde", "cde"));
    assert(!solution("abcde", "abc"));
    assert(!solution("abc", ""));

    cout << "Pass" << endl;

    return 0;
}
