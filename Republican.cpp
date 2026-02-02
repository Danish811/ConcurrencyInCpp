#include <bits/stdc++.h>
#include <thread>
#include <mutex>
#include <condition_variable>
using namespace std;

class Bathroom {
private:
    mutex mtx;
    condition_variable cv;

    int inside = 0;
    char gender = 'U'; // U, M, F

public:
    void maleUse(string name) {
        unique_lock<mutex> lock(mtx);
        cv.wait(lock, [&] {
            return (gender == 'U' || gender == 'M') && inside < 3;
        });

        gender = 'M';
        inside++;
        cout << name << " (M) entered | inside=" << inside << "\n";

        lock.unlock();
        this_thread::sleep_for(chrono::seconds(1));
        lock.lock();

        inside--;
        cout << name << " (M) leaving | inside=" << inside << "\n";
        if (inside == 0) gender = 'U';

        cv.notify_all();
    }

    void femaleUse(string name) {
        unique_lock<mutex> lock(mtx);
        cv.wait(lock, [&] {
            return (gender == 'U' || gender == 'F') && inside < 3;
        });

        gender = 'F';
        inside++;
        cout << name << " (F) entered | inside=" << inside << "\n";

        lock.unlock();
        this_thread::sleep_for(chrono::seconds(3));
        lock.lock();

        inside--;
        cout << name << " (F) leaving | inside=" << inside << "\n";
        if (inside == 0) gender = 'U';

        cv.notify_all();
    }
};



void test() {
    Bathroom B;
    vector<thread> threads;

    // Create many users
    vector<string> males = {
        "John", "Mike", "Alex", "Bob", "Chris", "David"
    };
    vector<string> females = {
        "Sarah", "Emma", "Olivia", "Sophia", "Mia", "Lily"
    };

    // Launch threads in mixed order
    for (int i = 0; i < 6; i++) {
        threads.emplace_back(&Bathroom::maleUse, &B, males[i]);
        threads.emplace_back(&Bathroom::femaleUse, &B, females[i]);
    }

    // Join all
    for (auto &t : threads) {
        t.join();
    }

    cout << "All threads finished.\n";
}
int main(){
    test();
}