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
#include <YSI_Coding\y_hooks>

#define SetAlpha(%0)            (%0 & 0xFFFFFFFE)
#define Darken(%0)              (%0 & 0x80808000)

#define MAX_3D_BARS             512
#define INVALID_3D_BAR          Bar3D:-1

#define BAR_3D_LAYOUT_THIN      0
#define BAR_3D_LAYOUT_NORMAL    1
#define BAR_3D_LAYOUT_THICK     2

enum BAR_3D_DATA {
    barLayout,
    barColor,
    Float:maxValue,
    Float:barValue,
    Text3D:Bar1, 
    Text3D:Bar2 
}

static Bar3D:Bars3D[MAX_3D_BARS][BAR_3D_DATA],
       Iterator:Bars3D_Index<MAX_3D_BARS>;

static _UpdateProgress3D(barid, color, layout, Float:max, Float:value) {    
    new bar1_idx,
        bar2_idx,
        bar1[35],
        bar2[35],
        bar_color[13];
    
    switch(layout) {
        case BAR_3D_LAYOUT_THIN:
            bar1 = "'''''''''''''''''''''''''",
            bar2 = " '''''''''''''''''''''''''";
        case BAR_3D_LAYOUT_NORMAL:
            bar1 = "IIIIIIIIIIIIIIIIIIIIIIIII",
            bar2 = " IIIIIIIIIIIIIIIIIIIIIIIII";
        case BAR_3D_LAYOUT_THICK:
            bar1 = "|||||||||||||||||||||||||",
            bar2 = " |||||||||||||||||||||||||";
    }

    format(bar_color, sizeof(bar_color), "{%06x}", Darken(color) >>> 8); 
    bar1_idx = bar2_idx = floatround(value / (max / 25), floatround_round);
    strins(bar1, bar_color, bar1_idx);
    strins(bar2, bar_color, bar2_idx + 1);
    UpdateDynamic3DTextLabelText(Bars3D[barid][Bar1], SetAlpha(color), bar1);
    UpdateDynamic3DTextLabelText(Bars3D[barid][Bar2], SetAlpha(color), bar2);
    return 1;
}

stock Bar3D:CreateProgressBar3D(color, layout, Float:x, Float:y, Float:z, Float:max_value, Float:init_value, Float:drawdistance, attachedplayer = INVALID_PLAYER_ID, attachedvehicle = INVALID_VEHICLE_ID, testlos = 0, worldid = -1, interiorid = -1, playerid = -1, Float:streamdistance = STREAMER_3D_TEXT_LABEL_SD, areaid = -1, priority = 0) {
    new barid = Iter_Free(Bars3D_Index);
    if(barid == ITER_NONE) {
        return INVALID_3D_BAR;
    }

    Bars3D[barid][Bar1] = CreateDynamic3DTextLabel("Loading...", SetAlpha(color), x, y, z, drawdistance, attachedplayer, attachedvehicle, testlos, worldid, interiorid, playerid, streamdistance, areaid, priority);
    Bars3D[barid][Bar2] = CreateDynamic3DTextLabel("Loading...", SetAlpha(color), x, y, z, drawdistance, attachedplayer, attachedvehicle, testlos, worldid, interiorid, playerid, streamdistance, areaid, priority);

    _UpdateProgress3D(barid, color, layout, max_value, init_value);

    Bars3D[barid][barColor] = color;
    Bars3D[barid][barLayout] = layout;
    Bars3D[barid][maxValue] = max_value;
    Bars3D[barid][barValue] = init_value;

    Iter_Add(Bars3D_Index, barid);
    return Bar3D:barid;
}

stock DestroyProgressBar3D(Bar3D:barid) {
    if(!IsValidProgressBar3D(barid)) {
        return 0;
    }

    Bars3D[_:barid][barColor] = -1;
    Bars3D[_:barid][barLayout] = -1;
    Bars3D[_:barid][maxValue] = -1;
    Bars3D[_:barid][barValue] = -1;

    DestroyDynamic3DTextLabel(Bars3D[_:barid][Bar1]);
    DestroyDynamic3DTextLabel(Bars3D[_:barid][Bar2]);

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
    _UpdateProgress3D(_:barid, Bars3D[_:barid][barColor], Bars3D[_:barid][barLayout], Bars3D[_:barid][maxValue], value);
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
    _UpdateProgress3D(_:barid, SetAlpha(color), Bars3D[_:barid][barLayout], Bars3D[_:barid][maxValue], Bars3D[_:barid][barValue]);
    Bars3D[_:barid][barColor] = SetAlpha(color);
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
    _UpdateProgress3D(_:barid, Bars3D[_:barid][barColor], Bars3D[_:barid][barLayout], max_value, Bars3D[_:barid][barValue]);
    Bars3D[_:barid][maxValue] = max_value;
    return 1;
}

stock GetProgressBar3DLayout(Bar3D:barid) {
    if(!IsValidProgressBar3D(barid)) {
        return 0;
    }
    return _:Bars3D[_:barid][barLayout];
}

stock SetProgressBar3DLayout(Bar3D:barid, layout) {
    if(!IsValidProgressBar3D(barid)) {
        return 0;
    }
    _UpdateProgress3D(_:barid, Bars3D[_:barid][barColor], layout, Bars3D[_:barid][maxValue], Bars3D[_:barid][barValue]);
    Bars3D[_:barid][barLayout] = layout;
    return 1;
}

stock IsValidProgressBar3D(Bar3D:barid) {
	return Iter_Contains(Bars3D_Index, _:barid);
}
