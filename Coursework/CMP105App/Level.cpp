#include "Level.h"

Level::Level(sf::RenderWindow& hwnd, Input& in) :
	BaseLevel(hwnd, in)
{

	if (!m_sheepTexture.loadFromFile("gfx/sheep_sheet.png"))
		std::cerr << "No Sheep Texture\n";

	m_sheep.setTexture(&m_sheepTexture);
	//m_sheep.setTextureRect(sf::IntRect({ 0,0 }, { 64,64 }));

	m_sheep.setPosition({ 10,10 });
	m_sheep.setSize({ 64,64 });
	m_sheep.setInput(&m_input);
}

// handle user input
void Level::handleInput(float dt)
{
	if (m_gameOver) return;

	m_sheep.handleInput(dt);
}

// Update game objects
void Level::update(float dt)
{
	if (m_gameOver) return;

	// check wall collision
	sf::Vector2f pos = m_sheep.getPosition();
	float width = m_sheep.getSize().x/2;
	float height = m_sheep.getSize().y/2;

	if (pos.x < 0 || pos.x + width > m_window.getSize().x || pos.y < 0 || pos.y + height > m_window.getSize().y)
	{
		m_gameOver = true;
		std::cout << "Game over";
	}

	m_sheep.update(dt);

}

// Render level
void Level::render()
{
	beginDraw();
	m_window.draw(m_sheep);
	endDraw();
}

