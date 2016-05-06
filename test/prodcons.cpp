#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>
#include <condition_variable>
#include "../structures/header/lists.hpp"

class PCBuffer
    {
    public:
        void add(double d) {
            while (true) {
                std::unique_lock<std::mutex> locker(mu);
                buffer_.push_front(d);
                locker.unlock();
                cond.notify_all();
                return;
            }
        }
        double remove() {
            while (true) {
                std::unique_lock<std::mutex> locker(mu);
                cond.wait(locker, [this](){
                    return false == buffer_.isEmpty();
                });
                double back = buffer_.pop_back();
                locker.unlock();
                cond.notify_all();
                return back;
            }
        }
        PCBuffer() {}
    private:
       // Add them as member variables here
        std::mutex mu;
        std::condition_variable cond;

       // Your normal variables here
        queue<double> buffer_;
    };