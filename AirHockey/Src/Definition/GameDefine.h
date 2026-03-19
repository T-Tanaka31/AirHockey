#pragma once
#include <DxLib.h>

namespace GameConfig {
	//	パック
	namespace Puck {
		static constexpr float Radius = 50.0f;		//	半径
		static constexpr float Friction = 0.995f;	//	摩擦抵抗
		static constexpr float MaxSpeed = 80.0f;	//	最高速度
		static constexpr float PushPower = 6.0f;	//	押し出す力

		const VECTOR StartPos = VGet(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2, 0);	//	初期位置
	}

	//	マレット
	namespace Mallet {
		static constexpr float Radius = 70.0f;	//	半径
		static constexpr float Speed = 25.0f;	//	速度

		const VECTOR Player1StartPos = VGet(320.0f, 840.0f, 0.0f);	//	Player1の初期位置
		const VECTOR Player2StartPos = VGet(1600.0f, 240.0f, 0.0f);	//	Player2の初期位置

		struct Area {
			float minX, maxX, minY, maxY;	//	移動範囲制限
		};

		static constexpr Area P1Limit = { 0, WINDOW_WIDTH / 2, 0, WINDOW_HEIGHT };				//	Player1の移動範囲制限
		static constexpr Area P2Limit = { WINDOW_WIDTH / 2, WINDOW_WIDTH, 0, WINDOW_HEIGHT };	//	Player2の移動範囲制限
	}

	//	ゴール
	namespace Goal {
		static constexpr int Top = 310;		//	ゴール範囲(上)
		static constexpr int Bottom = 775;	//	ゴール範囲(下)
		static constexpr int Width = -80;	//	ゴール範囲(奥)
	}

	//	コート
	namespace Court {
		static constexpr float Left = 0.0f;				//	コート範囲(左)
		static constexpr float Right = WINDOW_WIDTH;	//	コート範囲(右)
		static constexpr float Top = 0.0f;				//	コート範囲(上)
		static constexpr float Bottom = WINDOW_HEIGHT;	//	コート範囲(下)

		//	コート内かどうか
		inline bool IsInside(const VECTOR& pos) {
			return (pos.x >= Left &&
					pos.x <= Right &&
					pos.y >= Top &&
					pos.y <= Bottom);
		}
	}

	//	パック出現
	namespace PuckSpawn {

		static constexpr float SpawnY = -100.0f;	//	落下開始位置(画面外上)

		static constexpr float TargetY = WINDOW_HEIGHT * 0.5f;	//	ターゲット位置

		// 左側コート
		inline VECTOR LeftSpawn() {
			return VGet(WINDOW_WIDTH * 0.45f, SpawnY, 0);
		}
		inline VECTOR LeftTarget() {
			return VGet(WINDOW_WIDTH * 0.45f, TargetY, 0);
		}

		// 右側コート
		inline VECTOR RightSpawn() {
			return VGet(WINDOW_WIDTH * 0.55f, SpawnY, 0);
		}
		inline VECTOR RightTarget() {
			return VGet(WINDOW_WIDTH * 0.55f, TargetY, 0);
		}
	}

	namespace Score {
		static constexpr int WinScore = 10;
	}

}