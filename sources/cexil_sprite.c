#include "cexil_sprite.h"

#include <stdlib.h>

void cexil_sprite_initialize(
  struct cexil_sprite* sprite,
  struct cexil_size* size
) {
  sprite->size.width = size->width;
  sprite->size.height = size->height;
  sprite->position.x = 0;
  sprite->position.y = 0;
  sprite->blend_mode = or;
  sprite->pixels = malloc(
    sizeof(unsigned char*) *
    sprite->size.height
  );
  for (
    unsigned int y = 0;
    y < sprite->size.height;
    ++y
  ) {
    sprite->pixels[y] = malloc(
      sizeof(unsigned char) *
      sprite->size.width
    );

    for (
      unsigned int x = 0;
      x < sprite->size.width;
      ++x
    ) {
      sprite->pixels[y][x] = 0;
    }
  }
  sprite->frames = malloc(0);
}

void cexil_sprite_destroy(
  struct cexil_sprite* sprite
) {
  for (
    unsigned int y = 0;
    y < sprite->size.height;
    ++y
  ) {
    free(sprite->pixels[y]);
  }

  free(sprite->pixels);
  free(sprite->frames);
}

