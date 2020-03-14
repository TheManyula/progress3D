#include <a_samp>
#include <zcmd>
#include <sscanf2>
#include <YSI_Coding\y_timers>

#include "progress3D"

static const Colors[7] = {
    0x0000FFFF, // Blue
    0x00FF00FF, // Green
    0x00FFFFFF, // Cyan
    0xFF0000FF, // Red
    0xFF00FFFF, // Purple
    0xFFFF00FF, // Yellow
    0xFFFFFFFF // White
};

static Bar3D:Bar,
       PlayerBar3D:PlayerBar,
       bool:toggle,
       Timer:update,
       Timer:pupdate;

main() {
    print("\n+-----------------------------------+");
    print("| progress3D demo script by Manyula |");
    print("+-----------------------------------+\n");
}

public OnGameModeInit() {
    SetGameModeText("progress3D");
    AddPlayerClass(0, 1958.3783, 1343.1572, 15.3746, 269.1425, 0, 0, 0, 0, 0, 0);
    return 1;
}

public OnPlayerRequestClass(playerid, classid) {
    SetPlayerPos(playerid, 1958.3783, 1343.1572, 15.3746);
    SetPlayerCameraPos(playerid, 1958.3783, 1343.1572, 15.3746);
    SetPlayerCameraLookAt(playerid, 1958.3783, 1343.1572, 15.3746);
    return 1;
}

public OnPlayerSpawn(playerid) {
    SendClientMessage(playerid, 0xFF0000FF, "/(p)bar <0 or 1> <0 or 1> {FFFFFF}to create a 3D progress bar. (only visible if you move after the creation)");
    SendClientMessage(playerid, 0xFF0000FF, "  1. Auto-Fill Mode (0: disable, 1: enable)");
    SendClientMessage(playerid, 0xFF0000FF, "  2. Borders (0: disable, 1: enable)");
    SendClientMessage(playerid, 0xFF0000FF, "/(p)value <float> {FFFFFF}to change the value.");
    SendClientMessage(playerid, 0xFF0000FF, "/(p)max <float> {FFFFFF}to change the maximum value.");
    SendClientMessage(playerid, 0xFF0000FF, "/(p)color {FFFFFF}to change the color randomly.");
    return 1;
}

timer Update[100]() {
    new Float:currentValue = GetProgressBar3DValue(Bar);
    if(currentValue <= 0.0) {
        toggle = true;
    } else if(currentValue >= 100.0) {
        toggle = false;
    }

    if(toggle) {
        SetProgressBar3DValue(Bar, currentValue+2.0);
    } else {
        SetProgressBar3DValue(Bar, currentValue-2.0);
    }
}

timer pUpdate[100](playerid) {
    new Float:currentValue = GetPlayerProgressBar3DValue(playerid, PlayerBar);
    if(currentValue <= 0.0) {
        toggle = true;
    } else if(currentValue >= 100.0) {
        toggle = false;
    }

    if(toggle) {
        SetPlayerProgressBar3DValue(playerid, PlayerBar, currentValue+2.0);
    } else {
        SetPlayerProgressBar3DValue(playerid, PlayerBar, currentValue-2.0);
    }
}

CMD:bar(playerid, params[]) {
    new autofill, borders;
    if(sscanf(params, "ii", autofill, borders)) {
        return SendClientMessage(playerid, -1, "USAGE: /bar <0 or 1> (0: auto on, 1: auto off) <0 or 1> (0: no borders, 1: with borders)");
    } else if(autofill != 0 && autofill != 1) {
        return SendClientMessage(playerid, -1, "USAGE: /bar <0 or 1> (0: auto on, 1: auto off) <0 or 1> (0: no borders, 1: with borders)");
    } else if(borders != 0 && borders != 1) {
        return SendClientMessage(playerid, -1, "USAGE: /bar <0 or 1> (0: auto on, 1: auto off) <0 or 1> (0: no borders, 1: with borders)");
    }

    if(IsValidProgressBar3D(Bar)) {
        stop update;
        DestroyProgressBar3D(Bar);
    }

    new Float:x, Float:y, Float:z;
    GetPlayerPos(playerid, x, y, z);
    Bar = CreateProgressBar3D(Colors[random(sizeof(Colors))], (borders == 0) ? (false) : (true), x, y, z, 100.0, 50.0, 100.0);
    update = repeat Update();
    return 1;
}

CMD:pbar(playerid, params[]) {
    new autofill, borders;
    if(sscanf(params, "ii", autofill, borders)) {
        return SendClientMessage(playerid, -1, "USAGE: /bar <0 or 1> (0: auto on, 1: auto off) <0 or 1> (0: no borders, 1: with borders)");
    } else if(autofill != 0 && autofill != 1) {
        return SendClientMessage(playerid, -1, "USAGE: /bar <0 or 1> (0: auto on, 1: auto off) <0 or 1> (0: no borders, 1: with borders)");
    } else if(borders != 0 && borders != 1) {
        return SendClientMessage(playerid, -1, "USAGE: /bar <0 or 1> (0: auto on, 1: auto off) <0 or 1> (0: no borders, 1: with borders)");
    }

    if(IsValidPlayerProgressBar3D(PlayerBar)) {
        stop pupdate;
        DestroyPlayerProgressBar3D(playerid, PlayerBar);
    }

    new Float:x, Float:y, Float:z;
    GetPlayerPos(playerid, x, y, z);
    PlayerBar = CreatePlayerProgressBar3D(playerid, Colors[random(sizeof(Colors))], (borders == 0) ? (false) : (true), x, y, z, 100.0, 50.0, 100.0);
    pupdate = repeat pUpdate(playerid);
    return 1;
}

CMD:hide(playerid, params[]) {
    HideProgressBar3D(Bar);
    return 1;
}

CMD:phide(playerid, params[]) {
    HidePlayerProgressBar3D(playerid, PlayerBar);
    return 1;
}

CMD:show(playerid, params[]) {
    ShowProgressBar3D(Bar);
    return 1;
}

CMD:pshow(playerid, params[]) {
    ShowPlayerProgressBar3D(playerid, PlayerBar);
    return 1;
}

CMD:value(playerid, params[]) {
    new Float:value;
    if(sscanf(params, "f", value)) {
        return SendClientMessage(playerid, -1, "USAGE: /value <float>");
    }
    SetProgressBar3DValue(Bar, value);
    return 1;
}

CMD:pvalue(playerid, params[]) {
    new Float:value;
    if(sscanf(params, "f", value)) {
        return SendClientMessage(playerid, -1, "USAGE: /value <float>");
    }
    SetPlayerProgressBar3DValue(playerid, PlayerBar, value);
    return 1;
}

CMD:max(playerid, params[]) {
    new Float:value;
    if(sscanf(params, "f", value)) {
        return SendClientMessage(playerid, -1, "USAGE: /max <float>");
    }
    SetProgressBar3DMaxValue(Bar, value);
    return 1;
}

CMD:pmax(playerid, params[]) {
    new Float:value;
    if(sscanf(params, "f", value)) {
        return SendClientMessage(playerid, -1, "USAGE: /max <float>");
    }
    SetPlayerProgressBar3DMaxValue(playerid, PlayerBar, value);
    return 1;
}

CMD:color(playerid, params[]) {
    SetProgressBar3DColor(Bar, Colors[random(sizeof(Colors))]);
    return 1;
}

CMD:pcolor(playerid, params[]) {
    SetPlayerProgressBar3DColor(playerid, PlayerBar, Colors[random(sizeof(Colors))]);
    return 1;
}
