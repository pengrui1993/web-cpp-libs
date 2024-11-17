#include <httplib.h>
#include <iostream>
#include <cstdlib>
#include <thread>
#include "log.h"
#include "sync.h"
#define PORT "8080"
extern void test_json();
extern void test_redis();
extern void test_mysql();
extern void test_rabbit();


int main(){
    log_init();
    sync_init();
    // test_json();
    // test_redis();
    // test_mysql();
    // test_rabbit();
    using httplib::Server;
    using httplib::Request;
    using httplib::Response;
    Server svr;
    svr.Get("/", [](const Request& req, Response& res) {
        std::cout << "server thread:" << std::this_thread::get_id() << std::endl;
        sync_task_submit([](){
            std::cout << "sync thread:" << std::this_thread::get_id() << std::endl;
        });
        res.set_content("Hello World!", "text/plain");
    });
    svr.Get("/stop", [&](const Request& req, Response& res) {
        svr.stop();
    });

    if(!svr.listen("localhost", atoi(PORT))){
        log() << "port:" PORT" bound failed";
    }
    sync_exit();
    syslog()  << "exit...";
    return 0;
}