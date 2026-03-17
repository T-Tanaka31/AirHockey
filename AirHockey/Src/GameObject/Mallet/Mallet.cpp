#include "Mallet.h"
#include "../../Utility/MathUtility.h"

Mallet::Mallet(VECTOR startPos, float r, float speed, float _minX, float _maxX, float _minY, float _maxY, std::string _tag)
	: GameObject(startPos, _tag)
	, radius(r)
	, moveSpeed(speed)
	, minX(_minX)
	, maxX(_maxX)
	, minY(_minY)
	, maxY(_maxY) {
}

void Mallet::Start() {
}

void Mallet::Update() {
}

void Mallet::Render() {
	DrawCircle((int)position.x, (int)position.y, radius, GetColor(102, 192, 255), TRUE);
}

void Mallet::UpdateByGamepad(int _padID) {
	auto input = InputManager::GetInstance();

	float inputX = input->IsJoypadSthick(_padID, "L_Horizontal");
	float inputY = input->IsJoypadSthick(_padID, "L_Vertical");
	
	position.x += inputX * moveSpeed;
	position.y += inputY * moveSpeed;

	ClampPosition();
}

void Mallet::ClampPosition() {
	position.x = MathUtility::Clamp(position.x, minX + radius, maxX - radius);
	position.y = MathUtility::Clamp(position.y, minY + radius, maxY - radius);

}
