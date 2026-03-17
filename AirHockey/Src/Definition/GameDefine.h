#pragma once
//==============================
// パック関連
//==============================
//	パックの半径
#define PUCK_RADIUS (50.0f)
//	パックの開始位置
#define PUCK_START_POS (VGet(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2, 0))
//	パックの摩擦
#define PUCK_FRICTION (0.995f)
//	パックの最大速度
#define PUCK_MAX_SPEED (50.0f)

//==============================
// マレット関連
//==============================
//	マレットの半径
#define MALLET_RADIUS (70.0f)
//	マレットの速度
#define MALLET_SPEED (25.0f)
//	マレットの開始位置
#define PLAYER1_START_POS (VGet(320.0f, 240.0f, 0.0f))
#define PLAYER2_START_POS (VGet(1600.0f, 240.0f, 0.0f))

//==============================
// マレット移動制限
//==============================
#define P1_MIN_X (0)
#define P1_MAX_X (WINDOW_WIDTH / 2)
#define P1_MIN_Y (0)
#define P1_MAX_Y (WINDOW_HEIGHT)

#define P2_MIN_X (WINDOW_WIDTH / 2)
#define P2_MAX_X (WINDOW_WIDTH)
#define P2_MIN_Y (0)
#define P2_MAX_Y (WINDOW_HEIGHT)

//==============================
// ゴール関連
//==============================
//	ゴール判定
#define GOAL_TOP (380)
#define GOAL_BOTTOM (780)
#define GOAL_WIDTH (-80)


