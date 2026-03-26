#pragma once
#include <string>
// このファイルはExcelから自動生成されています。直接書き換えない

struct AudioData {
    std::string fullPath;
    std::string name;
    bool is3D;
};

const AudioData AudioList[] = {
    {"Res/Audio/Hit.mp3", "Hit", false},
    {"Res/Audio/Goal.mp3", "Goal", false},
};

const int AudioCount = sizeof(AudioList) / sizeof(AudioData);
