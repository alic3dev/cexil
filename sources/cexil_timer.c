#include "cexil_timer.h"

void cexil_timer_start(struct cexil_timer* cexil_timer) {
  gettimeofday(&cexil_timer->time_starting, (void*)0);
}

void cexil_timer_stop(struct cexil_timer* cexil_timer) {
  gettimeofday(&cexil_timer->time_ending, (void*)0);
}

unsigned long long int cexil_timer_time_difference(struct timeval* timeval_a, struct timeval* timeval_b) {
  return (
    ((timeval_b->tv_sec * 1000000) + timeval_b->tv_usec) -
    ((timeval_a->tv_sec * 1000000) + timeval_a->tv_usec)
  );
}

unsigned long long int cexil_timer_time_elapsed(struct cexil_timer* cexil_timer) {
  struct timeval time_current;

  gettimeofday(&time_current, (void*)0);

  return cexil_timer_time_difference(&cexil_timer->time_starting, &time_current);
}

unsigned long long int cexil_timer_time_total(struct cexil_timer* cexil_timer) {
  return cexil_timer_time_difference(&cexil_timer->time_starting, &cexil_timer->time_ending);
}

