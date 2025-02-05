#ifndef __CEXIL_SPRITE_H
#define __CEXIL_SPRITE_H

#include "cexil_blend_mode.h"
#include "cexil_position.h"
#include "cexil_size.h"

struct cexil_sprite {
  struct cexil_position position;
  struct cexil_size size;
  char** pixels;
  char*** frames;
  enum cexil_blend_mode blend_mode;
};

void cexil_sprite_initialize(
  struct cexil_sprite*,
  struct cexil_size*
);

void cexil_sprite_destroy(
  struct cexil_sprite*
);

#endif

