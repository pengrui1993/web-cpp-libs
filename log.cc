#include <glog/logging.h>

void log_init(){
    google::SetLogDestination(0,".");
    google::InitGoogleLogging("raiser"); 
    google::SetLogSymlink(google::GLOG_INFO, "raiser_curr");
}

std::ostream& log(){
    return LOG(INFO);
}
std::ostream& syslog(){
    return SYSLOG(INFO);
}