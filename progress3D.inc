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

#define SetAlpha(%0)          (%0 & 0xFFFFFFFE)
#define Darken(%0)            (%0 & 0x80808000)

#define BAR_3D_TYPE_GLOBAL    0
#define BAR_3D_TYPE_PLAYER    1

#define MAX_GLOBAL_3D_BARS    MAX_3DTEXT_GLOBAL
#define MAX_PLAYER_3D_BARS    MAX_3DTEXT_PLAYER

#define INVALID_GLOBAL_3D_BAR Bar3D:-1
#define INVALID_PLAYER_3D_BAR PlayerBar3D:-1

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

static Bar3D:GlobalBars3D[MAX_GLOBAL_3D_BARS][BAR_3D_DATA],
       PlayerBar3D:PlayerBars3D[MAX_PLAYERS][MAX_PLAYER_3D_BARS][BAR_3D_DATA],
       Iterator:GlobalBars3D_Index<MAX_GLOBAL_3D_BARS>,
       Iterator:PlayerBars3D_Index[MAX_PLAYERS]<MAX_PLAYER_3D_BARS>;

static _UpdateProgress3D(barid, playerid, type, color, bool:borders, bool:shown, Float:max, Float:value) {    
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

    UpdateDynamic3DTextLabelText((type == BAR_3D_TYPE_GLOBAL) ? (GlobalBars3D[_:barid][Bar1]) : (PlayerBars3D[playerid][_:barid][Bar1]), (shown) ? (SetAlpha(color)) : (0x00000000), bar1);
    UpdateDynamic3DTextLabelText((type == BAR_3D_TYPE_GLOBAL) ? (GlobalBars3D[_:barid][Bar2]) : (PlayerBars3D[playerid][_:barid][Bar2]), (shown) ? (SetAlpha(color)) : (0x00000000), bar2);

    if(borders) {
        UpdateDynamic3DTextLabelText((type == BAR_3D_TYPE_GLOBAL) ? (GlobalBars3D[_:barid][BgBar1]) : (PlayerBars3D[playerid][_:barid][BgBar1]), (shown) ? (0x000000FF) : (0x00000000), "||||||||||||||||||||||||||");
        UpdateDynamic3DTextLabelText((type == BAR_3D_TYPE_GLOBAL) ? (GlobalBars3D[_:barid][BgBar2]) : (PlayerBars3D[playerid][_:barid][BgBar2]), (shown) ? (0x000000FF) : (0x00000000), " ||||||||||||||||||||||||||");
    }
    return 1;
}

// API for Progress 3D Bars

stock Bar3D:CreateProgressBar3D(color, bool:borders, Float:x, Float:y, Float:z, Float:max_value, Float:init_value, Float:drawdistance, attachedplayer = INVALID_PLAYER_ID, attachedvehicle = INVALID_VEHICLE_ID, testlos = 0, worldid = -1, interiorid = -1, Float:streamdistance = STREAMER_3D_TEXT_LABEL_SD, areaid = -1, priority = 0) {
    new barid = Iter_Free(GlobalBars3D_Index);
    if(barid == ITER_NONE) {
        return INVALID_GLOBAL_3D_BAR;
    }

    if(borders && !IsValidDynamic3DTextLabel(GlobalBars3D[barid][BgBar1]) && !IsValidDynamic3DTextLabel(GlobalBars3D[barid][BgBar2])) {
        GlobalBars3D[barid][BgBar1] = CreateDynamic3DTextLabel("||||||||||||||||||||||||||", 0x000000FF, x, y, z+0.0075, drawdistance, attachedplayer, attachedvehicle, testlos, worldid, interiorid, -1, streamdistance, areaid, priority+1);
        GlobalBars3D[barid][BgBar2] = CreateDynamic3DTextLabel(" ||||||||||||||||||||||||||", 0x000000FF, x, y, z+0.0075, drawdistance, attachedplayer, attachedvehicle, testlos, worldid, interiorid, -1, streamdistance, areaid, priority+1);
    }

    GlobalBars3D[barid][Bar1] = CreateDynamic3DTextLabel("Loading...", SetAlpha(color), x, y, z, drawdistance, attachedplayer, attachedvehicle, testlos, worldid, interiorid, -1, streamdistance, areaid, priority);
    GlobalBars3D[barid][Bar2] = CreateDynamic3DTextLabel("Loading...", SetAlpha(color), x, y, z, drawdistance, attachedplayer, attachedvehicle, testlos, worldid, interiorid, -1, streamdistance, areaid, priority);

    _UpdateProgress3D(barid, -1, BAR_3D_TYPE_GLOBAL, color, borders, true, max_value, init_value);

    GlobalBars3D[barid][barColor] = color;
    GlobalBars3D[barid][barBorders] = borders;
    GlobalBars3D[barid][barShown] = true;
    GlobalBars3D[barid][maxValue] = max_value;
    GlobalBars3D[barid][barValue] = init_value;

    Iter_Add(GlobalBars3D_Index, barid);
    return Bar3D:barid;
}

