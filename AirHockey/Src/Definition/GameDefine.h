#pragma once
#include <DxLib.h>

namespace GameConfig {
	namespace Puck {
		static constexpr float Radius = 50.0f;
		static constexpr float Friction = 0.995f;
		static constexpr float MaxSpeed = 50.0f;

		const VECTOR StartPos = VGet(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2, 0);
	}

	namespace Mallet {
		static constexpr float Radius = 70.0f;
		static constexpr float Speed = 25.0f;

		const VECTOR Player1StartPos = VGet(320.0f, 840.0f, 0.0f);
		const VECTOR Player2StartPos = VGet(1600.0f, 240.0f, 0.0f);

		struct Area {
			float minX, maxX, minY, maxY;
		};

		static const Area P1Limit = { 0, WINDOW_WIDTH / 2, 0, WINDOW_HEIGHT };
		static constexpr Area P2Limit = { WINDOW_WIDTH / 2, WINDOW_WIDTH, 0, WINDOW_HEIGHT };
	}

	namespace Goal {
		static constexpr int Top = 310;
		static constexpr int Bottom = 775;
		static constexpr int Width = -80;
	}
}