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
    if(ending.size() == 0) {
        return true;
    }

    // Find the index of the ending and if it is exactlt the last
    // characters in the str
    size_t index = str.find(ending);
    if(index != string::npos) {
        return (index == (str.size() - ending.size()));
    }
    return false;
}

int main() {
    // Test cases
    assert(solution("abcde", "cde"));
    assert(!solution("abcde", "abc"));
    assert(!solution("abc", "e"));
    assert(solution("alsdkfj", ""));

    cout << "Pass" << endl;

    return 0;
}
