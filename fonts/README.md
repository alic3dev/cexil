# fonts

A collection of fonts designed to be used by/in cexil.

## *.cexil_font format

`cexil` uses the `.cexil_font` format for fonts before they get transpiled down into `c` code which is then included as an object during the build process.

### parameters

Parameters must come first in the `.cexil_font` file.
They are seperated by a single `\n` character.
To mark the end of parameter declarations then simply add an extra `\n` after the last parameter.

#### character_set

This parameter is required.
It's value should be a value defined by `enum cexil_character_set`.

```
character_set:SOME_CHARACTER_SET
```

#### size_width

This parameter is optional. It's default value will be `CEXIL_FONT_SIZE_WIDTH_DEFAULT`.
Otherwise any number.

```
size_width:6
```

#### size_height

This parameter is optional. It's default value will be `CEXIL_FONT_SIZE_HEIGHT_DEFAULT`.
Otherwise any number.

```
size_height: 4
```

### characters

Characters are defined after all of the parameters have been defined (marked by two `\n` in succession).
There can be a variable number of characters but it's recommended that you match the count of characters for whichever `character_set` you're using.

## building

Building the fonts into a format that can be used during development of/with `cexil` requires you to run the `cexil_font_transpiler` (see the corresponding directory within this one for more information).

