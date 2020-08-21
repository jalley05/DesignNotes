// g++ -pthread -o app main.cpp

#include <thread>
#include <chrono>

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
        m_thread = new thread(&ThreadClass::Process, this);
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
