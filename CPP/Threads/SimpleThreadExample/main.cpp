// g++ -pthread -o app main.cpp

#include <thread>
#include <chrono>
#include <iostream>

using namespace std;

class ThreadClass {
public:
    ThreadClass() = default;
    ~ThreadClass() { m_thread->join(); }

    void Create(void);

private:
    void Process(void);

    thread* m_thread;
};

void ThreadClass::Create() {
    if(!m_thread)
    {
        unsigned num_cpus = thread::hardware_concurrency();
        m_thread = new thread(&ThreadClass::Process, this);

        cpu_set_t cpuset;
        CPU_ZERO(&cpuset);
        CPU_SET(0, &cpuset);

        int rc = pthread_setaffinity_np(m_thread->native_handle(), sizeof(cpu_set_t), &cpuset);

        if(rc != 0)
            cout << "Error calling pthread_setaffinity_np: " << rc << "\n";
    }
}

void ThreadClass::Process() {
    while(1)
    {
        printf("Running thread process...\n");
        this_thread::sleep_for(chrono::milliseconds(1000));
    }
}

int main()
{

    ThreadClass tc = ThreadClass();
    tc.Create();

    while(1)
    {
        printf("Main thread running...\n");
        this_thread::sleep_for(chrono::milliseconds(2500));
    }

    return 0;
}