stock HideProgressBar3D(Bar3D:barid) {
    if(!IsValidProgressBar3D(barid)) {
        return _:INVALID_GLOBAL_3D_BAR;
    }

    _UpdateProgress3D(_:barid, -1, BAR_3D_TYPE_GLOBAL, 0x00000000, GlobalBars3D[_:barid][barBorders], false, GlobalBars3D[_:barid][maxValue], GlobalBars3D[_:barid][maxValue]);
    GlobalBars3D[_:barid][barShown] = false;
    return 1;
}

stock ShowProgressBar3D(Bar3D:barid) {
    if(!IsValidProgressBar3D(barid)) {
        return _:INVALID_GLOBAL_3D_BAR;
    }

    _UpdateProgress3D(_:barid, -1, BAR_3D_TYPE_GLOBAL, GlobalBars3D[_:barid][barColor], GlobalBars3D[_:barid][barBorders], true, GlobalBars3D[_:barid][maxValue], GlobalBars3D[_:barid][barValue]);
    GlobalBars3D[_:barid][barShown] = true;
    return 1;
}

stock DestroyProgressBar3D(Bar3D:barid) {
    if(!IsValidProgressBar3D(barid)) {
        return _:INVALID_GLOBAL_3D_BAR;
    }

    GlobalBars3D[_:barid][barColor] = -1;
    GlobalBars3D[_:barid][barShown] = false;
    GlobalBars3D[_:barid][maxValue] = -1;
    GlobalBars3D[_:barid][barValue] = -1;

    DestroyDynamic3DTextLabel(GlobalBars3D[_:barid][Bar1]);
    DestroyDynamic3DTextLabel(GlobalBars3D[_:barid][Bar2]);

    if(GlobalBars3D[_:barid][barBorders]) {
        GlobalBars3D[_:barid][barBorders] = false;
        DestroyDynamic3DTextLabel(GlobalBars3D[_:barid][BgBar1]);
        DestroyDynamic3DTextLabel(GlobalBars3D[_:barid][BgBar2]);
    }

    Iter_Remove(GlobalBars3D_Index, _:barid);
    return 1;
}

stock Float:GetProgressBar3DValue(Bar3D:barid) {
    if(!IsValidProgressBar3D(barid)) {
        return Float:INVALID_GLOBAL_3D_BAR;
    }
    return GlobalBars3D[_:barid][barValue];
}

stock SetProgressBar3DValue(Bar3D:barid, Float:value) {
    if(!IsValidProgressBar3D(barid)) {
        return _:INVALID_GLOBAL_3D_BAR;
    }

    if(value > GlobalBars3D[_:barid][maxValue]) {
        return 0;
    }

    _UpdateProgress3D(_:barid, -1, BAR_3D_TYPE_GLOBAL, GlobalBars3D[_:barid][barColor], GlobalBars3D[_:barid][barBorders], GlobalBars3D[_:barid][barShown], GlobalBars3D[_:barid][maxValue], value);
    GlobalBars3D[_:barid][barValue] = value;
    return 1;
}

stock GetProgressBar3DColor(Bar3D:barid) {
    if(!IsValidProgressBar3D(barid)) {
        return _:INVALID_GLOBAL_3D_BAR;
    }
    return GlobalBars3D[_:barid][barColor];
}

stock SetProgressBar3DColor(Bar3D:barid, color) {
    if(!IsValidProgressBar3D(barid)) {
        return _:INVALID_GLOBAL_3D_BAR;
    }

    _UpdateProgress3D(_:barid, -1, BAR_3D_TYPE_GLOBAL, color, GlobalBars3D[_:barid][barBorders], GlobalBars3D[_:barid][barShown], GlobalBars3D[_:barid][maxValue], GlobalBars3D[_:barid][barValue]);
    GlobalBars3D[_:barid][barColor] = color;
    return 1;
}

stock Float:GetProgressBar3DMaxValue(Bar3D:barid) {
    if(!IsValidProgressBar3D(barid)) {
        return Float:INVALID_GLOBAL_3D_BAR;
    }
    return GlobalBars3D[_:barid][maxValue];
}

