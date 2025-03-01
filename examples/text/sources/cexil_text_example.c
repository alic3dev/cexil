#include "cexil_text_example.h"

#include <signal.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <time.h>

#include <stdio.h>

#include "cexil.h"

unsigned char interupted = 0;

int main() {
  struct sigaction signal_action;
  signal_action.sa_handler = interupt_handler;
  sigaction(SIGINT, &signal_action, NULL);
  
  struct winsize terminal_size;

  srand(time(NULL));

  if (
    ioctl(0, TIOCGWINSZ, &terminal_size) == -1
  ) {
    return 1;
  }

  struct cexil_renderer renderer;
  struct cexil_size size = {
    width: (terminal_size.ws_col - 1) * 2,
    height: (terminal_size.ws_row - 1) * 4
  };

  cexil_renderer_initialize(
    &renderer,
    &size
  );

  struct cexil_text text;
  cexil_text_initialize(
    &text,
    "abcdefghijklmnopqrstuvwxyz"
  );

  cexil_renderer_text_add(
    &renderer,
    &text
  );

  struct cexil_text text_long;
  cexil_text_initialize(
    &text_long,
    "this is a long line of text that can either be truncated or set to wrap around the screen"
  );

  text_long.position.y = text_long.font->size.height * 2;

  cexil_renderer_text_add(
    &renderer,
    &text_long
  );

  struct timespec frame_time = { 0, 25000000 };
  
  while (interupted == 0) {
    nanosleep(&frame_time, NULL);

    cexil_renderer_render_clear(&renderer);
    cexil_renderer_render(&renderer);
  }
  
  cexil_renderer_destroy(&renderer);
 
  return 0;
}

void interupt_handler(int _) {
  interupted = 1;
}

