#pragma once
#include <SFML/Graphics.hpp>
#include "Entity.h"
#include <string>
#include "EntityManager.h"

struct Window {
    std::string name;
    int width;
    int height;
    int fps;
    int vsync;
};

struct Font {
    std::string name;
    std::string path;
    int size;
    int r;
    int g;
    int b;
};

struct Player {
    std::string name;
    int shapeRadius;
    int collisionRadius;
    int speed;
    int jump_height;
    int gravity;
    int health;
    int r;
    int g;
    int b;
    int damage;
    float s;
};

struct Enemy {
    std::string name;
    int shapeRadius;
    int collisionRadius;
    int speed;
    int health;
    int r;
    int g;
    int b;
    int damage;
    int cooldown;
    int aggro_range;
    float smin;
    float smax;
};

struct Bullet {
    std::string name;
    int width;
    int height;
    int speed;
    int r;
    int g;
    int b;
    int damage;
    int duration;
    int range;
    int angle;
    int L;
    float S;
};
class shapeShooterGame
{
	sf::RenderWindow		m_window;
	EntityManager			m_entities;
	sf::Font				m_font;
	sf::Text				m_text;
	Player			        m_playerConfig;
	Enemy				    m_enemyConfig;
	Bullet			        m_bulletConfig;
	int						m_score = 0;
	int						m_currentFrame = 0;
	int						m_lastEnemySpawnTime = 0;
	bool					m_paused = false;
    bool                    m_running = true;
	std::shared_ptr<Entity> m_player;

	void init(const std::string& config);
	void setPaused(bool paused);

	void sMovement();
	void sUserInput();
	void sLifespan();
	void sRender();
	void sEnemySpawner();
	void sCollision();

	void spawnPlayer();
	void spawnEnemy();
	void spawnSmallEnemies(std::shared_ptr<Entity> entity);
	void spawnBullet(std::shared_ptr<Entity> entity, const Vec2& mousePos);
	void spawnSpecialWeapon(std::shared_ptr<Entity> entity);

public:
	shapeShooterGame(const std::string& config);
	void run();
};

