/*
 * Feld[2D]Engine - FeldECS module
 *
 * Copyright (c) 2016 Victor DENIS (Feldrise, victordenis01@gmail.com)
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of
 * this software and associated documentation files (the "Software"), to deal in
 * the Software without restriction, including without limitation the rights to
 * use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies
 * of the Software, and to permit persons to whom the Software is furnished to do
 * so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */
#include <FeldEngine/ECS/World.h>

#include <cassert>
#include <algorithm>
#include <iostream>

namespace FECS
{

	World::~World()
	{
		for (auto stock : m_stocks) {
			delete stock.second;
		}
	}

	Entity World::createEntity()
	{
		Entity e{ ++m_next };
		assert(e != INVALID_ENTITY);

		auto retour{ m_entities.insert(std::make_pair(e, std::set<ComponentType>())) };
		assert(retour.second);
		return e;
	}

	bool World::destroyEntity(Entity e)
	{
		auto count{ m_entities.erase(e) };
		return count > 0;
	}

	std::set<Entity> World::getEntities() const
	{
		std::set<Entity> retour{};

		for (auto entity : m_entities) {
			retour.insert(entity.first);
		}

		return std::move(retour);
	}

	Stock * World::getStock(ComponentType ct)
	{
		auto it{ m_stocks.find(ct) };
		return it == m_stocks.end() ? nullptr : it->second;
	}

	bool World::createStockFor(ComponentType ct)
	{
		auto retour{ m_stocks.insert(std::make_pair(ct, new Stock)) };
		return retour.second;
	}

	Component * World::getComponent(Entity e, ComponentType ct)
	{
		if (e == INVALID_ENTITY || ct == INVALID_COMPONENT)
			return nullptr;

		Stock *stock{ getStock(ct) };

		if (stock == nullptr)
			return nullptr;

		return stock->get(e);
	}

	bool World::addComponent(Entity e, ComponentType ct, Component * c)
	{
		if (e == INVALID_ENTITY || ct == INVALID_COMPONENT)
			return false;

		Stock* stock{ getStock(ct) };

		if (stock == nullptr)
			return false;

		auto it{ m_entities.find(e) };

		if (it == m_entities.end())
			return false;

		it->second.insert(ct);
		return stock->add(e, c);
	}

	Component * World::extractComponent(Entity e, ComponentType ct)
	{
		if (e == INVALID_ENTITY || ct == INVALID_COMPONENT)
			return nullptr;

		Stock* stock{ getStock(ct) };

		if (stock == nullptr) 
			return nullptr;

		auto it{ m_entities.find(e) };
		if (it == m_entities.end())
			return nullptr;
		it->second.erase(ct);

		Component* c{ stock->get(e) };
		stock->remove(e);
		return c;
	}

	int World::subscribeEntityToSystems(Entity e, std::set<ComponentType> components)
	{
		if (e == INVALID_ENTITY)
			return 0;

		int n{ 0 };

		for (auto& sys : m_systems) {
			const std::set<ComponentType> needed{ sys->getNeededComponents() };
			if (std::includes(components.begin(), components.end(), needed.begin(), needed.end())) {
				sys->addEntity(e);
				++n;
			}
			else {
				sys->removeEntity(e);
			}
		}

		return n;
	}

	int World::subscribeEntityToSystems(Entity e)
	{
		auto it{ m_entities.find(e) };

		if (it == m_entities.end())
			return 0;

		return subscribeEntityToSystems(e, it->second);
	}

	bool World::addSystem(std::shared_ptr<System> sys)
	{
		if (sys)
			m_systems.push_back(sys);

		return true;
	}

	void World::updateSystems(float deltaTime)
	{
		for (auto& sys : m_systems) {
			sys->preUpdate(deltaTime);
		}

		for (auto& sys : m_systems) {
			sys->update(deltaTime);
		}

		for (auto& sys : m_systems) {
			sys->postUpdate(deltaTime);
		}

	}

	void World::registerHandler(EventType type, EventHandler handler)
	{
		assert(handler);
		auto it{ m_handlers.find(type) };

		if (it == m_handlers.end()) {
			bool inserted{};
			std::tie(it, inserted) = m_handlers.insert(std::make_pair(type, std::vector<EventHandler>()));
			assert(inserted);
		}

		it->second.push_back(handler);
	}

	void World::triggerEvent(Entity origin, EventType type, Event * evnt)
	{
		auto it{ m_handlers.find(type) };

		if (it == m_handlers.end())
			return;

		std::vector<EventHandler> kept{};

		for (auto handler : it->second) {
			if (handler(origin, type, evnt) == EventStatus::KEEP)
				kept.push_back(handler);
		}
	std::swap(it->second, kept);
	}


}
