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
    inFile >> player.name >> player.shapeRadius >> player.collisionRadius >> player.sides >> player.shapr_color_r >> player.shape_color_g;
    inFile >> player.shape_color_b >> player.outline_color_r >> player.outline_color_g >> player.outline_color_b >> player.outline_thickness >> player.speed;
    inFile >> enemy.name >> enemy.shapeRadius >> enemy.collisionRadius >> enemy.speed >> enemy.health >> enemy.r >> enemy.g >> enemy.b;
    inFile >> enemy.damage >> enemy.cooldown >> enemy.aggro_range >> enemy.smin >> enemy.smax;
    inFile >> bullet.name >> bullet.width >> bullet.height >> bullet.speed >> bullet.r >> bullet.g >> bullet.b;
    inFile >> bullet.damage >> bullet.duration >> bullet.range >> bullet.angle>>bullet.L>>bullet.S;
    m_playerConfig = player;
    m_enemyConfig = enemy;
    m_bulletConfig = bullet;

    inFile.close();

    std::cout << window.name << " " << window.width << " " << window.height << " " << window.fps << " " << window.vsync << " " << std::endl;

    std::cout << font.name << " " << font.path << " " << font.size << " " << font.r << " " << font.g << " " << font.b <<std::endl;

    std::cout << player.name << " " << player.shapeRadius << " " << player.collisionRadius << " " << player.sides << " " << player.shapr_color_r << " " << player.shape_color_g
        << " " << player.shape_color_b << " " << player.outline_color_r << " " << player.outline_color_g << " " << player.outline_color_b << " " << player.outline_thickness << " " << player.speed << std::endl;

    std::cout << enemy.name << " " << enemy.shapeRadius << " " << enemy.collisionRadius << " " << enemy.speed << " " << enemy.health << " " << enemy.r << " " << enemy.g << " " << enemy.b
        << " " << enemy.damage << " " << enemy.cooldown << " " << enemy.aggro_range << " " << enemy.smin << " " << enemy.smax<<std::endl;

    std::cout << bullet.name << " " << bullet.width << " " << bullet.height << " " << bullet.speed << " " << bullet.r << " " << bullet.g << " " << bullet.b
        << " " << bullet.damage << " " << bullet.duration << " " << bullet.range << " " << bullet.angle << " " << bullet.L << " " << bullet.S << std::endl;

	m_window.create(sf::VideoMode(window.width, window.height), "Shape Shooter");
	m_window.setFramerateLimit(window.fps);
	spawnPlayer();
}

void shapeShooterGame::setPaused(bool paused)
{
}

void shapeShooterGame::sMovement()
{
    /*for (auto e : m_entities.getEntities()) {
        e->cTransform->velocity = {0,0};
    }*/
    m_player->cTransform->velocity = { 0,0 };
   
    if (m_player->cInput->up && m_player->cTransform->pos.y > m_playerConfig.shapeRadius) {
        m_player->cTransform->velocity.y = -m_playerConfig.speed;
    }
    if (m_player->cInput->down && m_player->cTransform->pos.y < (m_window.getSize().y- m_playerConfig.shapeRadius)) {
        m_player->cTransform->velocity.y = m_playerConfig.speed;
    }
    if (m_player->cInput->right && m_player->cTransform->pos.x < (m_window.getSize().x - m_playerConfig.shapeRadius)) {
        m_player->cTransform->velocity.x = m_playerConfig.speed;
    }
    if (m_player->cInput->left && m_player->cTransform->pos.x > m_playerConfig.shapeRadius) {
        m_player->cTransform->velocity.x = -m_playerConfig.speed;
    }
    for (auto e : m_entities.getEntities()) {
        e->cTransform->pos.x += e->cTransform->velocity.x;
        e->cTransform->pos.y += e->cTransform->velocity.y;
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
                   // std::cout << "W key pressed\n";
                    m_player->cInput->up = true;
                    break;
                case sf::Keyboard::A:
                  //  std::cout << "A key pressed\n";
                    m_player->cInput->left = true;
                    break;
                case sf::Keyboard::S:
                   // std::cout << "S key pressed\n";
                    m_player->cInput->down = true;
                    break;
                case sf::Keyboard::D:
                   // std::cout << "D key pressed\n";
                    m_player->cInput->right = true;
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
                   // std::cout << "W key released\n";
                    m_player->cInput->up = false;
                    break;
                case sf::Keyboard::A:
                   // std::cout << "A key released\n";
                    m_player->cInput->left = false;
                    break;
                case sf::Keyboard::S:
                  //  std::cout << "S key released\n";
                    m_player->cInput->down = false;
                    break;
                case sf::Keyboard::D:
                  //  std::cout << "D key released\n";
                    m_player->cInput->right = false;
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
                    auto entity = m_entities.addEntity("bullet");
                    spawnBullet(entity, Vec2(event.mouseButton.x, event.mouseButton.y));
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
    for (auto e : m_entities.getEntities("bullet")) {
        e->cLifespan->remaining--;
        if (e->cLifespan->remaining <= 0)
        {
            e->destroy();
        }
    }
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
    if (m_currentFrame - m_lastEnemySpawnTime > 10)
    {
       // spawnEnemy();
    }
}

void shapeShooterGame::sCollision()
{
}

void shapeShooterGame::spawnPlayer()
{
    float ex = m_window.getSize().x/2;
    float ey = m_window.getSize().y/2;
    auto entity = m_entities.addEntity("player");
    entity->cTransform = std::make_shared<CTransform>(Vec2(ex, ey), Vec2(0.0f, 0.0f), 0.0f);
    entity->cShape = std::make_shared<CShape>(m_playerConfig.shapeRadius, m_playerConfig.sides, sf::Color(m_playerConfig.shapr_color_r, m_playerConfig.shape_color_g, m_playerConfig.shape_color_b)
        , sf::Color(m_playerConfig.outline_color_r, m_playerConfig.outline_color_g, m_playerConfig.outline_color_b),m_playerConfig.outline_thickness);
    entity->cInput = std::make_shared<Cinput>();
    m_player = entity; // assign this entity to player for easily accessing the player

}

void shapeShooterGame::spawnEnemy()
{
    auto entity = m_entities.addEntity("enemy");
    float ex = rand() % m_window.getSize().x;
    float ey = rand() % m_window.getSize().y;

    entity->cTransform = std::make_shared<CTransform>(Vec2(ex,ey), Vec2(0.0f,0.0f),0.0f);
    entity->cShape = std::make_shared<CShape>(16.0f, 3, sf::Color(0, 0, 255), sf::Color(255, 255, 255), 4.0f);
    
    m_lastEnemySpawnTime = m_currentFrame;
}

void shapeShooterGame::spawnSmallEnemies(std::shared_ptr<Entity> entity)
{
}

void shapeShooterGame::spawnBullet(std::shared_ptr<Entity> entity, const Vec2& mousePos)
{
    
    entity->cTransform = std::make_shared<CTransform>(Vec2(m_player->cTransform->pos.x, m_player->cTransform->pos.y), Vec2(0,0),0);
    entity->cShape = std::make_shared<CShape>(16.0f, 3, sf::Color(0, 0, 255), sf::Color(255, 255, 255), 4.0f);
    entity->cLifespan = std::make_shared<CLifeSpan>(10);
    float speed = 0.05;
    entity->cTransform->velocity = { (mousePos.x - m_player->cTransform->pos.x)*speed, (mousePos.y - m_player->cTransform->pos.y)*speed};
  //  entity->cTransform->velocity.y = mousePos.y;
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
        sLifespan();
        m_currentFrame++;
    }
}
