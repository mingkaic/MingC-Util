#include <thread>
#include <mutex>
#include <chrono>
#include <condition_variable>
#include "../structures/header/lists.hpp"

template <typename T>
class PCBuffer
    {
    public:
        void add(T d) {
            while (true) {
                std::unique_lock<std::mutex> locker(mu);
                buffer_.push_front(d);
                locker.unlock();
                cond.notify_all();
                return;
            }
        }
        T remove() {
            while (true) {
                std::unique_lock<std::mutex> locker(mu);
                cond.wait(locker, [this](){
                    return false == this->buffer_.isEmpty();
                });
                T back = buffer_.pop_back();
                locker.unlock();
                cond.notify_all();
                return back;
            }
        }
        PCBuffer() {}
    private:
        std::mutex mu;
        std::condition_variable cond;

        list::queue<T> buffer_;
    };