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

// -----------------------------------------------------------------------------------------------
// PROBLEM 2. Simple Multi threading synchronization problem
// Have two functions and two lists.
// Thread1 should start first and print everything in list1
// Thread2 should start after thread1 and print everything in list2
// -----------------------------------------------------------------------------------------------
static const vector<string> list1 = {"NTAP", "FB", "GOOG", "TSLA", "LUV", "M"};
static const vector<uint32_t> list2 = {35, 105, 780, 250, 42, 38};

std::condition_variable condVar;
//std::mutex mtx2;
std::atomic<bool> flag {false};

void printList1()
{
    // Take a mutex lock
    //unique_lock<std::mutex> stickerLock(mtx2);

    cout << "1. ";
    for (uint32_t i = 0; i < list1.size(); i++)
    {
        cout << list1[i] << ", ";
        i++;
    }

    flag.store(true);
}

void printList2()
{
    //unique_lock<std::mutex> stockLock(mtx2);

    if (!flag)
    {
        condVar.wait();
    }

    cout << "2. ";
    for (uint32_t i = 0; i < list2.size(); i++)
    {
        cout << list2[i] << ", ";
        i++;
    }
}

// ----------------------------------------------------------------------------------------------
// PROBLEM 3. Simple Multi threading synchronization problem to print Stocks and Prices
// Have two lists, one containing stock stickers and one containing the corresponding prices
//
// Thread1 should start first and print One entry in StockSticker list
// Then thread1 should pass control to thread2
// Thread2 should print its top entry in the list
// Then thread2 should pass control to thread1
// ----------------------------------------------------------------------------------------------
/*
static const vector<string> stockSticker = {"NTAP", "FB", "GOOG", "TSLA", "LUV", "M"};
static const vector<uint32_t> stockPrices = {35, 105, 780, 250, 42, 38};

std::condition_variable condVar;
std::mutex mtx2;
std::atomic<bool> flag {false};

void printStockSticker(uint32_t index)
{
    // Take a mutex lock
    unique_lock<std::mutex> stickerLock(mtx2);
    flag = true;

    if (flag && index < stockSticker.size())
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

    if (flag && index < stockSticker.size())
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
*/
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
        thread thPrintList1 (printList1);
        thread thPrintList2 (printList2);

        printSticker.join();
        printPrices.join();
    }

    cout << endl;
    return 0;
}
