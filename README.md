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

```sh
make
```

### clean

```sh
make clean
```

### examples

Each example under the `./examples` directory has an individual make file which will build the output into its corresponding `./bin` directory.

You can also build all examples in one shot in the root directory with

```sh
make examples
```

or you can run the following within the `./examples` directory

```sh
make
```

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
