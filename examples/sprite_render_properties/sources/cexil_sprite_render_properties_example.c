#include "cexil_sprite_render_properties_example.h"

#include <signal.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <time.h>

#include <stdio.h>

#include "cexil.h"

unsigned char interupted = 0;

int main() {
  srand(time((void*)0));
  
  struct cexil_renderer renderer;
  struct cexil_size size_terminal;
  cexil_size_set_to_terminal(&size_terminal);

  cexil_renderer_initialize(
    &renderer,
    &size_terminal
  );

  struct cexil_sprite background;
  struct cexil_size size_background = {
    width: renderer.size.width * 10,
    height: renderer.size.height
  };

  cexil_sprite_initialize(
    &background,
    &size_background
  );

  for (
    unsigned int x = 0;
    x < background.size.width;
    ++x
  ) {
    background.pixels[0][x] = 1;
    background.pixels[1][x] = 1;
    background.pixels[
      background.size.height - 1
    ][x] = 1;
    background.pixels[
      background.size.height - 2
    ][x] = 1;

    unsigned char stag_height_upper = rand() % 10;
    unsigned char stag_height_lower = rand() % 10;

    for (
      unsigned char y = 0;
      y < stag_height_upper;
      ++y
    ) {
      background.pixels[y + 2][x] = 1;
    }

    for (
      unsigned char y = (
        background.render_size.height -
        stag_height_lower -
        1
      );
      y < background.render_size.height - 1;
      ++y) {
        background.pixels[y][x] = 1;
      }
  }

  cexil_sprite_render_size_set(
    &background,
    &renderer.size
  );

  cexil_renderer_sprite_add(
    &renderer,
    &background
  );

  struct cexil_time time_frame;
  cexil_time_initialize(&time_frame, 0, 25000);

  struct cexil_timer timer_scroll;
  cexil_timer_start(&timer_scroll);

  unsigned long long int speed_scroll = 5000;

  do {
    if (
      cexil_timer_time_elapsed(&timer_scroll) >=
      speed_scroll
    ) {
      background.render_offset.x = (
        background.render_offset.x + 1
      );

      if (
        background.render_offset.x +
        background.render_size.width >=
        background.size.width
      ) {
       background.render_offset.x = 0;
      }

      cexil_timer_start(&timer_scroll);
    }
    cexil_renderer_render_clear(&renderer);
    cexil_renderer_render(&renderer);

    cexil_time_sleep(&time_frame);
  } while (interupted == 0);
  
  cexil_renderer_destroy(&renderer);
 
  return 0;
}

void interupt_handler(int _) {
  interupted = 1;
}

