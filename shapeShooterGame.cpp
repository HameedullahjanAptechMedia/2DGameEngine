#include "shapeShooterGame.h"
#include <fstream>
#include <iostream>
#include "EntityManager.h"

shapeShooterGame::shapeShooterGame(const std::string& config)
{
	init(config);
}

void shapeShooterGame::init(const std::string& config)
{
    std::ifstream inFile;
    inFile.open(config);

    Window window;
    Font font;
    Player player;
    Enemy enemy;
    Bullet bullet;

    inFile >> window.name >> window.width >> window.height >> window.fps >> window.vsync;
    inFile >> font.name >> font.path >> font.size >> font.r >> font.g >> font.b;
    inFile >> player.name >> player.shapeRadius >> player.collisionRadius >> player.speed >> player.jump_height >> player.gravity;
    inFile >> player.health >> player.r >> player.g >> player.b >> player.damage >> player.s;
    inFile >> enemy.name >> enemy.shapeRadius >> enemy.collisionRadius >> enemy.speed >> enemy.health >> enemy.r >> enemy.g >> enemy.b;
    inFile >> enemy.damage >> enemy.cooldown >> enemy.aggro_range >> enemy.smin >> enemy.smax;
    inFile >> bullet.name >> bullet.width >> bullet.height >> bullet.speed >> bullet.r >> bullet.g >> bullet.b;
    inFile >> bullet.damage >> bullet.duration >> bullet.range >> bullet.angle>>bullet.L>>bullet.S;

    inFile.close();

    std::cout << window.name << " " << window.width << " " << window.height << " " << window.fps << " " << window.vsync << " " << std::endl;

    std::cout << font.name << " " << font.path << " " << font.size << " " << font.r << " " << font.g << " " << font.b <<std::endl;

    std::cout << player.name << " " << player.shapeRadius << " " << player.collisionRadius << " " << player.speed << " " << player.jump_height << " " << player.gravity
        << " " << player.health << " " << player.r << " " << player.g << " " << player.b << " " << player.damage << " " << player.s << std::endl;

    std::cout << enemy.name << " " << enemy.shapeRadius << " " << enemy.collisionRadius << " " << enemy.speed << " " << enemy.health << " " << enemy.r << " " << enemy.g << " " << enemy.b
        << " " << enemy.damage << " " << enemy.cooldown << " " << enemy.aggro_range << " " << enemy.smin << " " << enemy.smax<<std::endl;

    std::cout << bullet.name << " " << bullet.width << " " << bullet.height << " " << bullet.speed << " " << bullet.r << " " << bullet.g << " " << bullet.b
        << " " << bullet.damage << " " << bullet.duration << " " << bullet.range << " " << bullet.angle << " " << bullet.L << " " << bullet.S << std::endl;

	m_window.create(sf::VideoMode(1280, 720), "Shape Shooter");
	m_window.setFramerateLimit(60);
	spawnPlayer();
}

void shapeShooterGame::setPaused(bool paused)
{
}

void shapeShooterGame::sMovement()
{
    if (m_player->cInput->up) {
        m_player->cTransform->velocity.y = -5;
    }
}

void shapeShooterGame::sUserInput()
{
     sf::Event event;
        while (m_window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                m_running = false;
            }
            if (event.type == sf::Event::KeyPressed)
            {
                switch (event.key.code)
                {
                case sf::Keyboard::W:
                    std::cout << "W key pressed\n";
                    m_player->cInput->up = true;
                    break;
                case sf::Keyboard::A:
                    std::cout << "A key pressed\n";
                    break;
                case sf::Keyboard::S:
                    std::cout << "S key pressed\n";
                    break;
                case sf::Keyboard::D:
                    std::cout << "D key pressed\n";
                    break;
                default:
                    break;
                }
            }
            if (event.type == sf::Event::KeyReleased)
            {
                switch (event.key.code)
                {
                case sf::Keyboard::W:
                    std::cout << "W key released\n";
                    m_player->cInput->up = false;
                    break;
                case sf::Keyboard::A:
                    std::cout << "A key released\n";
                    break;
                case sf::Keyboard::S:
                    std::cout << "S key released\n";
                    break;
                case sf::Keyboard::D:
                    std::cout << "D key released\n";
                    break;
                default:
                    break;
                }
            }

            if (event.type == sf::Event::MouseButtonPressed)
            {
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    std::cout << "left mouse button clicked";
                    // call spawn bullet here
                }
                if (event.mouseButton.button == sf::Mouse::Right)
                {
                    std::cout << "right mouse button clicked";
                }
            }
         
        }
}

void shapeShooterGame::sLifespan()
{
}

void shapeShooterGame::sRender()
{
    m_window.clear();
    for (auto e : m_entities.getEntities()) {
        e->cShape->circle.setPosition(e->cTransform->pos.x, e->cTransform->pos.y);
        e->cTransform->angle += 1.0f;
        e->cShape->circle.setRotation(e->cTransform->angle);
        m_window.draw(e->cShape->circle);
    }
    m_window.display();
}

void shapeShooterGame::sEnemySpawner()
{
}

void shapeShooterGame::sCollision()
{
}

void shapeShooterGame::spawnPlayer()
{
    auto entity = m_entities.addEntity("player");
    entity->cTransform = std::make_shared<CTransform>(Vec2(200.0f, 200.0f), Vec2(1.0f, 1.0f), 0.0f);
    entity->cShape = std::make_shared<CShape>(32.0f, 8, sf::Color(10, 10, 10), sf::Color(255, 0, 0),4.0f);
    m_player = entity; // assign this entity to player for easily accessing the player

}

void shapeShooterGame::spawnEnemy()
{
}

void shapeShooterGame::spawnSmallEnemies(std::shared_ptr<Entity> entity)
{
}

void shapeShooterGame::spawnBullet(std::shared_ptr<Entity> entity, const Vec2& mousePos)
{
}

void shapeShooterGame::spawnSpecialWeapon(std::shared_ptr<Entity> entity)
{
}



void shapeShooterGame::run()
{
    while (m_running)
    {
       
        m_entities.update();
        sEnemySpawner();
        sMovement();
        sCollision();
        sUserInput();
        sRender();
        m_currentFrame++;
    }
}
