# cexil

A terminal based 2D pixel graphics system library.

## standards

### coordinates

cexil uses an `[y][x]` coordinate system for efficiency.

This is inverse the standard `[x][y]` coordinates of standard systems.

#### example

To select a pixel at a position of `x: 4` and `y: 6` you would lookup the position as follows

```c
renderer->pixels[6][4]
```

## building

```sh
make
```

