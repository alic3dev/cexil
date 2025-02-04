#include "cexil_renderer.h"

#include <stdio.h>
#include <stdlib.h>

void cexil_renderer_initialize(
  struct cexil_renderer* renderer
) {
  renderer->size.width = 0;
  renderer->size.height = 0;
  renderer->pixels = malloc(
    sizeof(unsigned char) *
      renderer->size.width *
      renderer->size.height
  );
  renderer->sprites_length = 0;
  renderer->sprites = malloc(
    sizeof(struct cexil_sprite*) *
    renderer->sprites_length
  );
}

void cexil_renderer_render(
  struct cexil_renderer* renderer
) {
  
}

void cexil_renderer_sprite_add(
  struct cexil_renderer* renderer,
  struct cexil_sprite* sprite
) {
  renderer->sprites_length = (
    renderer->sprites_length + 1
  );

  renderer->sprites = realloc(
    renderer->sprites,
    sizeof(struct cexil_sprite*) *
      renderer->sprites_length
  );

  renderer->sprites[
    renderer->sprites_length - 1
  ] = sprite;
}

void cexil_renderer_destroy(
  struct cexil_renderer* renderer
) {
  free(renderer->pixels);
  free(renderer->sprites);
}

