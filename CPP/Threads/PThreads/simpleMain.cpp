#include <stdio.h>
#include <stdlib.h>

void* Process(void* arg)
{

}


int main(int argc, char** argv)
{
    // Cores :

    // Thread ID
    pthread_t threadId;

    pthread_attr_t attr;
    pthread_attr_init(&attr);

    pthread_create(&threadId, &attr, Process, void);


}
