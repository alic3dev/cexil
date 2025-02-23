#ifndef __CEXIL_FONT_H
#define __CEXIL_FONT_H

#include "cexil_character_set.h"
#include "cexil_size.h"

struct cexil_font {
  enum cexil_character_set character_set;
  char* characters;
  struct cexil_size size;
};

#endif

