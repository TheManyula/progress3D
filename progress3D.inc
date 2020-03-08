#if defined _inc_progress3D
    #undef _inc_progress3D
#endif

#if defined progress3D_included_
    #endinput
#endif
#define progress3D_included_

#include <a_samp>
#include <streamer>
#include <YSI_Data\y_iterate>

#define SetAlpha(%0)   (%0 & 0xFFFFFFFE)
#define Darken(%0)     (%0 & 0x80808000)

#define MAX_3D_BARS    512
#define INVALID_3D_BAR Bar3D:-1

enum BAR_3D_DATA {
    barColor,
    bool:barBorders,
    bool:barShown,
    Float:maxValue,
    Float:barValue,
    Text3D:Bar1, 
    Text3D:Bar2,
    Text3D:BgBar1,
    Text3D:BgBar2
}

static Bar3D:Bars3D[MAX_3D_BARS][BAR_3D_DATA],
       Iterator:Bars3D_Index<MAX_3D_BARS>;

static _UpdateProgress3D(barid, color, bool:shown, Float:max, Float:value) {    
    new bar1_idx,
        bar2_idx,
        bar1[35],
        bar2[35],
        bar_color[13];
    
    bar1 = "IIIIIIIIIIIIIIIIIIIIIIIII",
    bar2 = " IIIIIIIIIIIIIIIIIIIIIIIII";

    if(shown) {
        format(bar_color, sizeof(bar_color), "{%06x}", Darken(color) >>> 8); 
        bar1_idx = bar2_idx = floatround(value / (max / 25), floatround_round);

        strins(bar1, bar_color, bar1_idx);
        strins(bar2, bar_color, bar2_idx + 1);
    }

    UpdateDynamic3DTextLabelText(Bars3D[_:barid][Bar1], (shown) ? (SetAlpha(color)) : (0x00000000), bar1);
    UpdateDynamic3DTextLabelText(Bars3D[_:barid][Bar2], (shown) ? (SetAlpha(color)) : (0x00000000), bar2);

    UpdateDynamic3DTextLabelText(Bars3D[_:barid][BgBar1], (shown) ? (0x000000FF) : (0x00000000), "||||||||||||||||||||||||||");
    UpdateDynamic3DTextLabelText(Bars3D[_:barid][BgBar2], (shown) ? (0x000000FF) : (0x00000000), " ||||||||||||||||||||||||||");
    return 1;
}

stock Bar3D:CreateProgressBar3D(color, bool:borders, Float:x, Float:y, Float:z, Float:max_value, Float:init_value, Float:drawdistance, attachedplayer = INVALID_PLAYER_ID, attachedvehicle = INVALID_VEHICLE_ID, testlos = 0, worldid = -1, interiorid = -1, playerid = -1, Float:streamdistance = STREAMER_3D_TEXT_LABEL_SD, areaid = -1, priority = 0) {
    new barid = Iter_Free(Bars3D_Index);
    if(barid == ITER_NONE) {
        return INVALID_3D_BAR;
    }

    if(borders) {
        Bars3D[barid][barBorders] = true;
        Bars3D[barid][BgBar1] = CreateDynamic3DTextLabel("||||||||||||||||||||||||||", 0x000000FF, x, y, z+0.0075, drawdistance, attachedplayer, attachedvehicle, testlos, worldid, interiorid, playerid, streamdistance, areaid, priority+1);
        Bars3D[barid][BgBar2] = CreateDynamic3DTextLabel(" ||||||||||||||||||||||||||", 0x000000FF, x, y, z+0.0075, drawdistance, attachedplayer, attachedvehicle, testlos, worldid, interiorid, playerid, streamdistance, areaid, priority+1);
    }

    Bars3D[barid][Bar1] = CreateDynamic3DTextLabel("Loading...", SetAlpha(color), x, y, z, drawdistance, attachedplayer, attachedvehicle, testlos, worldid, interiorid, playerid, streamdistance, areaid, priority);
    Bars3D[barid][Bar2] = CreateDynamic3DTextLabel("Loading...", SetAlpha(color), x, y, z, drawdistance, attachedplayer, attachedvehicle, testlos, worldid, interiorid, playerid, streamdistance, areaid, priority);

    _UpdateProgress3D(barid, color, true, max_value, init_value);

    Bars3D[barid][barColor] = color;
    Bars3D[barid][barShown] = true;
    Bars3D[barid][maxValue] = max_value;
    Bars3D[barid][barValue] = init_value;

    Iter_Add(Bars3D_Index, barid);
    return Bar3D:barid;
}

