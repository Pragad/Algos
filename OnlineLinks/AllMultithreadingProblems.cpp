#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm> // For sort
#include <thread>
#include <mutex>
#include <condition_variable>
using namespace std;

/*
 * PROBLEM 1. Producer Consumer Problem
 * void producer()
 * void consumer()
 *
 * PROBLEM 2: Simple Multi threading synchronization problem
 * 
 */
 
// -----------------------------------------------------------------------------------------
// PROBLEM 1. Producer Consumer Problem
// -----------------------------------------------------------------------------------------
static const int MAX_BUFFER_SIZE = 5;
static const uint32_t NUM_THREADS = 5;
static uint32_t BUFFER[MAX_BUFFER_SIZE];
static vector<uint32_t> VEC_BUFFER;

std::mutex mtx;
std::condition_variable cv;

void producer()
{
    for (uint32_t i = 0; i < MAX_BUFFER_SIZE; i++)
    {
        // Take a lock on the mutex
        unique_lock<std::mutex> prodLock(mtx);
        if (VEC_BUFFER.size() > MAX_BUFFER_SIZE)
        {
            // Wait if Producer does not have space to put into the buffer
            // The execution of the current thread is blocked until notified.
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
        // Take a lock on the mutex
        // When a  second consumer comes, it has to wait
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

// -----------------------------------------------------------------------------------------
// PROBLEM 2. Simple Multi threading synchronization problem
// -----------------------------------------------------------------------------------------
static const vector<string> stockSticker = {"NTAP", "FB", "GOOG", "TSLA", "LUV", "M"};
static const vector<uint32_t> stockPrices = {35, 105, 780, 250, 42, 38};

std::condition_variable condVar;
std::mutex mtx2;

void printStockSticker(uint32_t index)
{
    // Take a mutex lock
    unique_lock<std::mutex> stickerLock(mtx2);

    if (index < stockSticker.size())
    {
        cout << stockSticker[index] << " - ";
        index++;
        condVar.notify_one();
    }
    else
    {
        condVar.wait(stickerLock);
    }
}

void printStockPrices(uint32_t index)
{
    unique_lock<std::mutex> stockLock(mtx2);

    if (index < stockSticker.size())
    {
        cout << stockPrices[index] << endl;
        index++;
        condVar.notify_one();
    }
    else
    {
        condVar.wait(stockLock);
    }
}

// -----------------------------------------------------------------------------------------
// Main Function
// -----------------------------------------------------------------------------------------
int main()
{
    // PROBLEM 1. Single Threaded Producer Consumer Problem
    {
        cout << endl << "Single Threaded Producer Consumer Problem" << endl;
        thread prod (producer);
        thread cons (consumer);

        prod.join();
        cons.join();
    }

    // Multi-threaded Producer Consumer Problem
    {
        cout << endl << "Multi Threaded Producer Consumer Problem" << endl;
        thread prodThreads[NUM_THREADS];
        thread consThreads[NUM_THREADS];

        for (uint32_t i = 0; i < NUM_THREADS; i++)
        {
            prodThreads[i] = thread(producer);
            consThreads[i] = thread(consumer);
        }

        for (uint32_t i = 0; i < NUM_THREADS; i++)
        {
            prodThreads[i].join();
            consThreads[i].join();
        }
    }

    // 2. Simple Thread Synchronization Problem
    {
        printStockSticker(0);
        printStockPrices(0);
    }

    cout << endl;
    return 0;
}
