#if defined _inc_progress3D
    #undef _inc_progress3D
#endif

#if defined progress3D_included_
    #endinput
#endif
#define progress3D_included_

#define MAX_3D_BARS     512
#define INVALID_3D_BAR  Bar3D:-1

#include <a_samp>
#include <streamer>
#include <YSI_Data\y_iterate>

enum BAR_3D_DATA {
    fillColor,
    backgroundColor,
    Float:barValue,
    Text3D:Bar1, 
    Text3D:Bar2 
}

static Bar3D:Bars3D[MAX_3D_BARS][BAR_3D_DATA];
new Iterator:Bars3D_Index<MAX_3D_BARS>;

static UpdateProgress(barid, fill_color, background_color, Float:value) {
    if(value > 100.0) {
        value = 100.0;
    } else if(value < 0) {
        value = 0.0;
    }
    
    new bar1[36],
        bar2[36],
        bar1_idx,
        bar2_idx;
    
    bar1 = "IIIIIIIIIIIIIIIIIIIIIIIII",
    bar2 = " IIIIIIIIIIIIIIIIIIIIIIIII";

    new bcolor[16];
    format(bcolor, sizeof(bcolor), "{%06x}", (background_color - 1) >>> 8);

    bar1_idx = bar2_idx = floatround(value / 4, floatround_round);
    strins(bar1, bcolor, bar1_idx, 36);
    printf("bar1: %s", bar1);
    printf("bar2: %s", bar2);
    strins(bar2, bcolor, bar2_idx + 1, 36);
    printf("bar1: %s", bar1);
    printf("bar2: %s", bar2);
    UpdateDynamic3DTextLabelText(Bars3D[barid][Bar1], (fill_color - 1), bar1);
    UpdateDynamic3DTextLabelText(Bars3D[barid][Bar2], (fill_color - 1), bar2);
    return 1;
}

stock Bar3D:CreateProgressBar3D(fill_color, background_color, Float:init_value, Float:x, Float:y, Float:z, Float:drawdistance, attachedplayer = INVALID_PLAYER_ID, attachedvehicle = INVALID_VEHICLE_ID, testlos = 0, worldid = -1, interiorid = -1, playerid = -1, Float:streamdistance = STREAMER_3D_TEXT_LABEL_SD, STREAMER_TAG_AREA areaid = STREAMER_TAG_AREA -1) {
    new barid = Iter_Free(Bars3D_Index);

    if(barid == ITER_NONE) {
        return INVALID_3D_BAR;
    }
    
    Bars3D[barid][Bar1] = CreateDynamic3DTextLabel("IIIIIIIIIIIIIIIIIIIIIIIII", fill_color-1, x, y, z, drawdistance, attachedplayer, attachedvehicle, testlos, worldid, interiorid, playerid, streamdistance, areaid);
    Bars3D[barid][Bar2] = CreateDynamic3DTextLabel(" IIIIIIIIIIIIIIIIIIIIIIIII", fill_color-1, x, y, z, drawdistance, attachedplayer, attachedvehicle, testlos, worldid, interiorid, playerid, streamdistance, areaid);

    UpdateProgress(barid, fill_color, background_color, init_value);

    Bars3D[barid][fillColor] = fill_color;
    Bars3D[barid][backgroundColor] = background_color;
    Bars3D[barid][barValue] = init_value;

    Iter_Add(Bars3D_Index, barid);
    return Bar3D:barid;
}

stock DestroyProgressBar3D(Bar3D:barid) {
    if(!IsValidProgressBar3D(barid)) {
        return 0;
    }

    Bars3D[_:barid][fillColor] = 0;
    Bars3D[_:barid][backgroundColor] = 0;
    Bars3D[_:barid][barValue] = 0;

    Iter_Remove(Bars3D_Index, _:barid);

    DestroyDynamic3DTextLabel(Bars3D[_:barid][Bar1]);
    DestroyDynamic3DTextLabel(Bars3D[_:barid][Bar2]);
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

    UpdateProgress(_:barid, Bars3D[_:barid][fillColor], Bars3D[_:barid][backgroundColor], value);
    Bars3D[_:barid][barValue] = value;
    return 1;
}

stock GetProgressBar3DFillColor(Bar3D:barid) {
    if(!IsValidProgressBar3D(barid)) {
        return 0;
    }
    return Bars3D[_:barid][fillColor];
}

stock SetProgressBar3DFillColor(Bar3D:barid, fill_color) {
    if(!IsValidProgressBar3D(barid)) {
        return 0;
    }

    UpdateProgress(_:barid, fill_color, Bars3D[_:barid][backgroundColor], Bars3D[_:barid][barValue]);
    Bars3D[_:barid][fillColor] = fill_color-1;
    return 1;
}

stock GetProgressBar3DBackgroundColor(Bar3D:barid) {
    if(!IsValidProgressBar3D(barid)) {
        return 0;
    }
    return Bars3D[_:barid][backgroundColor];
}

stock SetProgressBar3DBackgroundColor(Bar3D:barid, background_color) {
    if(!IsValidProgressBar3D(barid)) {
        return 0;
    }

    UpdateProgress(_:barid, Bars3D[_:barid][fillColor], background_color, Bars3D[_:barid][barValue]);
    Bars3D[_:barid][backgroundColor] = background_color-1;
    return 1;
}

stock IsValidProgressBar3D(Bar3D:barid) {
	return Iter_Contains(Bars3D_Index, _:barid);
}