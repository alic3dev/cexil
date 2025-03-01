#include "cexil_character_set.h"

signed int cexil_character_set_index_get(
  enum cexil_character_set character_set,
  char character
) {
  switch (character_set) {
    case ascii:
      break;
    case lower:
      if (character >= 'a' && character <= 'z') {
        return character - 'a';
      }
      break;
    default:
      break;
  }

  return -1;
}