stock SetProgressBar3DMaxValue(Bar3D:barid, Float:max_value) {
    if(!IsValidProgressBar3D(barid)) {
        return _:INVALID_GLOBAL_3D_BAR;
    }

    if(max_value < GlobalBars3D[_:barid][barValue]) {
        return 0;
    }

    _UpdateProgress3D(_:barid, -1, BAR_3D_TYPE_GLOBAL, GlobalBars3D[_:barid][barColor], GlobalBars3D[_:barid][barBorders], GlobalBars3D[_:barid][barShown], max_value, GlobalBars3D[_:barid][barValue]);
    GlobalBars3D[_:barid][maxValue] = max_value;
    return 1;
}

stock IsValidProgressBar3D(Bar3D:barid) {
	return Iter_Contains(GlobalBars3D_Index, _:barid);
}

// API for Player Progress 3D Bars

stock PlayerBar3D:CreatePlayerProgressBar3D(playerid, color, bool:borders, Float:x, Float:y, Float:z, Float:max_value, Float:init_value, Float:drawdistance, attachedplayer = INVALID_PLAYER_ID, attachedvehicle = INVALID_VEHICLE_ID, testlos = 0, worldid = -1, interiorid = -1, Float:streamdistance = STREAMER_3D_TEXT_LABEL_SD, areaid = -1, priority = 0) {
    if(playerid == -1) {
        return INVALID_PLAYER_3D_BAR;
    }
    
    new barid = Iter_Free(PlayerBars3D_Index[playerid]);
    if(barid == ITER_NONE) {
        return INVALID_PLAYER_3D_BAR;
    }
    
    if(borders && !IsValidDynamic3DTextLabel(PlayerBars3D[playerid][barid][BgBar1]) && !IsValidDynamic3DTextLabel(PlayerBars3D[playerid][barid][BgBar2])) {
        PlayerBars3D[playerid][barid][BgBar1] = CreateDynamic3DTextLabel("||||||||||||||||||||||||||", 0x000000FF, x, y, z+0.0075, drawdistance, attachedplayer, attachedvehicle, testlos, worldid, interiorid, playerid, streamdistance, areaid, priority+1);
        PlayerBars3D[playerid][barid][BgBar2] = CreateDynamic3DTextLabel(" ||||||||||||||||||||||||||", 0x000000FF, x, y, z+0.0075, drawdistance, attachedplayer, attachedvehicle, testlos, worldid, interiorid, playerid, streamdistance, areaid, priority+1);
    }

    PlayerBars3D[playerid][barid][Bar1] = CreateDynamic3DTextLabel("Loading...", SetAlpha(color), x, y, z, drawdistance, attachedplayer, attachedvehicle, testlos, worldid, interiorid, playerid, streamdistance, areaid, priority);
    PlayerBars3D[playerid][barid][Bar2] = CreateDynamic3DTextLabel("Loading...", SetAlpha(color), x, y, z, drawdistance, attachedplayer, attachedvehicle, testlos, worldid, interiorid, playerid, streamdistance, areaid, priority);

    _UpdateProgress3D(barid, playerid, BAR_3D_TYPE_PLAYER, color, borders, true, max_value, init_value);

    PlayerBars3D[playerid][barid][barColor] = color;
    PlayerBars3D[playerid][barid][barBorders] = borders;
    PlayerBars3D[playerid][barid][barShown] = true;
    PlayerBars3D[playerid][barid][maxValue] = max_value;
    PlayerBars3D[playerid][barid][barValue] = init_value;

    Iter_Add(PlayerBars3D_Index[playerid], barid);
    return PlayerBar3D:barid;
}

stock HidePlayerProgressBar3D(playerid, PlayerBar3D:barid) {
    if(!IsValidPlayerProgressBar3D(playerid, barid)) {
        return _:INVALID_PLAYER_3D_BAR;
    }

    _UpdateProgress3D(_:barid, playerid, BAR_3D_TYPE_PLAYER, 0x00000000, PlayerBars3D[playerid][_:barid][barBorders], false, PlayerBars3D[playerid][_:barid][maxValue], PlayerBars3D[playerid][_:barid][maxValue]);
    PlayerBars3D[playerid][_:barid][barShown] = false;
    return 1;
}

stock ShowPlayerProgressBar3D(playerid, PlayerBar3D:barid) {
    if(!IsValidPlayerProgressBar3D(playerid, barid)) {
        return _:INVALID_PLAYER_3D_BAR;
    }

    _UpdateProgress3D(_:barid, playerid, BAR_3D_TYPE_PLAYER, PlayerBars3D[playerid][_:barid][barColor], PlayerBars3D[playerid][_:barid][barBorders], true, PlayerBars3D[playerid][_:barid][maxValue], PlayerBars3D[playerid][_:barid][barValue]);
    PlayerBars3D[playerid][_:barid][barShown] = true;
    return 1;
}

