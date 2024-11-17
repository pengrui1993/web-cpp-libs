#required cmake 3.22 or later
#ubuntu 
#g++:sudo apt install build-essential
#openssl:sudo apt install libssl-dev
#boost:sudo apt install libboost-dev
#hiredis:sudo apt install libhiredis-dev

#macos
#openssl:brew install openssl
#boot:brew install boost
#hiredis:brew install hiredis
CXXFLAGS += -std=c++17
HTTP_SERVER_INCLUDE:=./_demo_httplib/build
HTTP_SERVER_LIB:=$(HTTP_SERVER_INCLUDE)
JSON_INCLUDE:=./json/include
REDIS_DIR:=./_demo_redispp/build/pkg
REDIS_INCLUDE:=$(REDIS_DIR)/include
REDIS_LIB:=$(REDIS_DIR)/lib
SHARED_INCLUDE:=/opt/homebrew/include
SHARED_LIB:=/opt/homebrew/lib

RABBIT_DIR:=./_demo_rabbitmq/build/pkg
RABBIT_INCLUDE:=$(RABBIT_DIR)/include
RABBIT_LIB:=$(RABBIT_DIR)/lib
CXXFLAGS += -I$(HTTP_SERVER_INCLUDE) \
		-I$(JSON_INCLUDE) \
		-I$(REDIS_INCLUDE) \
		-I${SHARED_INCLUDE} \
		-I${RABBIT_INCLUDE} \
	$(shell pkg-config --cflags libglog gflags) \
	$(shell pkg-config --cflags gtest) \
	$(shell pkg-config --cflags hiredis) \
	$(shell pkg-config --cflags openssl)

#hiredis for redis++
LDFLAGS += -L${HTTP_SERVER_LIB} \
	-L$(REDIS_LIB) \
	-L$(SHARED_LIB) \
	-L$(RABBIT_LIB) \
	$(shell pkg-config --libs libglog gflags) \
	$(shell pkg-config --libs gtest) \
	$(shell pkg-config --libs hiredis) \
	$(shell pkg-config --libs openssl)

LDLIBS += -lboost_charconv -lcpp-httplib -lredis++ -lamqpcpp -lpthread \
		-pthread json.cc log.cc redis.cc mysql.cc rabbit.cc sync.cc
# lboost_charconv for mysql
