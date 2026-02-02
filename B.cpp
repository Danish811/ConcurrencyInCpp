#include <bits/stdc++.h>
#include<vector>
#include <thread>
using namespace std;
void HelloWorld() {
     cout << "Hello World " << this_thread::get_id() << endl;
}

int main() {
    printf("%d\n", this_thread::get_id());
    vector<thread> threads;

    int n = thread::hardware_concurrency();
    cout << "hardware concurrency "<< n << endl;
    for(int i=0; i<5; i++){
        threads.push_back(thread(HelloWorld));
    }
    thread t(HelloWorld);
    t.join();
    for(int i=0; i<5; i++){
        threads[i].join();
    }

}
