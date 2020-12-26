# progress3D.inc

A SA-MP library for creating progress bars in 3D space. This library was written and is maintained by Manyula.

![progress3D](https://i.ibb.co/gVby8wg/progress3-D.png)

## Installation

Simply install to your project:

```bash
sampctl package install TheManyula/progress3D:v2.3.2
```

Include in your code and begin using the library:

```pawn
#include <progress3D>
```

## Usage

### Constants

| Constant              | Description                                                                                                                       |
| :-------------------- | :-------------------------------------------------------------------------------------------------------------------------------- |
| MAX_GLOBAL_3D_BARS    | Total amount of global 3D progress bars that can be created.</br>Defaults to the 3D text label limit (currently 1024).            |
| MAX_PLAYER_3D_BARS    | Total amount of player 3D progress bars that can be created.</br>Defaults to the per-player 3D text label limit (currently 1024). |
| INVALID_GLOBAL_3D_BAR | Return value for an invalid or non-existent global 3D progress bar.                                                               |
| INVALID_PLAYER_3D_BAR | Return value for an invalid or non-existent player 3D progress bar.                                                               |

### Limits

Although progress3D requires the use of the streamer and therefore allows you to stretch the current limits, you should keep in mind that the hard limit for 3D progress bars is much lower than the current 3D text label limit. Here is what you need to take into account when creating them:

* 3D progress bars **without** border consist of two 3D text labels for the bar itself.
* 3D progress bars **with** borders consist of two 3D text labels for the bar itself **AND** two additional 3D text labels for the background bar.

### Functions

```pawn
Bar3D:CreateProgressBar3D(color, bool:borders, Float:x, Float:y, Float:z, Float:max_value, Float:init_value, Float:drawdistance, attachedplayer = INVALID_PLAYER_ID, attachedvehicle = INVALID_VEHICLE_ID, testlos = 0, worldid = -1, interiorid = -1, Float:streamdistance = STREAMER_3D_TEXT_LABEL_SD, areaid = -1, priority = 0)
```

Creates a 3D progress bar. Returns `INVALID_GLOBAL_3D_BAR` if bar already exists.

```pawn
HideProgressBar3D(Bar3D:barid)
```

Hides the specified 3D progress bar. Returns `INVALID_GLOBAL_3D_BAR` if bar doesn't exist.

```pawn
ShowProgressBar3D(Bar3D:barid)
```

Shows the specified 3D progress bar. Returns `INVALID_GLOBAL_3D_BAR` if bar doesn't exist.

```pawn
DestroyProgressBar3D(Bar3D:barid)
```

Destroys a 3D progress bar. Returns `INVALID_GLOBAL_3D_BAR` if bar doesn't exist.

```pawn
Float:GetProgressBar3DValue(Bar3D:barid)
```

Returns the current progress value. Returns `INVALID_GLOBAL_3D_BAR` if bar doesn't exist.

```pawn
SetProgressBar3DValue(Bar3D:barid, Float:value)
```

Updates the value of the specified 3D progress bar. Returns 0 if value is greater than max value. Returns `INVALID_GLOBAL_3D_BAR` if bar doesn't exist.

```pawn
GetProgressBar3DColor(Bar3D:barid)
```

Returns the color of the specified 3D progress bar. Returns `INVALID_GLOBAL_3D_BAR` if bar doesn't exist.

```pawn
SetProgressBar3DColor(Bar3D:barid, color)
```

Updates the color of the specified 3D progress bar. Returns `INVALID_GLOBAL_3D_BAR` if bar doesn't exist.

```pawn
Float:GetProgressBar3DMaxValue(Bar3D:barid)
```

Returns the maximum value of the specified 3D progress bar. Returns `INVALID_GLOBAL_3D_BAR` if bar doesn't exist.

```pawn
SetProgressBar3DMaxValue(Bar3D:barid, Float:max_value)
```

Updates the maximum value of the specified 3D progress bar. Returns 0 if the max value is smaller than the current value. Returns `INVALID_GLOBAL_3D_BAR` if bar doesn't exist.

```pawn
IsValidProgressBar3D(Bar3D:barid)
```

Returns 1, if the specified 3D progress bar ID is valid and exists. Returns `INVALID_GLOBAL_3D_BAR` if bar doesn't exist.

___

```pawn
PlayerBar3D:CreatePlayerProgressBar3D(playerid, color, bool:borders, Float:x, Float:y, Float:z, Float:max_value, Float:init_value, Float:drawdistance, attachedplayer = INVALID_PLAYER_ID, attachedvehicle = INVALID_VEHICLE_ID, testlos = 0, worldid = -1, interiorid = -1, Float:streamdistance = STREAMER_3D_TEXT_LABEL_SD, areaid = -1, priority = 0)
```

Creates a player 3D progress bar. Returns `INVALID_PLAYER_3D_BAR` if bar already exists.

```pawn
HidePlayerProgressBar3D(playerid, PlayerBar3D:barid)
```

Hides the specified player 3D progress bar. Returns `INVALID_PLAYER_3D_BAR` if bar doesn't exist.

```pawn
ShowPlayerProgressBar3D(playerid, PlayerBar3D:barid)
```

Shows the specified player 3D progress bar. Returns `INVALID_PLAYER_3D_BAR` if bar doesn't exist.

```pawn
DestroyPlayerProgressBar3D(playerid, PlayerBar3D:barid)
```

Destroys a 3D player progress bar. Returns `INVALID_PLAYER_3D_BAR` if bar doesn't exist.

```pawn
Float:GetPlayerProgressBar3DValue(playerid, PlayerBar3D:barid)
```

Returns the current progress value. Returns `INVALID_PLAYER_3D_BAR` if bar doesn't exist.

```pawn
SetPlayerProgressBar3DValue(playerid, PlayerBar3D:barid, Float:value)
```

Updates the value of the specified player 3D progress bar. Returns 0 if value is greater than max value. Returns `INVALID_PLAYER_3D_BAR` if bar doesn't exist.

```pawn
GetPlayerProgressBar3DColor(playerid, PlayerBar3D:barid)
```

Returns the color of the specified player 3D progress bar. Returns `INVALID_PLAYER_3D_BAR` if bar doesn't exist.

```pawn
SetPlayerProgressBar3DColor(playerid, PlayerBar3D:barid, color)
```

Updates the color of the specified player 3D progress bar. Returns `INVALID_GLOBAL_3D_BAR` if bar doesn't exist.

```pawn
Float:GetPlayerProgressBar3DMaxValue(playerid, PlayerBar3D:barid)
```

Returns the maximum value of the specified player 3D progress bar. Returns `INVALID_PLAYER_3D_BAR` if bar doesn't exist.

```pawn
SetPlayerProgressBar3DMaxValue(playerid, PlayerBar3D:barid, Float:max_value)
```

Updates the maximum value of the specified player 3D progress bar. Returns 0 if the max value is smaller than the current value. Returns `INVALID_PLAYER_3D_BAR` if bar doesn't exist.

```pawn
IsValidPlayerProgressBar3D(playerid, PlayerBar3D:barid)
```

Returns 1, if the specified player 3D progress bar ID is valid and exists. Returns `INVALID_PLAYER_3D_BAR` if bar doesn't exist.

### Internal

```pawn
_UpdateProgress3D(barid, playerid, type, color, bool:shown, Float:max_value, Float:value)
```

Updates the properties of a 3D progress bar. Called whenever any property of the 3D progress bar is changed.

## Testing

To test, simply run the package using

```bash
sampctl package run
```

and connect to your localhost (`localhost:7777` or `127.0.0.1:7777`).

### Commands

* `/bar <0 or 1> <0 or 1>` to create a 3D progress bar.
  1. Auto-Fill Mode (0: disable, 1: enable)
  2. Borders (0: disable, 1: enable)
* `/value <float>` to change the value.
* `/max <float>` to change the maximum value.
* `/color` to change the color randomly.
