#include "EntityManager.h"

EntityManager::EntityManager()
{
}

void EntityManager::update()
{
    for (auto e : m_toAdd)
    {
        m_entities.push_back(e);
        m_entityMap[e->tag()].push_back(e);
    }

    m_entities.erase(std::remove_if(m_entities.begin(), m_entities.end(),
        [](std::shared_ptr<Entity> const& e) {
            return !e->isActive();
        }), m_entities.end());

    // Remove entities from the entity map
    for (auto& pair : m_entityMap)
    {
        auto& entityVec = pair.second;
        entityVec.erase(std::remove_if(entityVec.begin(), entityVec.end(),
            [](std::shared_ptr<Entity> const& e) {
                return !e->isActive();
            }), entityVec.end());
    }
    m_toAdd.clear();
}

std::shared_ptr<Entity> EntityManager::addEntity(const std::string& tag)
{
    //auto e = std::make_shared<Entity>(tag, m_totalEntities++);
    auto e = std::shared_ptr<Entity>(new Entity(m_totalEntities++,tag));
    m_toAdd.push_back(e);
    return e;
}

EntityVec& EntityManager::getEntities()
{
    return m_entities;
}

EntityVec& EntityManager::getEntities(const std::string& tag)
{
    return m_entityMap[tag];
}
