# progress3D.inc

A SA-MP library for creating progress bars in 3D space. This library was written and is maintained by Manyula.

![progress3D by Manyula](https://www2.pic-upload.de/thumb/35895015/progress3D.png "progress3D by Manyula")

## Installation

Simply install to your project:

```bash
sampctl package install TheManyula/progress3D
```

Include in your code and begin using the library:

```pawn
#include <progress3D>
```

## Usage

### Constants

| Constant             | Description                                                                                             |
| :------------------- | :------------------------------------------------------------------------------------------------------ |
| MAX_3D_BARS          | Total amount of 3D progress bars that can be created. Defaults to the 3D text label limit divided by 2. |
| INVALID_3D_BAR       | Return value for an invalid or non-existent 3D progress bar.                                            |
| BAR_3D_LAYOUT_THIN   | Layout option for a thin 3D progress bar.                                                               |
| BAR_3D_LAYOUT_NORMAL | Layout option for a standard (medium thickness) 3D progress bar.                                        |
| BAR_3D_LAYOUT_THICK  | Layout option for a thick 3D progress bar.                                                              |

### Functions

```pawn
Bar3D:CreateProgressBar3D(color, layout, Float:x, Float:y, Float:z, Float:max_value, Float:init_value, Float:drawdistance, attachedplayer = INVALID_PLAYER_ID, attachedvehicle = INVALID_VEHICLE_ID, testlos = 0, worldid = -1, interiorid = -1, playerid = -1, Float:streamdistance = STREAMER_3D_TEXT_LABEL_SD, areaid = -1, priority = 0)
```

Creates a 3D progress bar. Returns `INVALID_3D_BAR` if bar already exists.

```pawn
HideProgressBar3D(Bar3D:barid)
```

Hides the specified 3D progress bar.

```pawn
ShowProgressBar3D(Bar3D:barid)
```

Shows the specified 3D progress bar.

```pawn
DestroyProgressBar3D(Bar3D:barid)
```

Destroys a 3D progress bar. Returns `INVALID_3D_BAR` if bar doesn't exist.

```pawn
GetProgressBar3DValue(Bar3D:barid)
```

Returns the current progress value.

```pawn
SetProgressBar3DValue(Bar3D:barid, Float:value)
```

Updates the value of the specified 3D progress bar. Returns 0 if value is greater than max value.

```pawn
GetProgressBar3DColor(Bar3D:barid)
```

Returns the color of the specified 3D progress bar.

```pawn
SetProgressBar3DColor(Bar3D:barid, color)
```

Updates the color of the specified 3D progress bar.

```pawn
GetProgressBar3DMaxValue(Bar3D:barid)
```

Returns the maximum value of the specified 3D progress bar.

```pawn
SetProgressBar3DMaxValue(Bar3D:barid, Float:max_value)
```

Updates the maximum value of the specified 3D progress bar. Returns 0 if the max value is smaller than the current value.

```pawn
GetProgressBar3DLayout(Bar3D:barid)
```

Returns the layout of the specified 3D progress bar.

```pawn
SetProgressBar3DLayout(Bar3D:barid, layout)
```

Updates the layout of the specified 3D progress bar. Returns 0 for an invalid layout.

```pawn
IsValidProgressBar3D(Bar3D:barid)
```

Returns 1, if the specified 3D progress bar ID is valid and exists.

### Internal

```pawn
_UpdateProgress3D(barid, color, layout, Float:max_value, Float:value)
```

Updates the properties of a 3D progress bar. Called on creation, deletion or whenever the layout, progress value, maximum value or color are updated.

## Testing

To test, simply run the package using

```bash
sampctl package run
```

and connect to your localhost (`localhost:7777` or `127.0.0.1:7777`).

### Commands

* `/bar` to create a 3D progress bar.
* `/layout` to change the layout.
* `/value <float>` to change the value.
* `/max <float>` to change the maximum value.
* `/color` to change the color randomly.
