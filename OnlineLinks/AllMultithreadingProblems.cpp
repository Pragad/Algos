#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm> // For sort
#include <thread>
#include <chrono>   // Sleep
#include <mutex>
#include <condition_variable>
#include <queue>
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
static const int MAX_SIZE = 10;
static const int MAX_BUFFER_SIZE = 5;
static const uint32_t NUM_THREADS = 5;
static uint32_t BUFFER[MAX_BUFFER_SIZE];
static vector<uint32_t> VEC_BUFFER;

std::mutex mtx;
std::condition_variable cv;

void producer()
{
    for (uint32_t i = 0; i < MAX_SIZE; i++)
    {
        cout << "Pro i: " << i << endl;
        // Take a lock on the mutex
        unique_lock<std::mutex> prodLock(mtx);
        if (VEC_BUFFER.size() > MAX_BUFFER_SIZE)
        {
            // Wait if Producer does not have space to put into the buffer
            // The execution of the current thread is blocked until notified.
            cout << "Producer waiting.." << endl;
            cv.wait(prodLock);
        }
        // Once consumer notifies back the producer, producer should insert that element
        // So Comment below ELSE block
        //else
        //{
            cout << "Produced: " << i << endl;
            VEC_BUFFER.push_back(i);
        //}

        if (VEC_BUFFER.size() == 1)
        {
            // Notify the client if Producer has produced the first element and put it into
            // the buffer
            cout << "Producer notifying consumer as there is one entry to free" << endl;
            cv.notify_one();
        }
    }
    // VERY IMP: Once done with loop if there are consumers waiting for producer
    // to produce then notify them
    cv.notify_one();
}

