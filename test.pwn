#include <a_samp>
#include <zcmd>
#include <sscanf2>

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

static Bar3D:Bar;

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
    SendClientMessage(playerid, 0xFF0000FF, "/bar <0 or 1> (0: no borders, 1: with borders) {FFFFFF}to create a 3D progress bar. (only visible if you move after the creation)");
    SendClientMessage(playerid, 0xFF0000FF, "/value <float> {FFFFFF}to change the value.");
    SendClientMessage(playerid, 0xFF0000FF, "/max <float> {FFFFFF}to change the maximum value.");
    SendClientMessage(playerid, 0xFF0000FF, "/color {FFFFFF}to change the color randomly.");
    return 1;
}

CMD:bar(playerid, params[]) {
    if(IsValidProgressBar3D(Bar)) {
        DestroyProgressBar3D(Bar);
    }

    new option = 0;
    if(sscanf(params, "i", option)) {
        return SendClientMessage(playerid, -1, "USAGE: /bar <0 or 1> (0: no borders, 1: with borders)");
    }
    if(option != 0 && option != 1) {
        return SendClientMessage(playerid, -1, "USAGE: /bar <0 or 1> (0: no borders, 1: with borders)");
    }

    new Float:x,
        Float:y,
        Float:z;
    
    GetPlayerPos(playerid, x, y, z);
    Bar = CreateProgressBar3D(Colors[random(sizeof(Colors))], (option == 0) ? (false) : (true), x, y, z, 100.0, 50.0, 100.0);
    return 1;
}

CMD:hide(playerid, params[]) {
    HideProgressBar3D(Bar);
    return 1;
}

CMD:show(playerid, params[]) {
    ShowProgressBar3D(Bar);
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

CMD:max(playerid, params[]) {
    new Float:value;
    if(sscanf(params, "f", value)) {
        return SendClientMessage(playerid, -1, "USAGE: /max <float>");
    }
    SetProgressBar3DMaxValue(Bar, value);
    return 1;
}

CMD:color(playerid, params[]) {
    SetProgressBar3DColor(Bar, Colors[random(sizeof(Colors))]);
    return 1;
}
