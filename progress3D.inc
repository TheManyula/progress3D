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
#include <YSI\y_iterate>

enum BAR_3D_DATA {
    fillColor,
    backgroundColor,
    Float:barValue
}

static Bar3D:Bars3D[MAX_3D_BARS][BAR_3D_DATA],
       Text3D:Bars1[MAX_3D_BARS],
       Text3D:Bars2[MAX_3D_BARS];

new Iterator:Bars3D_Index<MAX_3D_BARS>,
    Iterator:Bars1_Index<MAX_3D_BARS>,
    Iterator:Bars2_Index<MAX_3D_BARS>;

stock Bar3D:CreateProgressBar3D(fill_color, background_color, Float:init_value, Float:x, Float:y, Float:z, Float:drawdistance, attachedplayer = INVALID_PLAYER_ID, attachedvehicle = INVALID_VEHICLE_ID, testlos = 0, worldid = -1, interiorid = -1, playerid = -1, Float:streamdistance = STREAMER_3D_TEXT_LABEL_SD, STREAMER_TAG_AREA areaid = STREAMER_TAG_AREA -1) {
    new barid = Iter_Free(Bars3D_Index);

    if(barid == ITER_NONE) {
        print("[ERROR] The 'MAX_3D_BARS' limit is reached. Please destroy a 3D progress bar to free space.");
        return INVALID_3D_BAR;
    }
    
    new bar1[34], bar1_idx,
        bar2[34], bar2_idx;
    
    bar1 = "IIIIIIIIIIIIIIIIIIIIIIIII",
    bar2 = " IIIIIIIIIIIIIIIIIIIIIIIII";
    
    Bars1[barid] = CreateDynamic3DTextLabel(bar1, fill_color-1, x, y, z, drawdistance, attachedplayer, attachedvehicle, testlos, worldid, interiorid, playerid, streamdistance, areaid);
    Bars2[barid] = CreateDynamic3DTextLabel(bar2, fill_color-1, x, y, z, drawdistance, attachedplayer, attachedvehicle, testlos, worldid, interiorid, playerid, streamdistance, areaid);

    new bcolor[16];
    format(bcolor, sizeof(bcolor), "{%06x}", background_color-1 >>> 8);

    bar1_idx = bar2_idx = floatround(init_value / 4, floatround_round);
    strins(bar1, bcolor, bar1_idx);
    strins(bar2, bcolor, bar2_idx+1);
    UpdateDynamic3DTextLabelText(Bars1[barid], fill_color-1, bar1);
    UpdateDynamic3DTextLabelText(Bars2[barid], fill_color-1, bar2);

    Bars3D[barid][fillColor] = fill_color;
    Bars3D[barid][backgroundColor] = background_color;
    Bars3D[barid][barValue] = init_value;

    Iter_Add(Bars3D_Index, barid);
    Iter_Add(Bars1_Index, barid);
    Iter_Add(Bars2_Index, barid);
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
    Iter_Remove(Bars1_Index, _:barid);
    Iter_Remove(Bars2_Index, _:barid);

    DestroyDynamic3DTextLabel(Bars1[_:barid]);
    DestroyDynamic3DTextLabel(Bars2[_:barid]);
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

    new bar1[34],   bar1_idx,
        bar2[34],   bar2_idx,
        bcolor[16], fcolor = Bars3D[_:barid][fillColor];
    
    bar1 = "IIIIIIIIIIIIIIIIIIIIIIIII",
    bar2 = " IIIIIIIIIIIIIIIIIIIIIIIII";

    format(bcolor, sizeof(bcolor), "{%06x}", Bars3D[_:barid][backgroundColor]-1 >>> 8);

    bar1_idx = bar2_idx = floatround(value / 4, floatround_round);
    strins(bar1, bcolor, bar1_idx);
    strins(bar2, bcolor, bar2_idx+1);
    UpdateDynamic3DTextLabelText(Bars1[_:barid], fcolor-1, bar1);
    UpdateDynamic3DTextLabelText(Bars2[_:barid], fcolor-1, bar2);

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

    new bar1[34],   bar1_idx,
        bar2[34],   bar2_idx,
        bcolor[16];
    
    bar1 = "IIIIIIIIIIIIIIIIIIIIIIIII",
    bar2 = " IIIIIIIIIIIIIIIIIIIIIIIII";

    format(bcolor, sizeof(bcolor), "{%06x}", Bars3D[_:barid][backgroundColor]-1 >>> 8);

    bar1_idx = bar2_idx = floatround(Bars3D[_:barid][barValue] / 4, floatround_round);
    strins(bar1, bcolor, bar1_idx);
    strins(bar2, bcolor, bar2_idx+1);
    UpdateDynamic3DTextLabelText(Bars1[_:barid], fill_color-1, bar1);
    UpdateDynamic3DTextLabelText(Bars2[_:barid], fill_color-1, bar2);

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

    new bar1[34],   bar1_idx,
        bar2[34],   bar2_idx,
        bcolor[16], fcolor = Bars3D[_:barid][fillColor];
    
    bar1 = "IIIIIIIIIIIIIIIIIIIIIIIII",
    bar2 = " IIIIIIIIIIIIIIIIIIIIIIIII";

    format(bcolor, sizeof(bcolor), "{%06x}", background_color-1 >>> 8);

    bar1_idx = bar2_idx = floatround(Bars3D[_:barid][barValue] / 4, floatround_round);
    strins(bar1, bcolor, bar1_idx);
    strins(bar2, bcolor, bar2_idx+1);
    UpdateDynamic3DTextLabelText(Bars1[_:barid], fcolor-1, bar1);
    UpdateDynamic3DTextLabelText(Bars2[_:barid], fcolor-1, bar2);

    Bars3D[_:barid][backgroundColor] = background_color-1;
    return 1;
}

stock IsValidProgressBar3D(Bar3D:barid) {
	return Iter_Contains(Bars3D_Index, _:barid);
}