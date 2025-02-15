#ifndef __CEXIL_TIME_H
#define __CEXIL_TIME_H

#include <time.h>

struct cexil_time {
  struct timespec timespec;
};

void cexil_time_initialize(struct cexil_time*, unsigned long long, unsigned long long);
void cexil_time_sleep(struct cexil_time*);

#endif

