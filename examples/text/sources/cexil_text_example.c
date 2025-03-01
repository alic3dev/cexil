#include "cexil_text_example.h"

#include <signal.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <time.h>

#include <stdio.h>

#include "cexil.h"

unsigned char interupted = 0;

char string_wrap_on[8] = "wrap on\0";
char string_wrap_off[9] = "wrap off\0";

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

  struct cexil_text text_wrap;
  cexil_text_initialize(
    &text_wrap,
    text_wrap.wrap == 1 ? string_wrap_on : string_wrap_off
  );

  text_wrap.position.y = renderer.size.height - text_wrap.font->size.height;

  cexil_renderer_text_add(
    &renderer,
    &text_wrap
  );

  struct cexil_time time_frame;
  cexil_time_initialize(&time_frame, 0, 25000000);

  struct cexil_timer timer_wrap;
  cexil_timer_start(&timer_wrap); 
 
  while (interupted == 0) {
    cexil_time_sleep(&time_frame);

    if (
      cexil_timer_time_elapsed(&timer_wrap) > 2000000
    ) {
      cexil_timer_start(&timer_wrap);
      
      text_long.wrap = text_long.wrap == 0 ? 1 : 0;
      cexil_text_text_set(
        &text_wrap,
        text_long.wrap == 0 ? string_wrap_off : string_wrap_on
      );
    }

    cexil_renderer_render_clear(&renderer);
    cexil_renderer_render(&renderer);
  }
  
  cexil_renderer_destroy(&renderer);
 
  return 0;
}

void interupt_handler(int _) {
  interupted = 1;
}

