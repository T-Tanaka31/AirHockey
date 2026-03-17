#pragma once
#include <DxLib.h>
#define VRight   (VGet(1.0f,0.0f,0.0f))
#define VLeft    (VGet(-1.0f,0.0f,0.0f))
#define VUp      (VGet(0.0f,1.0f,0.0f))
#define VDown    (VGet(0.0f,-1.0f,0.0f))
#define VForward (VGet(0.0f,0.0f,1.0f))
#define VBack    (VGet(0.0f,0.0f,-1.0f))

#define VZero (VGet(0.0f,0.0f,0.0f))
#define VOne  (VGet(1.0f,1.0f,1.0f))

//	プレイヤーの開始位置
#define PLAYER1_START_POS (VGet(320.0f, 240.0f, 0.0f))
#define PLAYER2_START_POS (VGet(1600.0f, 240.0f, 0.0f))

//	マレット移動制限
#define P1_MIN_X (0)
#define P1_MAX_X (WINDOW_WIDTH / 2)
#define P1_MIN_Y (0)
#define P1_MAX_Y (WINDOW_HEIGHT)

#define P2_MIN_X (WINDOW_WIDTH / 2)
#define P2_MAX_X (WINDOW_WIDTH)
#define P2_MIN_Y (0)
#define P2_MAX_Y (WINDOW_HEIGHT)
