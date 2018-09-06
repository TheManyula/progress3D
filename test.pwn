#include <a_samp>
#include <zcmd>
#include <sscanf2>

#include "progress3D"

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

new Bar3D:Bar;

main() {
    print("[DEMO] progress3D by Manyula");
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
    SendClientMessage(playerid, 0xFFFFFFFF, "> COMMANDS <");
    SendClientMessage(playerid, 0xFF0000FF, "/bar {FFFFFF}to create a 3D progress bar.");
    SendClientMessage(playerid, 0xFF0000FF, "/layout {FFFFFF}to change the layout.");
    SendClientMessage(playerid, 0xFF0000FF, " => Please be aware that the 3D progress bar will only become visible, if you move after the creation!");
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

    new Float:pos[3];
    GetPlayerPos(playerid, pos[0], pos[1], pos[2]);
    Bar = CreateProgressBar3D(BAR_3D_LAYOUT_NORMAL, 0xFF0000FF, 0xFFFFFFFF, 100.0, 50.0, pos[0], pos[1], pos[2], 100.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, -1, -1, -1, STREAMER_3D_TEXT_LABEL_SD, -1);
    return 1;
}

CMD:layout(playerid, params[]) {
    new layout = GetProgressBar3DLayout(Bar);

    if(layout < 2) {
        layout++;
    } else {
        layout = 0;
    }

    SetProgressBar3DLayout(Bar, layout);
    return 1;
}

CMD:value(playerid, params[]) {
    new Float:value;
    if(sscanf(params, "f", value)) {
        SendClientMessage(playerid, -1, "[USAGE] /value <number>");
        return 1;
    }

    SetProgressBar3DValue(Bar, value);
    return 1;
}

CMD:max(playerid, params[]) {
    new Float:value;
    if(sscanf(params, "f", value)) {
        SendClientMessage(playerid, -1, "[USAGE] /setmax <number>");
        return 1;
    }

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