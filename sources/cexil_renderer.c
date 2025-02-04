#include "cexil_renderer.h"

#include <stdio.h>
#include <stdlib.h>

#include "cexil_pixel_mapping.h"

void cexil_renderer_initialize(
  struct cexil_renderer* renderer,
  struct cexil_size* size
) {
  cexil_renderer_size_set(
    renderer,
    size
  );
  
  renderer->sprites_length = 0;
  renderer->sprites = malloc(
    sizeof(struct cexil_sprite*) *
    renderer->sprites_length
  );
}

void cexil_renderer_size_set(
  struct cexil_renderer* renderer,
  struct cexil_size* size
) {
  renderer->size.width = size->width;
  renderer->size.height = size->height;

  renderer->pixels = malloc(
    sizeof(unsigned char*) *
      renderer->size.height
  );

  for (
    unsigned int y = 0;
    y < renderer->size.height;
    ++y
  ) {
    renderer->pixels[y] = malloc(
      sizeof(unsigned char) *
        renderer->size.width
    );
  }
}

void cexil_renderer_render(
  struct cexil_renderer* renderer
) {
  // TODO: Clear on render should be an option
  // cexil_renderer_render_clear(renderer);
  cexil_renderer_render_sprites(renderer);

  char* buffer;
  unsigned int buffer_length = (
    (((renderer->size.width / 2) * 3) + 1) *
    (renderer->size.height / 4)
  ) + 1;
  buffer = malloc(
    sizeof(char) * buffer_length
  );
  buffer[buffer_length - 1] = '\0';

  unsigned int index = 0;

  for (
    unsigned int y = 0;
    y < renderer->size.height;
    y = y + 4
  ) {
    for (
      unsigned int x = 0;
      x < renderer->size.width;
      x = x + 2
    ) {
      unsigned char pixel_mapping_index = 0;

      if (renderer->pixels[y][x]) {
        pixel_mapping_index = (
          pixel_mapping_index +
          0b00000001
        );
      }

      if (renderer->pixels[y + 1][x]) {
        pixel_mapping_index = (
          pixel_mapping_index +
          0b00000010
        );
      }

      if (renderer->pixels[y + 2][x]) {
        pixel_mapping_index = (
          pixel_mapping_index +
          0b00000100
        );
      }

      if (renderer->pixels[y + 3][x]) {
        pixel_mapping_index = (
          pixel_mapping_index +
          0b01000000
        );
      }

      if (renderer->pixels[y][x + 1]) {
        pixel_mapping_index = (
          pixel_mapping_index +
          0b00001000
        );
      }

      if (renderer->pixels[y + 1][x + 1]) {
        pixel_mapping_index = (
          pixel_mapping_index +
          0b00010000
        );
      }

      if (renderer->pixels[y + 2][x + 1]) {
        pixel_mapping_index = (
          pixel_mapping_index +
          0b00100000
        );
      }

      if (renderer->pixels[y + 3][x + 1]) {
        pixel_mapping_index = (
          pixel_mapping_index +
          0b10000000
        );
      }

      buffer[index] = (
        cexil_pixel_mapping[
          pixel_mapping_index
        ][0]
      );
      buffer[index + 1] = (
        cexil_pixel_mapping[
          pixel_mapping_index
        ][1]
      );
      buffer[index + 2] = (
        cexil_pixel_mapping[
          pixel_mapping_index
        ][2]
      );

      index = index + 3;
    }

    buffer[index] = '\n';
    index = index + 1;
  }

  printf("\e[H\e[2J\e[3J%s", buffer);
  free(buffer);
}

void cexil_renderer_render_clear(
  struct cexil_renderer* renderer
) {
  for (
    unsigned int y = 0;
    y < renderer->size.height;
    ++y
  ) {
    for (
      unsigned int x = 0;
      x < renderer->size.width;
      ++x
    ) {
      renderer->pixels[y][x] = 0;
    }
  }
}

void cexil_renderer_render_sprites(
  struct cexil_renderer* renderer
) {
  for (
    unsigned int i = 0;
    i < renderer->sprites_length;
    ++i
  ) {
    cexil_renderer_sprite_render(
      renderer,
      renderer->sprites[i]
    );
  }
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

void cexil_renderer_sprite_render(
  struct cexil_renderer* renderer,
  struct cexil_sprite* sprite
) {
  for (
    unsigned int y = 0;
    y < sprite->size.height;
    ++y
  ) {
    unsigned int y_index = sprite->position.y + y;

    for (
      unsigned int x = 0;
      x < sprite->size.width;
      ++x
    ) {
      unsigned int x_index = (
        sprite->position.x + x
      );

      renderer->pixels[y_index][x_index] = (
        sprite->pixels[y][x]
      );
    }
  }
}

void cexil_renderer_destroy(
  struct cexil_renderer* renderer
) {
  for (
    unsigned int y = 0;
    y < renderer->size.height;
    ++y
  ) {
    free(renderer->pixels[y]);
  }
  free(renderer->pixels);
  free(renderer->sprites);
}

