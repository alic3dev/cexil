#ifndef __CEXIL_FONT_H
#define __CEXIL_FONT_H

#include "cexil_size.h"

#define CEXIL_FONT_SIZE_WIDTH_DEFAULT 6
#define CEXIL_FONT_SIZE_HEIGHT_DEFAULT 4

struct cexil_font {
  enum cexil_character_set character_set;
  char*** characters;
  struct cexil_size size;
};

#endif

