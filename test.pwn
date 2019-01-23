#include <a_samp>
#include <zcmd>
#include <sscanf2>

#include "progress3D"

#define FILL_COLOR          0xFF0000FF
#define BACKGROUND_COLOR    0xFFFFFFFF

static const Colors[8] = {
    0x000000FF,
    0x0000FFFF,
    0x00FF00FF,
    0x00FFFFFF,
    0xFF0000FF,
    0xFF00FFFF,
    0xFFFF00FF,
    0xFFFFFFFF
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
    SendClientMessage(playerid, 0xFFFFFFFF, " ");
    SendClientMessage(playerid, 0xFFFFFFFF, " ");
    SendClientMessage(playerid, 0xFFFFFFFF, "============================== COMMANDS ==============================");
    SendClientMessage(playerid, 0xFF0000FF, "/bar {FFFFFF}to create a 3D progress bar.");
    SendClientMessage(playerid, 0xFF0000FF, " => Please be aware that the 3D progress bar will only become visible, if you move after the creation!");
    SendClientMessage(playerid, 0xFF0000FF, "/layout {FFFFFF}to change the layout.");
    SendClientMessage(playerid, 0xFF0000FF, "/value <number> {FFFFFF}to change the value.");
    SendClientMessage(playerid, 0xFF0000FF, "/max <number> {FFFFFF}to change the maximum value.");
    SendClientMessage(playerid, 0xFF0000FF, "/fill {FFFFFF}to change the fill color randomly.");
    SendClientMessage(playerid, 0xFF0000FF, "/background {FFFFFF}to change the background color randomly.");
    return 1;
}

CMD:bar(playerid, params[]) {
    if(IsValidProgressBar3D(Bar)) {
        DestroyProgressBar3D(Bar);
    }

    new Float:x,
        Float:y,
        Float:z;
    
    GetPlayerPos(playerid, x, y, z);
    Bar = CreateProgressBar3D(x, y, z, BAR_3D_LAYOUT_NORMAL, FILL_COLOR, BACKGROUND_COLOR, 100.0, 50.0, 100.0);
    return 1;
}

CMD:layout(playerid, params[]) {
    new layout = GetProgressBar3DLayout(Bar);
    SetProgressBar3DLayout(Bar, (layout < BAR_3D_LAYOUT_THICK) ? (layout + 1) : (BAR_3D_LAYOUT_THIN));
    return 1;
}

CMD:value(playerid, params[]) {
    new Float:value;

    if(sscanf(params, "f", value))
        return SendClientMessage(playerid, -1, "[USAGE] /value <number>");

    SetProgressBar3DValue(Bar, value);
    return 1;
}

CMD:max(playerid, params[]) {
    new Float:value;

    if(sscanf(params, "f", value))
        return SendClientMessage(playerid, -1, "[USAGE] /setmax <number>");

    SetProgressBar3DMaxValue(Bar, value);
    return 1;
}

CMD:fill(playerid, params[]) {
    SetProgressBar3DFillColor(Bar, Colors[random(sizeof(Colors))]);
    return 1;
}

CMD:background(playerid, params[]) {
    SetProgressBar3DBackgroundColor(Bar, Colors[random(sizeof(Colors))]);
    return 1;
}