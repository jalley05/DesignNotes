/*
You live in the city of Cartesia where all roads are laid out in a perfect grid.
You arrived ten minutes too early to an appointment, so you decided to take the
opportunity to go for a short walk. The city provides its citizens with a Walk 
Generating App on their phones -- everytime you press the button it sends you an
array of one-letter strings representing directions to walk (eg. ['n', 's', 'w', 'e']).
You always walk only a single block in a direction and you know it take
s you one minute to traverse one city block, so create a function that will return
true if the walk the app gives you will take you exactly ten minutes (you don't want
to be early or late!) and will, of course, return you to your starting point.
Return false otherwise.

Note: you will always receive a valid array containing a random assortment of direction
letters ('n', 's', 'e', or 'w' only). It will never give you an empty array
(that's not a walk, that's standing still!).
 */

#include <iostream>
#include <vector>
#include <assert.h>

using namespace std;

bool isValidWalk(vector<char> walk)
{
    if (walk.size() != 10)
    {
        // Walk exceeds 10 minute limit
        return false;
    }

    int vertCount = 0;
    int horzCount = 0;

    for(const auto& dir : walk)
    {
        switch(dir) {
            default:
            case 'n': vertCount++; break;
            case 's': vertCount--; break;
            case 'e': horzCount++; break;
            case 'w': horzCount--; break;
        }
    }

    if((vertCount == 0) && (horzCount == 0))
    {
        return true;
    }

    return false;
}

int main() {
    vector<char> badWalk({'n','s','e','w','n','s','e','w','s','s'}); 
    cout << isValidWalk(badWalk) << endl;
    vector<char> goodWalk({'n','s','e','w','n','s','e','w','s','n'}); 
    cout << isValidWalk(goodWalk) << endl;

    return 0;
}
