#pragma once

enum class GameState {
	Title,
	Playing,
	Paused,
	Result
};

enum class FadeState {
	FadeIn = -1,
	FadeOut = 1,
	FadeEnd,
};