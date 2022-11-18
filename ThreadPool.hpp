//
//  ThreadPool.hpp
//  PuzzleGames
//
//  Created by James Folk on 10/27/22.
//

#ifndef ThreadPool_hpp
#define ThreadPool_hpp

#include <functional>
#include <mutex>
#include <thread>
#include <vector>
#include <queue>

class ThreadPool {
public:
    void Start();
    void QueueJob(const std::function<void()>& job);
    void Stop();
    bool Busy();

private:
    void ThreadLoop();

    bool should_terminate = false;           // Tells threads to stop looking for jobs
    std::mutex queue_mutex;                  // Prevents data races to the job queue
    std::condition_variable mutex_condition; // Allows threads to wait on new jobs or termination
    std::vector<std::thread> threads;
    std::queue<std::function<void()>> jobs;
};

#endif /* ThreadPool_hpp */
