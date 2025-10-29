// SPDX-License-Identifier: BSD-3-Clause

#include <internal/syscall.h>
#include <time.h>
#include <errno.h>

unsigned int sleep(unsigned int seconds)
{
    struct timespec rem = {0, 0};
    struct timespec time;
    time.tv_nsec = 0;
    time.tv_sec = seconds;
    if (nanosleep(&time, &rem)) {
        return time.tv_sec;
    }
    return 0;
}
