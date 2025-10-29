// SPDX-License-Identifier: BSD-3-Clause

#include <stdio.h>
#include <internal/syscall.h>
#include <errno.h>
#include <string.h>

int puts(const char *s)
{
    int n = strlen(s);
    int ret = syscall(__NR_write, 1, s, n);

    if (ret < 0) {
        errno = -ret;
        return -1;
    }

    ret = syscall(__NR_write, 1, "\n", 1);

    if (ret < 0) {
        errno = -ret;
        return -1;
    }

    return ret;
}
