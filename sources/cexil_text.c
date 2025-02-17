#include "cexil_text.h"

#include <stdlib.h>

void cexil_text_initialize(
  struct cexil_text* cexil_text,
  char* text
) {
  cexil_text->position.x = 0;
  cexil_text->position.y = 0;
  cexil_text->size.height = 1;
  cexil_text->size.width = 1;

  cexil_text->wrap = 0;

  unsigned int length = 0;

  while (text[length] != '\0') {
    length = length + 1;
  }
  length = length + 1;

  cexil_text->text = malloc(
    sizeof(char) * length
  );

  for (
    unsigned int character_index = 0;
    character_index < length;
    ++character_index
  ) {
    cexil_text->text[character_index] = (
      text[character_index]
    );
  }
}

void cexil_text_destroy(
  struct cexil_text* text
) {
  free(text->text);
}

