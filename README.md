# cexil

A terminal based 2D pixel graphics system library.

## standards

### coordinates

cexil uses an `[y][x]` coordinate system for efficiency.

This is inverse the standard `[x][y]` coordinates of typical systems.

#### example

To select a pixel at a position of `x: 4` and `y: 6` you would lookup the position as follows

```c
renderer->pixels[6][4]
```

## building

### library

You can build the library on its own with the following

```sh
make
```

### cleaning

To clean up all the object files and resulting library file you can use

```sh
make clean
```

### examples

You can build all of the examples in one shot using

```sh
make examples
```

See [examples/README.md](/examples/README.md) for more details.

### all

To build the library + examples

```sh
make all
```

To clean the library + examples

```sh
make clean_all
```

> ©️ Copyright "alic3dev (2025)" - All rights reserved
