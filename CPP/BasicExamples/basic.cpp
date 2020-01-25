#include "basic.h"
#include <iostream>

using namespace std;


int Basic::instanceCount = 0;
Basic::Basic(void)
{
    instanceCount++;
}

void Basic::function(void)
{
    cout << "Hello world" << endl;
    cout << "Instance " << instanceCount << endl;
}
