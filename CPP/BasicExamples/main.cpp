#include "basic.h"
#include <memory>

using namespace std;

int main()
{
    // Unique shared pointer will take care of deallocation
    unique_ptr<Basic> objectA(new Basic());

    objectA->function();

    unique_ptr<Basic> objectB(new Basic());

    objectB->function();
}
