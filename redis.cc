#include <sw/redis++/redis++.h>
#include <iostream>
void test_redis(){
    using sw::redis::Redis;
	try{
        auto redis = Redis("tcp://127.0.0.1:6379");
        redis.set("key", "val");
        auto val = redis.get("key");    
        if (val) {
            std::cout << *val << std::endl;
        }
	}catch(...){
		std::cerr << "error ..." << std::endl;
	}
}