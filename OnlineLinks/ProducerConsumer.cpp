#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm> // For sort
#include <thread>
#include <mutex>
#include <condition_variable>
using namespace std;

static const int MAX_BUFFER_SIZE = 5;
static uint32_t BUFFER[MAX_BUFFER_SIZE];
static vector<uint32_t> VEC_BUFFER;

mutex mtx;
condition_variable cv;

void producer()
{
    for (uint32_t i = 0; i < MAX_BUFFER_SIZE; i++)
    {
        // Take a lock on the mutex before working on the buffer
        unique_lock<std::mutex> prodLock(mtx);
        if (VEC_BUFFER.size() > MAX_BUFFER_SIZE)
        {
            // Wait if Producer does not have space to put into the buffer
            cv.wait(prodLock);
        }
        else
        {
            cout << "Produced: " << i << endl;
            VEC_BUFFER.push_back(i);
        }

        if (VEC_BUFFER.size() == 1)
        {
            // Notify the client if Producer has produced the first element and put it into
            // the buffer
            cv.notify_one();
        }
    }
}

void consumer()
{
    for (uint32_t i = 0; i < MAX_BUFFER_SIZE; i++)
    {
        // Take a lock on the mutext before working on the BUFFER
        unique_lock<std::mutex> consLock(mtx);
        if (VEC_BUFFER.size() < 1)
        {
            cv.wait(consLock);
        }
        else
        {
            cout << "Consumed: " << VEC_BUFFER.back() << endl;
            VEC_BUFFER.pop_back();
        }

        if (VEC_BUFFER.size() == MAX_BUFFER_SIZE - 1)
        {
            // Notify the Producer once the last element is consumed and there is space for
            // adding elements
            cv.notify_one();
        }
    }
}

int main()
{
    cout << "Producer Consumer Problem" << endl;
    thread prod (producer);
    thread cons (consumer);

    prod.join();
    cons.join();

    cout << endl;
    return 0;
}
