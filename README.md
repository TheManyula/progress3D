# progress3D.inc

[![sampctl](https://shields.southcla.ws/badge/sampctl-progress3D-2f2f2f.svg?style=for-the-badge)](https://github.com/TheManyula/progress3D)

A SA-MP library for creating progress bars in 3D space.
This library was written and is maintained by Manyula.

![3D progress bar](https://www2.pic-upload.de/thumb/35895015/progress3D.png)

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

* `MAX_3D_BARS`
  * Defaults to the 3D text label limit divided by 2.
* `INVALID_3D_BAR`
  * Return value for an invalid or non-existent 3D progress bar.
* `BAR_3D_LAYOUT_THIN`
  * Thin progress bar.
* `BAR_3D_LAYOUT_NORMAL`
  * Standard thickness progress bar.
* `BAR_3D_LAYOUT_THICK`
  * Slightly thicker progress bar.

### Functions

* `Bar3D:CreateProgressBar3D(Float:x, Float:y, Float:z, layout, fill_color, background_color, Float:max_value, Float:init_value, Float:drawdistance, attachedplayer = INVALID_PLAYER_ID, attachedvehicle = INVALID_VEHICLE_ID, testlos = 0, worldid = -1, interiorid = -1, playerid = -1, Float:streamdistance = STREAMER_3D_TEXT_LABEL_SD, areaid = -1, priority = 0)`
  * Creates a 3D progress bar.
* `DestroyProgressBar3D(Bar3D:barid)`
  * Destroys a 3D progress bar.
* `GetProgressBar3DValue(Bar3D:barid)`
  * Returns the current progress value.
* `SetProgressBar3DValue(Bar3D:barid, Float:value)`
  * Updates the value of the specified 3D progress bar.
* `GetProgressBar3DFillColor(Bar3D:barid)`
  * Returns the fill color of the specified 3D progress bar.
* `SetProgressBar3DFillColor(Bar3D:barid, fill_color)`
  * Updates the fill color of the specified 3D progress bar.
* `GetProgressBar3DBackgroundColor(Bar3D:barid)`
  * Returns the background color of the specified 3D progress bar.
* `SetProgressBar3DBackgroundColor(Bar3D:barid, background_color)`
  * Updates the background color of the specified 3D progress bar.
* `GetProgressBar3DMaxValue(Bar3D:barid)`
  * Returns the maximum value of the specified 3D progress bar.
* `SetProgressBar3DMaxValue(Bar3D:barid, Float:max_value)`
  * Updates the maximum value of the specified 3D progress bar.
* `GetProgressBar3DLayout(Bar3D:barid)`
  * Returns the layout of the specified 3D progress bar.
* `SetProgressBar3DLayout(Bar3D:barid, layout)`
  * Updates the layout of the specified 3D progress bar.
* `IsValidProgressBar3D(Bar3D:barid)`
  * Returns true, if the specified 3D progress bar ID is valid and exists.

### Internal

* `_UpdateProgress3D(barid, layout, fill_color, background_color, Float:max_value, Float:value)`
  * Updates the properties of a 3D progress bar. Called on creation, deletion or whenever the layout, progress value, maximum value, fill color or background color are updated.

## Testing

To test, simply run the package using

```bash
sampctl package run
```

and connect to your localhost (`localhost:7777` or `127.0.0.1:7777`).

### Commands
* `/bar` to create a 3D progress bar.
* `/layout` to change the layout.
* `/value <number>` to change the value.
* `/max <number>` to change the maximum value. 
* `/fill` to change the fill color randomly.
* `/background` to change the background color randomly. 
