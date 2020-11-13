#ifndef UTIL_H
#define UTIL_H

#ifdef _WIN32
#include <Windows.h>
#define SLEEP_FACTOR 1000
#else
#include <unistd.h>
#define SLEEP_FACTOR 1
#endif

void tba_sleep(int d) {
    sleep(d * SLEEP_FACTOR);
}

#endif