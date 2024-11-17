#ifndef _SYNC_H__
#define _SYNC_H__
#include<iostream>
using Task = std::function<void(void)>;
extern void sync_init();
extern void sync_exit();
extern bool sync_task_submit(Task task);
#endif