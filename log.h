#ifndef _LOG_H__
#define _LOG_H__
#include<iostream>
extern void log_init();
extern std::ostream& log();
extern std::ostream& syslog();
#endif