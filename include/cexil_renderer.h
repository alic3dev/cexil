#ifndef __CEXIL_RENDERER_H
#define __CEXIL_RENDERER_H

#include "cexil_size.h"
#include "cexil_sprite.h"
#include "cexil_text.h"

struct cexil_renderer {
  char** pixels;
  struct cexil_size size;
  struct cexil_sprite** sprites;
  unsigned int sprites_length;
  struct cexil_text** texts;
  unsigned int texts_length;
};

void cexil_renderer_initialize(
  struct cexil_renderer*,
  struct cexil_size*
);

void cexil_renderer_size_set(
  struct cexil_renderer*,
  struct cexil_size*
);

void cexil_renderer_render(
  struct cexil_renderer*
);

void cexil_renderer_render_clear(
  struct cexil_renderer*
);

void cexil_renderer_render_sprites(
  struct cexil_renderer*
);

void cexil_renderer_render_texts(
  struct cexil_renderer*
);

void cexil_renderer_sprite_add(
  struct cexil_renderer*,
  struct cexil_sprite*
);

void cexil_renderer_sprite_render(
  struct cexil_renderer*,
  struct cexil_sprite*
);

void cexil_renderer_text_add(
  struct cexil_renderer*,
  struct cexil_text*
);

void cexil_renderer_text_render(
  struct cexil_renderer*,
  struct cexil_text*
);

void cexil_renderer_destroy(
  struct cexil_renderer*
);

#endif

