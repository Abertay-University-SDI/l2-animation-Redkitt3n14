#include "Sheep.h"
#include "Framework/animation.h"

Sheep::Sheep()
{
	//initialise animations
	// walk down
	for (int i = 0; i < 4; i++) {
		m_walkDown.addFrame({ { 64 * i,0 }, { 64, 64 } });
		m_walkUp.addFrame({ { 64 * i + 256,0 }, { 64, 64 } });
		m_walkUpRight.addFrame({ { 64 * i,64 }, { 64, 64 } });
		m_walkRight.addFrame({ { 64 * i + 256,64 }, { 64, 64 } });
		m_walkDownRight.addFrame({ { 64 * i,128 }, { 64, 64 } });
	}
	m_walkDown.setLooping(true);
	m_walkDown.setFrameSpeed(0.2f);
	m_walkUp.setLooping(true);
	m_walkUp.setFrameSpeed(0.2f);
	m_walkRight.setLooping(true);
	m_walkRight.setFrameSpeed(0.2f);
	m_walkUpRight.setLooping(true);
	m_walkUpRight.setFrameSpeed(0.2f);
	m_walkDownRight.setLooping(true);
	m_walkDownRight.setFrameSpeed(0.2f);

	// makes the flipped variants
	m_walkLeft = m_walkRight;
	m_walkDownLeft = m_walkDownRight; 
	m_walkUpLeft = m_walkUpRight;
	m_walkLeft.setFlipped(true);
	m_walkDownLeft.setFlipped(true);
	m_walkUpLeft.setFlipped(true);
	
	m_currentAnimation = &m_walkDown;
	setTextureRect(m_currentAnimation->getCurrentFrame());
}

void Sheep::update(float dt)
{
	setTextureRect(m_currentAnimation->getCurrentFrame());
	m_currentAnimation->animate(dt);

	// set sheep direction
	
	// for diagonal movement
	float diagonal_speed = m_speed * APPROX_ONE_OVER_ROOT_TWO * dt;
	float orthog_speed = m_speed * dt;	// orthogonal movement

	switch (m_direction)
	{
	case Direction::UP:
		move({ 0, -orthog_speed });
		m_currentAnimation = &m_walkUp;
		break;
	case Direction::UP_RIGHT:
		move({ diagonal_speed, -diagonal_speed });
		m_currentAnimation = &m_walkUpRight;
		break;
	case Direction::RIGHT:
		move({ orthog_speed,0 });
		m_currentAnimation = &m_walkRight;
		break;
	case Direction::DOWN_RIGHT:
		move({ diagonal_speed, diagonal_speed });
		m_currentAnimation = &m_walkDownRight;
		break;
	case Direction::DOWN:
		move({ 0, orthog_speed });
		m_currentAnimation = &m_walkDown;
		break;
	case Direction::DOWN_LEFT:
		move({ -diagonal_speed, diagonal_speed });
		m_currentAnimation = &m_walkDownLeft;
		break;
	case Direction::LEFT:
		move({ -orthog_speed,0 });
		m_currentAnimation = &m_walkLeft;
		break;
	case Direction::UP_LEFT:
		move({ -diagonal_speed, -diagonal_speed });
		m_currentAnimation = &m_walkUpLeft;
		break;
	}
}

void Sheep::handleInput(float dt)
{
	// move the sheep
	// 
	// decrement and check the input buffer.
	m_inputBuffer -= dt;
	if (m_inputBuffer > 0)
	{
		// not long enough has passed since the last input change, so don't handle input
		return;
	}
	// grab this to detect changes per frame for later
	Direction last_dir = m_direction;

	// Set 8-directional movement based on WASD
	if (m_input->isKeyDown(sf::Keyboard::Scancode::A))
	{
		if (m_input->isKeyDown(sf::Keyboard::Scancode::W))
			m_direction = Direction::UP_LEFT;
		else if (m_input->isKeyDown(sf::Keyboard::Scancode::S))
			m_direction = Direction::DOWN_LEFT;
		else
			m_direction = Direction::LEFT;
	}
	else if (m_input->isKeyDown(sf::Keyboard::Scancode::D))
	{
		if (m_input->isKeyDown(sf::Keyboard::Scancode::W))
			m_direction = Direction::UP_RIGHT;
		else if (m_input->isKeyDown(sf::Keyboard::Scancode::S))
			m_direction = Direction::DOWN_RIGHT;
		else
			m_direction = Direction::RIGHT;
	}
	else
	{
		if (m_input->isKeyDown(sf::Keyboard::Scancode::W))
			m_direction = Direction::UP;
		else if (m_input->isKeyDown(sf::Keyboard::Scancode::S))
			m_direction = Direction::DOWN;
	}

	// set input buffer if needed, this makes diagonal movement easier
	if (m_direction != last_dir)
		m_inputBuffer = INPUT_BUFFER_LENGTH;
}
