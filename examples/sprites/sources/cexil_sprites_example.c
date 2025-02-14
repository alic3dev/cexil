#include "cexil_sprites_example.h"

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

  struct cexil_sprite* sprites;
  unsigned char sprites_length = 2;
  sprites = malloc(
    sizeof(struct cexil_sprite) *
    sprites_length
  );

  for (
    unsigned char i = 0; i < sprites_length; ++i
  ) {
    struct cexil_size sprite_size = {
      width: 6,
      height: 8
    };

    cexil_sprite_initialize(
      &sprites[i],
      &sprite_size
    );

    sprites[i].position.x = (
      i % 2 == 0
      ? 0
      : (
        renderer.size.width - 
        sprites[i].size.width * 2 - 2
      )
    );

    sprites[i].position.y = (
      (renderer.size.height / 2) -
      (sprites[i].size.height / 2) +
      (i % 2 == 0 ? 0 : 1)
    );

    sprites[i].pixels[0][2] = 1;
    sprites[i].pixels[0][3] = 1;
    sprites[i].pixels[1][1] = 1;
    sprites[i].pixels[1][2] = 1;
    sprites[i].pixels[1][3] = 1;
    sprites[i].pixels[1][4] = 1;
    sprites[i].pixels[2][0] = 1;
    sprites[i].pixels[2][1] = 1;
    sprites[i].pixels[2][2] = 1;
    sprites[i].pixels[2][3] = 1;
    sprites[i].pixels[2][4] = 1;
    sprites[i].pixels[2][5] = 1;

    sprites[i].pixels[3][0] = 1;
    sprites[i].pixels[3][2] = 1;
    sprites[i].pixels[3][3] = 1;
    sprites[i].pixels[3][5] = 1;
    sprites[i].pixels[4][0] = 1;
    sprites[i].pixels[4][2] = 1;
    sprites[i].pixels[4][3] = 1;
    sprites[i].pixels[4][5] = 1;

    sprites[i].pixels[5][0] = 1;
    sprites[i].pixels[5][1] = 1;
    sprites[i].pixels[5][2] = 1;
    sprites[i].pixels[5][3] = 1;
    sprites[i].pixels[5][4] = 1;
    sprites[i].pixels[5][5] = 1;
    sprites[i].pixels[6][0] = 1;
    sprites[i].pixels[6][1] = 1;
    sprites[i].pixels[6][2] = 1;
    sprites[i].pixels[6][3] = 1;
    sprites[i].pixels[6][4] = 1;
    sprites[i].pixels[6][5] = 1;
    sprites[i].pixels[7][1] = 1;
    sprites[i].pixels[7][2] = 1;
    sprites[i].pixels[7][4] = 1;
    sprites[i].pixels[7][5] = 1;
    
    cexil_renderer_sprite_add(
      &renderer,
      &sprites[i]
    );
  }

  struct timespec frame_time = { 0, 25000000 };
  
  for (long int _ = 0; _ < 10000000000; ++_) {
    for (
      unsigned int i = 0;
      i < sprites_length;
      ++i
    ) {
      sprites[i].position.x = (
        sprites[i].position.x +
        ((rand() % 3) - 1)
      );

      if (sprites[i].position.x < 0) {
        sprites[i].position.x = 0;
      } else if (
        sprites[i].position.x >
        renderer.size.width - 
        sprites[i].size.width
      ) {
        sprites[i].position.x = (
          renderer.size.width -
          sprites[i].size.width
        );
      }

      sprites[i].position.y = (
        sprites[i].position.y +
        ((rand() % 3) - 1)
      );
      
      if (sprites[i].position.y < 0) {
        sprites[i].position.y = 0;
      } else if (
        sprites[i].position.y >
        renderer.size.height - 
        sprites[i].size.height
      ) {
        sprites[i].position.y = (
          renderer.size.height -
          sprites[i].size.height
        );
      }
    }
    nanosleep(&frame_time, NULL);

    cexil_renderer_render_clear(&renderer);
    cexil_renderer_render(&renderer);

    if (interupted == 1) {
      break;
    }
  }
  
  cexil_renderer_destroy(&renderer);
 
  return 0;
}

void interupt_handler(int _) {
  interupted = 1;
}

