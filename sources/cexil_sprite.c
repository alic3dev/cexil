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

  sprite->render_offset.x = 0;
  sprite->render_offset.y = 0;
  sprite->render_size.width = sprite->size.width;
  sprite->render_size.height = (
    sprite->size.height
  );
}

void cexil_sprite_fill(
  struct cexil_sprite* sprite
) {
  for (
    unsigned int y = 0;
    y < sprite->size.height;
    ++y
  ) {
    for (
      unsigned int x = 0;
      x < sprite->size.width;
      ++x
    ) {
      sprite->pixels[y][x] = 1;
    }
  }
}

void cexil_sprite_render_offset_set(
  struct cexil_sprite* sprite,
  struct cexil_position* offset
) {
  sprite->render_offset.x = offset->x;
  sprite->render_offset.y = offset->y;
}

void cexil_sprite_render_size_set(
  struct cexil_sprite* sprite,
  struct cexil_size* size
) {
  sprite->render_size.width = size->width;
  sprite->render_size.height = size->height;
}

void cexil_sprite_render_set(
  struct cexil_sprite* sprite,
  struct cexil_position* offset,
  struct cexil_size* size
) {
  cexil_sprite_render_offset_set(sprite, offset);
  cexil_sprite_render_size_set(sprite, size);
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

