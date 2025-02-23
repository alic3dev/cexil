#ifndef __CEXIL_TEXT_H
#define __CEXIL_TEXT_H

#include "cexil_font.h"
#include "cexil_position.h"
#include "cexil_size.h"

struct cexil_text {
  char* text;
  const struct cexil_font* font;
  unsigned char wrap;
  struct cexil_position position;
  struct cexil_size size;
};

void cexil_text_initialize(
  struct cexil_text*,
  char*
);

void cexil_text_destroy(
  struct cexil_text*
);

#endif

