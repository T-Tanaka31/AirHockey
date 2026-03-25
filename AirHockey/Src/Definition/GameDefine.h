#pragma once
#include <DxLib.h>
#include "GameConstants.h"

namespace GameConfig {
	//	マレット
	namespace Mallet {
		const VECTOR Player1StartPos = VGet(280.0f, 880.0f, 0.0f);	//	Player1の初期位置
		const VECTOR Player2StartPos = VGet(1640.0f, 200.0f, 0.0f);	//	Player2の初期位置
	}
	//	パック
	namespace Puck {
		static const VECTOR StartPos = VGet(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2, 0);	//	初期位置
	}

	//	コート
	namespace Court {
		//	コート内かどうか
		inline bool IsInside(const VECTOR& pos) {
			return (pos.x >= Left &&
				pos.x <= Right &&
				pos.y >= Top &&
				pos.y <= Bottom);
		}

		static const VECTOR HalfCourt = VGet(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2, 0);
	}

	//	パック出現
	namespace PuckSpawn {
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
}