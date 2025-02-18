#include "cexil_font_transpiler_intermediary.h"

#include <stdlib.h>

void cexil_font_transpiler_intermediary_initialize(
  struct cexil_font_transpiler_intermediary* intermediary
) {
  intermediary->character_set = malloc(0);
  intermediary->characters = malloc(0);
  intermediary->characters_count = 0;
  intermediary->size_width = 0;
  intermediary->size_height = 0;
  intermediary->error = (void*)0;
}

void cexil_font_transpiler_intermediary_destroy(
  struct cexil_font_transpiler_intermediary* intermediary
) {
  free(intermediary->character_set);

  for (
    unsigned int index_character;
    index_character < 
    intermediary->characters_count;
    ++index_character
  ) {
    for (
      unsigned int index_y = 0;
      index_y < intermediary->size_height;
      ++index_y
    ) {
      free(
        intermediary->characters[
          index_character
        ][index_y]
      );
    }

    free(
      intermediary->characters[index_character]
    );
  }

  free(intermediary->characters);

  if (intermediary->error != (void*)0) {
    free(intermediary->error->message);
    free(intermediary->error);
  }
}

