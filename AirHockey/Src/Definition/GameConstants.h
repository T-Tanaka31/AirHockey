#pragma once
#include "TypeDefinition.h"
// このファイルはExcelから自動生成されています。直接書き換えない

namespace GameConfig {
    namespace Puck {
        static constexpr float Radius = 50.0f; // 半径
        static constexpr float Friction = 0.99f; // 摩擦抵抗
        static constexpr float  MaxSpeed = 80.0f; // 最高速度
        static constexpr float PushPower = 10.0f; // 押し出す力
    }
    namespace Mallet {
        static constexpr float Radius = 70.0f; // 半径
        static constexpr float Speed = 30.0f; // 速度
        static constexpr float ReturnDuration = 1.2f; // 初期位置に戻るまでの時間
        static constexpr Area P1Limit = { 0, WINDOW_WIDTH / 2, 0, WINDOW_HEIGHT }; // Player1の移動範囲制限
        static constexpr Area P2Limit = { WINDOW_WIDTH / 2, WINDOW_WIDTH, 0, WINDOW_HEIGHT }; // Player2の移動範囲制限
    }
    namespace Goal {
        static constexpr int Top = 310; // ゴール範囲(上)
        static constexpr int Bottom = 775; // ゴール範囲(下)
        static constexpr int Width = -50; // ゴール範囲(奥)
    }
    namespace Court {
        static constexpr float Left = 0.0f; // コート範囲(左)
        static constexpr float Right = WINDOW_WIDTH; // コート範囲(右)
        static constexpr float Top = 0.0f; // コート範囲(上)
        static constexpr float Bottom = WINDOW_HEIGHT; // コート範囲(下)
    }
    namespace PuckSpawn {
        static constexpr float SpawnY = -100.0f; // 落下開始位置(画面外上)
        static constexpr float TargetY = WINDOW_HEIGHT / 2; // ターゲット位置
        static constexpr float ReturnDuration = 4.8f; // パックが新しく出るまでの時間
    }
    namespace Score {
        static constexpr int WinScore = 7; // 勝利得点
    }
}
