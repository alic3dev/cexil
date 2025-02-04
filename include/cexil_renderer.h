#ifndef __CEXIL_RENDERER_H
#define __CEXIL_RENDERER_H

#include "cexil_size.h"
#include "cexil_sprite.h"

struct cexil_renderer {
  char** pixels;
  struct cexil_size size;
  struct cexil_sprite** sprites;
  unsigned int sprites_length;
};

void cexil_renderer_render(
  struct cexil_renderer*
);

void cexil_renderer_sprite_add(
  struct cexil_renderer*,
  struct cexil_sprite*
);

void cexil_renderer_destroy(
  struct cexil_renderer*
);

#endif

