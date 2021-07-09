
//Copyright 2021 Stratify Labs, See LICENSE.md for details

#ifndef CONFIG_OS_CONFIG_H_
#define CONFIG_OS_CONFIG_H_

#include <sdk/types.h>
#include <pthread.h>

void os_event_handler(int event, void *args); // optional event handler

pthread_t os_start_thread(
    void *(*thread_function)(void *),
    void *thread_argument,
    u32 stack_size,
    int scheduler_policy,
    int scheduler_priority);

#endif /* CONFIG_OS_CONFIG_H_ */
