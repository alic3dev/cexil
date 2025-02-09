#include "cexil_size.h"

#include <sys/ioctl.h>

unsigned char cexil_size_set_to_terminal(
  struct cexil_size* size
) {
  struct winsize terminal_size;

  if (
    ioctl(0, TIOCGWINSZ, &terminal_size) == -1
  ) {
    return 1;
  }

  size->width = (terminal_size.ws_col - 1) * 2;
  size->height = (terminal_size.ws_row - 1) * 4;

  return 0;
}

