#include "cexil_font.h"

signed int cexil_font_character_index_get(
  const struct cexil_font* font,
  char character
) {
  signed int character_set_index = cexil_character_set_index_get(
    font->character_set,
    character
  );

  if (character_set_index < 0) {
    return character_set_index;
  }

  return character_set_index * font->size_total;
}

