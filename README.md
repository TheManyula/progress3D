# progress3D.inc

A SA-MP library for creating progress bars in 3D space. This library was written and is maintained by Manyula.

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

| Constant             | Description                                                                                              |
| :------------------- | :------------------------------------------------------------------------------------------------------- |
| MAX_3D_BARS          | Total amount of 3D progress bars that can be created.\nDefaults to the 3D text label limit divided by 2. |
| INVALID_3D_BAR       | Return value for an invalid or non-existent 3D progress bar.                                             |
| BAR_3D_LAYOUT_THIN   | Layout option for a thin 3D progress bar.                                                                |
| BAR_3D_LAYOUT_NORMAL | Layout option for a standard (medium thickness) 3D progress bar.                                         |
| BAR_3D_LAYOUT_THICK  | Layout option for a thick 3D progress bar.                                                               |

### Functions

```pawn
Bar3D:CreateProgressBar3D(Float:x, Float:y, Float:z, layout, fill_color, background_color, Float:max_value, Float:init_value, Float:drawdistance, attachedplayer = INVALID_PLAYER_ID, attachedvehicle = INVALID_VEHICLE_ID, testlos = 0, worldid = -1, interiorid = -1, playerid = -1, Float:streamdistance = STREAMER_3D_TEXT_LABEL_SD, areaid = -1, priority = 0)
```

Creates a 3D progress bar.

```pawn
DestroyProgressBar3D(Bar3D:barid)
```

Destroys a 3D progress bar.

```pawn
GetProgressBar3DValue(Bar3D:barid)
```

Returns the current progress value.

```pawn
SetProgressBar3DValue(Bar3D:barid, Float:value)
```

Updates the value of the specified 3D progress bar.

```pawn
GetProgressBar3DFillColor(Bar3D:barid)
```

Returns the fill color of the specified 3D progress bar.

```pawn
SetProgressBar3DFillColor(Bar3D:barid, fill_color)
```

Updates the fill color of the specified 3D progress bar.

```pawn
GetProgressBar3DBackgroundColor(Bar3D:barid)
```

Returns the background color of the specified 3D progress bar.

```pawn
SetProgressBar3DBackgroundColor(Bar3D:barid, background_color)
```

Updates the background color of the specified 3D progress bar.

```pawnGetProgressBar3DMaxValue(Bar3D:barid)
```

Returns the maximum value of the specified 3D progress bar.

```pawn
SetProgressBar3DMaxValue(Bar3D:barid, Float:max_value)
```

Updates the maximum value of the specified 3D progress bar.

```pawn
GetProgressBar3DLayout(Bar3D:barid)
```

Returns the layout of the specified 3D progress bar.

```pawn
SetProgressBar3DLayout(Bar3D:barid, layout)
```

Updates the layout of the specified 3D progress bar.

```pawn
IsValidProgressBar3D(Bar3D:barid)
```

Returns true, if the specified 3D progress bar ID is valid and exists.

### Internal

```pawn
_UpdateProgress3D(barid, layout, fill_color, background_color, Float:max_value, Float:value)
```

Updates the properties of a 3D progress bar. Called on creation, deletion or whenever the layout, progress value, maximum value, fill color or background color are updated.

## Testing

To test, simply run the package using

```bash
sampctl package run
```

and connect to your localhost (`localhost:7777` or `127.0.0.1:7777`).

### Commands

* `/bar` to create a 3D progress bar.
* `/l` to change the layout.
* `/v <number>` to change the value.
* `/max <number>` to change the maximum value.
* `/fill` to change the fill color randomly.
* `/bg` to change the background color randomly.
