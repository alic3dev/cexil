#include "cexil_time.h"

#include <time.h>

void cexil_time_initialize(
  struct cexil_time* cexil_time,
  unsigned long long int seconds,
  unsigned long long int nano_seconds
) {
  cexil_time->timespec.tv_sec = seconds;
  cexil_time->timespec.tv_nsec = nano_seconds;
}

void cexil_time_nanosleep(struct cexil_time* cexil_time) {
  nanosleep(&cexil_time->timespec, (void*)0);
}

