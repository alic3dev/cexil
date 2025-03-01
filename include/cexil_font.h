#ifndef __CEXIL_FONT_H
#define __CEXIL_FONT_H

#include "cexil_character_set.h"
#include "cexil_size.h"

struct cexil_font {
  enum cexil_character_set character_set;
  const char* characters;
  struct cexil_size size;
  unsigned int size_total;
};

signed int cexil_font_character_index_get(
  const struct cexil_font*,
  char
);

#endif

