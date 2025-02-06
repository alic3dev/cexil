#ifndef __CEXIL_COLLISION_H
#define __CEXIL_COLLISION_H

#include "cexil_position.h"
#include "cexil_size.h"

unsigned char cexil_collision_intersects(
  struct cexil_position*,
  struct cexil_size*,
  struct cexil_position*,
  struct cexil_size*
);

unsigned char cexil_collision_will_intersect(
  struct cexil_position*,
  struct cexil_size*,
  struct cexil_position*,
  struct cexil_size*,
  struct cexil_position*
);

#endif

