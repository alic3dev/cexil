#include "cexil_renderer_example.h"

#include <time.h>

#include "cexil.h"

int main() {
  struct cexil_renderer renderer;
  struct cexil_size size = {
    width: 36,
    height: 36
  };

  cexil_renderer_initialize(
    &renderer, 
    &size
  );

  struct cexil_position position = {
    x: 0,
    y: 0
  };
  struct cexil_position direction = {
    x: 1,
    y: 0
  };

  int distance = (
    size.width < size.height
      ? size.width
      : size.height
  );

  renderer.pixels[0][0] = 1;

  struct timespec frame_time = { 0, 1000000 };

  do {
    for (int i = 0; i < distance - 1; ++i) {
      position.x = position.x + direction.x;
      position.y = position.y + direction.y;

      renderer.pixels[
        position.y
      ][
        position.x
      ] = 1;
      
      nanosleep(&frame_time, NULL);

      cexil_renderer_render(&renderer);
    }

    if (direction.x == 1) {
      direction.x = 0;
      direction.y = 1;
    } else if (direction.y == 1) {
      direction.x = -1;
      direction.y = 0;

      distance = distance - 2;
    } else if (direction.x == -1) {
      direction.x = 0;
      direction.y = -1;
    } else {
      direction.x = 1;
      direction.y = 0;
      
      distance = distance - 2;
    }
  } while (distance > 0);

  cexil_renderer_destroy(&renderer);
 
  return 0;
}

