#include "cexil_collision.h"

unsigned char cexil_collision_intersects(
  struct cexil_position* position_a,
  struct cexil_size* size_a,
  struct cexil_position* position_b,
  struct cexil_size* size_b
) {
  struct cexil_position position_a_max;
  position_a_max.x = (
    position_a->x + size_a->width
  );
  position_a_max.y = (
    position_a->y + size_a->height
  );

  struct cexil_position position_b_max;
  position_b_max.x = (
    position_b->x + size_b->width
  );
  position_b_max.y = (
    position_b->y + size_b->height
  );

  if (
    position_a->x >= position_b->x &&
    position_a->x <= position_b_max.x &&
    position_a->y >= position_b->y &&
    position_a->y <= position_b_max.y
  ) {
    return 1;
  } else if (
    position_a_max.x >= position_b->x &&
    position_a_max.x <= position_b_max.x &&
    position_a->y >= position_b->y &&
    position_a->y <= position_b_max.y
  ) {
    return 1;
  } else if (
    position_a->x >= position_b->x &&
    position_a->x <= position_b_max.x &&
    position_a_max.y >= position_b->y &&
    position_a_max.y <= position_b_max.y
  ) {
    return 1;
  } else if (
    position_a_max.x >= position_b->x &&
    position_a_max.x <= position_b_max.x &&
    position_a_max.y >= position_b->y &&
    position_a_max.y <= position_b_max.y
  ) {
    return 1;
  }

  return 0;
}

unsigned char cexil_collision_will_intersect(
  struct cexil_position* position_a,
  struct cexil_size* size_a,
  struct cexil_position* position_b,
  struct cexil_size* size_b,
  struct cexil_position* translation
) {
  struct cexil_position position_a_translated;
  position_a_translated.x = (
    position_a->x + translation->x
  );
  position_a_translated.y = (
    position_a->y + translation->y
  );

  return cexil_collision_intersects(
    &position_a_translated,
    size_a,
    position_b,
    size_b
  );
}