void consumer()
{
    for (uint32_t i = 0; i < MAX_SIZE; i++)
    {
        cout << "Con i: " << i << endl;
        this_thread::sleep_for(chrono::milliseconds(100));
        // Take a lock on the mutex
        // When a  second consumer comes, it has to wait
        unique_lock<std::mutex> consLock(mtx);
        if (VEC_BUFFER.size() < 1)
        {
            cout << "Consumer waiting.." << endl;
            cv.wait(consLock);
        }
        //else
        //{
            cout << "Consumed: " << VEC_BUFFER.back() << endl;
            VEC_BUFFER.pop_back();
        //}

        if (VEC_BUFFER.size() == MAX_BUFFER_SIZE - 1)
        {
            // Notify the Producer once the last element is consumed and there is space for
            // adding elements
            cout << "Consumer notifying producer as there is one spot free" << endl;
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
std::mutex mtx2;
std::atomic<bool> flag {false};

void printList1()
{
    // Take a mutex lock
    // So when thread1 is printing List1, thread2 can't print list 2
    unique_lock<std::mutex> list1Lock(mtx2);

    cout << "1. ";
    for (uint32_t i = 0; i < list1.size(); i++)
    {
        cout << list1[i] << ", ";
    }
    cout << endl;

    flag.store(true);
    condVar.notify_one();
}

void printList2()
{
    // Take a mutex lock
    // So when thread1 is printing List1, thread2 can't print list 2
    unique_lock<std::mutex> list2Lock(mtx2);

    // If the flag has not been set then wait for it
    if (!flag)
    {
        // IMP: Wait will release the lock that this thread has been holding so that thread1
        // can acquire the mutex and print list1
        condVar.wait(list2Lock);
    }

    cout << "2. ";
    for (uint32_t i = 0; i < list2.size(); i++)
    {
        cout << list2[i] << ", ";
    }
    cout << endl;

    // Set flag back to false
    flag.store(false);
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
static const vector<string> stockSticker = {"NTAP", "FB", "GOOG", "TSLA", "LUV", "M"};
static const vector<uint32_t> stockPrices = {35, 105, 780, 250, 42, 38};

std::condition_variable condVar3;
std::mutex mtx3;
std::atomic<bool> th1 {false};
std::atomic<bool> th2 {false};

void printStockSticker(uint32_t index)
{
    // Take a mutex lock
    unique_lock<std::mutex> stickerLock(mtx3);

    // Make sure th2 was the last guy that was executed. Only then we should print an item
    // from list1.
    // Otherwise we should wait till th2 prints an item
    for (uint32_t i = 0; i < stockSticker.size(); i++)
    {
        th2.store(false);
        cout << stockSticker[index] << " - ";
        index++;

        th1.store(true);
        condVar3.notify_one();
        condVar3.wait(stickerLock);
    }

    // Make sure to wake the other thread. Else it will be waiting forever
    condVar3.notify_one();

    cout << "List 1 done" << endl;
}

void printStockPrices(uint32_t index)
{
    unique_lock<std::mutex> stockLock(mtx3);

    // Make sure th1 was the last guy that was executed. Only then we should print an item
    // from list2.
    // Otherwise we should wait till th1 prints an item.
    if (!th1)
    {
        condVar3.wait(stockLock);
    }

    for (uint32_t i = 0; i < stockPrices.size(); i++)
    {
        th1.store(false);
        cout << stockPrices[index] << endl;
        index++;

        th2.store(true);
        condVar3.notify_one();
        condVar3.wait(stockLock);
    }

    cout << "List 2 done" << endl;
}

// -----------------------------------------------------------------------------
// Producer consumer using classes
// https://codereview.stackexchange.com/questions/84109/a-multi-threaded-producer-consumer-with-c11
// -----------------------------------------------------------------------------
class Buffer {
private:
    queue<int> buffer;
    int count;
    int capacity;
    mutex mtx;
    condition_variable cv;

public:
    Buffer() : capacity (5),
               count(0) { }
    Buffer(int capacity) : capacity(capacity),
                           count(0) { }

    void produce() {
        cout << "In produce" << endl;
        unique_lock<mutex> produceLock(mtx);
        if (buffer.size() == capacity) {
            cout << "Producer waiting.." << endl;
            cv.wait(produceLock);
        }
        buffer.push(count);
        cout << "Produced: " << count << endl;
        count++;
        produceLock.unlock();
        // Can do this unconditionally
        cout << "Producer notifying consumers.." << endl;
        cv.notify_all();
    }

    void consume() {
        unique_lock<mutex> consumeLock(mtx);
        if (buffer.size() == 0) {
            cout << "Consumer waiting.." << endl;
            cv.wait(consumeLock);
        }
        cout << "Consumed: " << buffer.front() << endl;
        buffer.pop();
        consumeLock.unlock();
        // Can do this unconditionally
        cout << "Consumer notifying producers.." << endl;
        cv.notify_one();
    }
};

class Producer {
private:
    Buffer& _b;

public:
    Producer(Buffer& b) : _b(b) { }

    void produce() {
        cout << "About to call produce\n";
        for (int i = 0; i < 10; i++) {
            _b.produce();
        }
    }
};

class Consumer {
private:
    Buffer& _b;

public:
    Consumer(Buffer& b) : _b(b) { }

    void consume() {
        for (int i = 0; i < 10; i++) {
            _b.consume();
        }
    }
};

// -----------------------------------------------------------------------------
// Reader writer problem
// -----------------------------------------------------------------------------
class ReadWriteLock {
private:
    mutex _mtx;
    condition_variable _cv;
    int _waitingReaders;
    int _waitingWriters;

public:
    ReadWriteLock() : _waitingReaders(0),
                      _waitingWriters(0) { }

    void readLock() {
        unique_lock<mutex> lock(mtx);
        if (_waitingWriters > 0) {
        }
    }

    void readUnlock() {
    }

    void writeLock() {
    }

    void writeUnlock() {
    }
};

// -----------------------------------------------------------------------------
// Counter
// -----------------------------------------------------------------------------
int counter = 0;
void increaseCounter() {
    while (true) {
        cout << "\nTid: " << this_thread::get_id() << endl;
        if (counter == 10) {
            cout << "\nThread return tid: " << this_thread::get_id() << endl;
            return;
        }
        counter++;
        cout << "\nTid: " << this_thread::get_id() << "; Counter: " << counter << endl;
    }
}

// -----------------------------------------------------------------------------
// Main Function
// -----------------------------------------------------------------------------
int main()
{
    // PROBLEM 1. Single Threaded Producer Consumer Problem
    /*
    {
        cout << endl << "Problem 1: Single Threaded Producer Consumer Problem" << endl;
        thread prod (producer);
        thread cons (consumer);

        prod.join();
        cons.join();
    }

    // Multi-threaded Producer Consumer Problem
    {
        cout << endl << "Problem 1: Multi Threaded Producer Consumer Problem" << endl;
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

    // 2. Simple Thread Synchronization Problem. Print one list fully and then another list
    {
        cout << endl << "Problem 2: " << endl;
        thread thPrintList1 (printList1);
        thread thPrintList2 (printList2);

        thPrintList1.join();
        thPrintList2.join();
    }

    // 3. Thread Synchronization Problem. Print one entry in each list
    {
        cout << endl << "Problem 3: " << endl;
        thread thPrintList3a (printStockSticker, 0);
        thread thPrintList3b (printStockPrices, 0);

        thPrintList3a.join();
        thPrintList3b.join();
    }
    */

    // Problem 4. Producer consumer using classes
    {
        cout << endl << "Problem 4. Producer consumer using classes" << endl;
        Buffer b;
        Producer p(b);
        /*
        Consumer c(b);
        thread prod(&Producer::produce, Producer(b));
        thread prod(&Producer::produce, &p);
        */
        thread prod(&Producer::produce, p);
        prod.join();
        /*
        //thread cons(&Consumer::consume, c);
        //cons.join();
        */
    }

    {
        thread t1(increaseCounter);
        thread t2(increaseCounter);
        t1.join();
        t2.join();
        cout << "Counter: " << counter << endl;
    }
    cout << endl;
    return 0;
}
