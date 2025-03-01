#ifndef __CEXIL_TIMER_H
#define __CEXIL_TIMER_H

#include <sys/time.h>

struct cexil_timer {
  struct timeval time_starting;
  struct timeval time_ending;  
};

void cexil_timer_start(struct cexil_timer*);
void cexil_timer_stop(struct cexil_timer*);

unsigned long long int cexil_timer_time_difference(struct timeval*, struct timeval*);
unsigned long long int cexil_timer_time_elapsed(struct cexil_timer*);
unsigned long long int cexil_timer_time_total(struct cexil_timer*);

#endif

