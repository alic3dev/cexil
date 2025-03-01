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

  renderer->texts_length = 0;
  renderer->texts = malloc(
    sizeof(struct cexil_text*) *
    renderer->texts_length
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
  cexil_renderer_render_texts(renderer);

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
    unsigned int sprite_index = 0;
    sprite_index < renderer->sprites_length;
    ++sprite_index
  ) {
    cexil_renderer_sprite_render(
      renderer,
      renderer->sprites[sprite_index]
    );
  }
}

void cexil_renderer_render_texts(
  struct cexil_renderer* renderer
) {
  for (
    unsigned int text_index = 0;
    text_index < renderer->texts_length;
    ++text_index
  ) {
    cexil_renderer_text_render(
      renderer,
      renderer->texts[text_index]
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
    y < sprite->render_size.height;
    ++y
  ) {
    unsigned int y_index = sprite->position.y + y;
    
    if (y_index >= renderer->size.height) {
      break;
    }

    unsigned int y_index_sprite = (
      (sprite->render_offset.y + y)
      % sprite->size.height
    );

    for (
      unsigned int x = 0;
      x < sprite->render_size.width;
      ++x
    ) {
      unsigned int x_index = (
        sprite->position.x + x
      );

      if (x_index >= renderer->size.width) {
        break;
      }

      renderer->pixels[y_index][x_index] = (
        renderer->pixels[y_index][x_index] +
        sprite->pixels[y_index_sprite][
          (x + sprite->render_offset.x)
          % sprite->size.width
        ]
      );
    }
  }
}

void cexil_renderer_text_add(
  struct cexil_renderer* renderer,
  struct cexil_text* text
) {
  renderer->texts_length = renderer->texts_length + 1;
  renderer->texts = realloc(
    renderer->texts,
    sizeof(struct cexil_text*) * renderer->texts_length
  );

  renderer->texts[renderer->texts_length - 1] = text;
}

void cexil_renderer_text_render(
  struct cexil_renderer* renderer,
  struct cexil_text* text
) {
  struct cexil_position offset;
  offset.x = 0;
  offset.y = 0;
  
  struct cexil_position position_pixels;
  position_pixels.x = 0;
  position_pixels.y = 0;

  unsigned int character_y_offset = 0;
  
  for (
    unsigned int text_index = 0;
    text->text[text_index] != '\0';
    ++text_index
  ) {
    signed int character_index = cexil_font_character_index_get(
      text->font,
      text->text[text_index]
    ); 
    
    if (character_index < 0) {
      offset.x = offset.x + text->font->size.width;
      continue;
    }
    
    if (text->position.x + text->font->size.width + offset.x >= renderer->size.width) {
      offset.x = 0;
      offset.y = offset.y + text->font->size.height;
    }

    for (
      unsigned int y_index = 0;
      y_index < text->font->size.height;
      ++y_index
    ) {
      position_pixels.y = text->position.y + y_index + offset.y;
      character_y_offset = y_index * text->font->size.width;

      if (position_pixels.y >= renderer->size.height) {
        break;
      }
      
      for (
        unsigned int x_index = 0;
        x_index < text->font->size.width;
        ++x_index
      ) {
        position_pixels.x = text->position.x + x_index + offset.x;
  
        if (position_pixels.x >= renderer->size.width) {
          break;
        }

        renderer->pixels[position_pixels.y][position_pixels.x] = (
          renderer->pixels[position_pixels.y][position_pixels.x] + 
          text->font->characters[character_index + character_y_offset + x_index]
        );
      }
    }

    offset.x = offset.x + text->font->size.width;
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
  
  for (
    unsigned int i = 0;
    i < renderer->sprites_length;
    ++i
  ) {
    cexil_sprite_destroy(renderer->sprites[i]);
  }
  free(renderer->sprites);

  for (
    unsigned int text_index = 0;
    text_index < renderer->texts_length;
    ++text_index
  ) {
    cexil_text_destroy(renderer->texts[text_index]);
  }

  free(renderer->texts);
}

