#include<iostream>
#include<thread>
#include<mutex>
using namespace std;
/*
To solve the producer-consumer problem:

A condition variable is a synchronization primitive that allows a thread 
to sleep efficiently until a specific condition on shared state becomes true, 
while atomically releasing a mutex during the wait and reacquiring it upon wake-up.
*/
condition_variable cv;
void pushToMessageQueue(int message){
    unique_lock<mutex> lock(mtx);
    messageQueue.push(message);
    cv.notify_one();
}
void consume(){
    while(1){
        unique_lock<mutex> lock(mtx);
        cv.wait(lock, []{ return !messageQueue.empty(); });
        messageQueue.pop();
    }
}
// cv.wait will make the consumer thread sleep
// and also release the lock, not blockign the producer