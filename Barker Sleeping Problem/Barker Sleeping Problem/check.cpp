
#include <iostream>
#include <string>
#include <thread>
#include <mutex>

using namespace std;

std::mutex mu;

void CallHome(string message)
{
    cout << "Thread " << this_thread::get_id() << " says " << message << endl;
}

int min()
{
    thread t1(CallHome, "Hello from Jupiter");
    thread t2(CallHome, "Hello from Pluto");
    thread t3(CallHome, "Hello from Moon");
    
    CallHome("Hello from Main/Earth");
    
    thread t4(CallHome, "Hello from Uranus");
    thread t5(CallHome, "Hello from Neptune");
    
    t1.join();
    t2.join();
    t3.join();
    t4.join();
    t5.join();
    
    return 0;
}
