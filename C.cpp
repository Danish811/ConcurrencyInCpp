#include<iostream>
#include<thread>
#include<mutex>
#include<shared_mutex>
using namespace std;

/*
A race condition occurs when two or more concurrent execution contexts access the same memory location 
or shared resource, at least one access is a write, and the program’s behavior varies depending on 
the execution order of those accesses.

A race condition is a concurrency error where program correctness depends on 
uncontrollable execution order due to unsynchronized access to shared mutable state.
*/

mutex mtx;
void deleteNthNode(Node *nthNode){
    lock_guard<mutex> lock(mtx);
    nthNode->prev->next = nthNode->next;
    nthNode->next->prev = nthNode->prev;
    delete(nthNode);
}
// Here lock_guard locks the function and releases 
// when the function finishes

// But what if i want to control where the lock unlocks
// then we use
unique_lock<mutex> Lock(mtx);
Lock.unlock();


std::shared_mutex mtx;
int shared_value = 107;
int getValue() {
    shared_lock<shared_mutex> lock(mtx);
    return shared_value;   // safe concurrent read
}

// std::unique_lock (write lock)
// Writers must use exclusive locking:
void setValue(int v) {
    std::unique_lock<std::shared_mutex> lock(mtx);
    shared_value = v;      // exclusive access
}
// Only one writer can hold the lock, and no readers are allowed simultaneously.

/*
Correct mental model

shared_lock → “I promise not to modify”

unique_lock → “I intend to modify”

shared_mutex → enforces those promises
*/
