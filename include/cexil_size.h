#ifndef __CEXIL_SIZE_H
#define __CEXIL_SIZE_H

struct cexil_size {
  unsigned int width;
  unsigned int height;
};

unsigned char cexil_size_set_to_terminal(
  struct cexil_size*
);

#endif

