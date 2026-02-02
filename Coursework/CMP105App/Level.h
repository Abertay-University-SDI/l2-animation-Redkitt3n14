#pragma once

#include "Framework/BaseLevel.h"
#include "Framework/GameObject.h"
#include "Sheep.h"

class Level : BaseLevel {
public:
	Level(sf::RenderWindow& window, Input& input);
	~Level() override = default;

	void handleInput(float dt) override;
	void update(float dt);
	void render();

private:
	// Default functions for rendering to the screen.

	// Default variables for level class.
	bool m_gameOver = false;

	// sheep object
	sf::Texture m_sheepTexture;
	Sheep m_sheep;



};