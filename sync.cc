#include<functional>
#include<thread>
#include<mutex>
#include<condition_variable>
#include<queue>
#include<iostream>
#include"sync.h"
namespace{
std::thread* worker{nullptr};
volatile bool prepared{false};
std::mutex mtx;
std::condition_variable cond;
volatile bool consumerIsWaiting{false};
std::queue<Task> queue;
uint32_t counter{0};
void loop(){
    std::cout << counter <<" sync.loop running..." << std::endl;
    while(prepared){
       {
            std::unique_lock<std::mutex> l(mtx);
            if(queue.empty()){
                consumerIsWaiting = true;
                cond.wait(l,[](){return !queue.empty();});
                consumerIsWaiting = false;
                l.unlock();
            }else{
                counter++;
                auto& task = queue.back();
                queue.pop();
                l.unlock();
                std::cout << counter <<" task start in sync..." << std::endl;
                task();
                std::cout << counter <<" task done in sync..." << std::endl;
            }
       }
    }
    while(!queue.empty()){
        auto& task = queue.back();
        queue.pop();
        task();
    }
    std::cout << counter <<" sync.loop done..." << std::endl;
}
}
void sync_init(){
    if(prepared)return;
    std::cout << "sync init..." << std::endl;
    worker = new std::thread(loop);
    prepared = true;
}
void sync_exit(){
    if(!prepared)return;
    prepared = false;
    if(consumerIsWaiting){
        std::lock_guard<std::mutex> g(mtx);
        queue.push([](){std::cout<< "empty task..." << std::endl;});
        cond.notify_all();
    }
    worker->join();
    delete worker;
    worker = nullptr;
    std::cout << "sync exit done..." << std::endl;
}
bool sync_task_submit(Task task){
    if(!prepared)return false;
    {
        std::lock_guard<std::mutex> g(mtx);
        queue.push(task);
        if(consumerIsWaiting){
            cond.notify_all();
        }
    }
    return true;
}