stock HideProgressBar3D(Bar3D:barid) {
    _UpdateProgress3D(_:barid, 0x00000000, false, Bars3D[_:barid][maxValue], Bars3D[_:barid][maxValue]);
    Bars3D[_:barid][barShown] = false;
    return 1;
}

stock ShowProgressBar3D(Bar3D:barid) {
    _UpdateProgress3D(_:barid, Bars3D[_:barid][barColor], true, Bars3D[_:barid][maxValue], Bars3D[_:barid][barValue]);
    Bars3D[_:barid][barShown] = true;
    return 1;
}

stock DestroyProgressBar3D(Bar3D:barid) {
    if(!IsValidProgressBar3D(barid)) {
        return _:INVALID_3D_BAR;
    }

    Bars3D[_:barid][barColor] = -1;
    Bars3D[_:barid][barBorders] = false;
    Bars3D[_:barid][barShown] = false;
    Bars3D[_:barid][maxValue] = -1;
    Bars3D[_:barid][barValue] = -1;

    DestroyDynamic3DTextLabel(Bars3D[_:barid][Bar1]);
    DestroyDynamic3DTextLabel(Bars3D[_:barid][Bar2]);

    if(Bars3D[_:barid][barBorders]) {
        DestroyDynamic3DTextLabel(Bars3D[_:barid][BgBar1]);
        DestroyDynamic3DTextLabel(Bars3D[_:barid][BgBar2]);
    }

    Iter_Remove(Bars3D_Index, _:barid);
    return 1;
}

stock GetProgressBar3DValue(Bar3D:barid) {
    if(!IsValidProgressBar3D(barid)) {
        return 0;
    }
    return Bars3D[_:barid][barValue];
}

stock SetProgressBar3DValue(Bar3D:barid, Float:value) {
    if(!IsValidProgressBar3D(barid)) {
        return 0;
    }

    if(value > Bars3D[_:barid][maxValue]) {
        return 0;
    }

    _UpdateProgress3D(_:barid, Bars3D[_:barid][barColor], Bars3D[_:barid][barShown], Bars3D[_:barid][maxValue], value);
    Bars3D[_:barid][barValue] = value;
    return 1;
}

stock GetProgressBar3DColor(Bar3D:barid) {
    if(!IsValidProgressBar3D(barid)) {
        return 0;
    }
    return _:Bars3D[_:barid][barColor];
}

stock SetProgressBar3DColor(Bar3D:barid, color) {
    if(!IsValidProgressBar3D(barid)) {
        return 0;
    }

    _UpdateProgress3D(_:barid, color, Bars3D[_:barid][barShown], Bars3D[_:barid][maxValue], Bars3D[_:barid][barValue]);
    Bars3D[_:barid][barColor] = color;
    return 1;
}

stock GetProgressBar3DMaxValue(Bar3D:barid) {
    if(!IsValidProgressBar3D(barid)) {
        return 0;
    }
    return _:Bars3D[_:barid][maxValue];
}

stock SetProgressBar3DMaxValue(Bar3D:barid, Float:max_value) {
    if(!IsValidProgressBar3D(barid)) {
        return 0;
    }

    if(max_value < Bars3D[_:barid][barValue]) {
        return 0;
    }

    _UpdateProgress3D(_:barid, Bars3D[_:barid][barColor], Bars3D[_:barid][barShown], max_value, Bars3D[_:barid][barValue]);
    Bars3D[_:barid][maxValue] = max_value;
    return 1;
}

stock IsValidProgressBar3D(Bar3D:barid) {
	return Iter_Contains(Bars3D_Index, _:barid);
}
