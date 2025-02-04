#include "cexil_sprite.h"

#include <stdlib.h>

void cexil_sprite_initialize(
  struct cexil_sprite* sprite
) {
  sprite->size.width = 0;
  sprite->size.height = 0;
  sprite->position.x = 0;
  sprite->position.y = 0;
  sprite->blend_mode = or;
  sprite->pixels = malloc(0);
  sprite->frames = malloc(0);
}

void cexil_sprite_destroy(
  struct cexil_sprite* sprite
) {
  free(sprite->pixels);
  free(sprite->frames);
}

