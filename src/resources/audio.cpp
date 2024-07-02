#include "audio.hpp"
#include "../move/move.hpp"

void InitSounds() {
    InitAudioDevice();
    Move::moveSound = LoadSound("../Sounds/move.mp3");
    Move::captureSound = LoadSound("../Sounds/capture.mp3");
    Move::checkSound = LoadSound("../Sounds/move-check.mp3");
}

void UnloadSounds() {
    UnloadSound(Move::checkSound);
    UnloadSound(Move::moveSound);
    UnloadSound(Move::captureSound);
    CloseAudioDevice();
}