stock DestroyPlayerProgressBar3D(playerid, PlayerBar3D:barid) {
    if(!IsValidPlayerProgressBar3D(playerid, barid)) {
        return _:INVALID_PLAYER_3D_BAR;
    }

    PlayerBars3D[playerid][_:barid][barColor] = -1;
    PlayerBars3D[playerid][_:barid][barShown] = false;
    PlayerBars3D[playerid][_:barid][maxValue] = -1;
    PlayerBars3D[playerid][_:barid][barValue] = -1;

    DestroyDynamic3DTextLabel(PlayerBars3D[playerid][_:barid][Bar1]);
    DestroyDynamic3DTextLabel(PlayerBars3D[playerid][_:barid][Bar2]);

    if(PlayerBars3D[playerid][_:barid][barBorders]) {
        PlayerBars3D[playerid][_:barid][barBorders] = false;
        DestroyDynamic3DTextLabel(PlayerBars3D[playerid][_:barid][BgBar1]);
        DestroyDynamic3DTextLabel(PlayerBars3D[playerid][_:barid][BgBar2]);
    }

    Iter_Remove(PlayerBars3D_Index[playerid], _:barid);
    return 1;
}

stock Float:GetPlayerProgressBar3DValue(playerid, PlayerBar3D:barid) {
    if(!IsValidPlayerProgressBar3D(playerid, barid)) {
        return Float:INVALID_PLAYER_3D_BAR;
    }
    return PlayerBars3D[playerid][_:barid][barValue];
}

stock SetPlayerProgressBar3DValue(playerid, PlayerBar3D:barid, Float:value) {
    if(!IsValidPlayerProgressBar3D(playerid, barid)) {
        return _:INVALID_PLAYER_3D_BAR;
    }

    _UpdateProgress3D(_:barid, playerid, BAR_3D_TYPE_PLAYER, PlayerBars3D[playerid][_:barid][barColor], PlayerBars3D[playerid][_:barid][barBorders], PlayerBars3D[playerid][_:barid][barShown], PlayerBars3D[playerid][_:barid][maxValue], value);
    PlayerBars3D[playerid][_:barid][barValue] = value;
    return 1;
}

stock GetPlayerProgressBar3DColor(playerid, PlayerBar3D:barid) {
    if(!IsValidPlayerProgressBar3D(playerid, barid)) {
        return _:INVALID_PLAYER_3D_BAR;
    }
    return PlayerBars3D[playerid][_:barid][barColor];
}

stock SetPlayerProgressBar3DColor(playerid, PlayerBar3D:barid, color) {
    if(!IsValidPlayerProgressBar3D(playerid, barid)) {
        return _:INVALID_PLAYER_3D_BAR;
    }

    _UpdateProgress3D(_:barid, playerid, BAR_3D_TYPE_PLAYER, color, PlayerBars3D[playerid][_:barid][barBorders], PlayerBars3D[playerid][_:barid][barShown], PlayerBars3D[playerid][_:barid][maxValue], PlayerBars3D[playerid][_:barid][barValue]);
    PlayerBars3D[playerid][_:barid][barColor] = color;
    return 1;
}

stock Float:GetPlayerProgressBar3DMaxValue(playerid, PlayerBar3D:barid) {
    if(!IsValidPlayerProgressBar3D(playerid, barid)) {
        return _:INVALID_PLAYER_3D_BAR;
    }
    return PlayerBars3D[playerid][_:barid][maxValue];
}

stock SetPlayerProgressBar3DMaxValue(playerid, PlayerBar3D:barid, Float:max_value) {
    if(!IsValidPlayerProgressBar3D(playerid, barid)) {
        return _:INVALID_PLAYER_3D_BAR;
    }

    if(max_value < PlayerBars3D[playerid][_:barid][barValue]) {
        return 0;
    }

    _UpdateProgress3D(_:barid, playerid, BAR_3D_TYPE_PLAYER, PlayerBars3D[playerid][_:barid][barColor], PlayerBars3D[playerid][_:barid][barBorders], PlayerBars3D[playerid][_:barid][barShown], max_value, PlayerBars3D[playerid][_:barid][barValue]);
    PlayerBars3D[playerid][_:barid][maxValue] = max_value;
    return 1;
}

stock IsValidPlayerProgressBar3D(playerid, PlayerBar3D:barid) {
    return Iter_Contains(PlayerBars3D_Index[playerid], _:barid);
}