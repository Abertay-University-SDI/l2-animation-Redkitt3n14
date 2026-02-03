#pragma once
#include "Framework/GameObject.h"
#include "Framework/Animation.h"

class Sheep : public GameObject
{

public:
	Sheep();
	~Sheep() = default;

	void update(float dt) override;
	void handleInput(float dt) override;


private:
	// Sheep member variables here
	enum class Direction { UP, DOWN, LEFT, RIGHT, UP_RIGHT, DOWN_RIGHT, DOWN_LEFT, UP_LEFT, NONE };
	Direction m_direction = Direction::NONE;
	float m_speed = 300.0f;
	float m_inputBuffer = 0.f;

	const float INPUT_BUFFER_LENGTH = 0.1f;
	const float APPROX_ONE_OVER_ROOT_TWO = 0.70710678f;	// 1 / sqrt(2)

	// animations
	Animation* m_currentAnimation;

	Animation m_walkDown;
	Animation m_walkUp;

	Animation m_walkRight;

	Animation m_walkUpRight;
	Animation m_walkDownRight;

	Animation m_walkLeft;

	Animation m_walkUpLeft;
	Animation m_walkDownLeft;

};