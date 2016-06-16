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
#pragma once

#include <map>
#include <memory>
#include <set>
#include <string>
#include <type_traits>
#include <vector>

#include <FeldEngine/ECS/Entity.h>
#include <FeldEngine/ECS/Event.h>
#include <FeldEngine/ECS/EventHandler.h>
#include <FeldEngine/ECS/Stock.h>
#include <FeldEngine/ECS/System.h>

namespace FECS
{
	class World
	{
	public:
		World() : m_next(1) {}
		~World();

		Entity createEntity();
		bool destroyEntity(Entity e);
		std::set<Entity> getEntities() const;

		Stock* getStock(ComponentType ct);
		bool createStockFor(ComponentType ct);
		template<typename C>
		bool createStockFor() {
			static_assert(std::is_base_of<Component, C>::value, "C doit être un Component");
			static_assert(C::type != INVALID_COMPONENT, "C doit définir ses types");
			return createStockFor(C::type);
		}

		Component* getComponent(Entity e, ComponentType ct);
		template<typename C>
		C* getComponent(Entity e) {
			static_assert(std::is_base_of<Component, C>::value, "C doit être un Component");
			static_assert(C::type != INVALID_COMPONENT, "C doit définir ses types");
			return static_cast<C*>(getComponent(e, C::type));
		}
		bool addComponent(Entity e, ComponentType ct, Component* c);
		template<typename C>
		bool addComponent(Entity e, C* c) {
			static_assert(std::is_base_of<Component, C>::value, "C doit être un Component");
			static_assert(C::type != INVALID_COMPONENT, "C doit définir ses types");
			return addComponent(e, C::type, c);
		}
		Component* extractComponent(Entity e, ComponentType ct);
		template<typename C>
		C* extractComponent(Entity e) {
			static_assert(std::is_base_of<Component, C>::value, "C doit être un Component");
			static_assert(C::type != INVALID_COMPONENT, "C doit définir ses types");
			return static_cast<C*>(extractComponent(e, C::type));
		}

		int subscribeEntityToSystems(Entity e, std::set<ComponentType> componentes);
		int subscribeEntityToSystems(Entity e);
		bool addSystem(std::shared_ptr<System> sys);
		template<typename S, typename ... Args>
		bool addSystem(Args&&... args) {
			static_assert(std::is_base_of<System, S>::value, "S doit être un System");
			return addSystem(std::make_shared<S>(std::forward<Args>(args)...));
		}
		void updateSystems(float deltaTime);

		void registerHandler(EventType type, EventHandler handler);
		template<typename E>
		void registerHandler(EventHandler handler) {
			static_assert(std::is_base_of<Event, E>::value, "E doit être un event");
			static_assert(E::type != INVALID_EVENT, "E doit définir ses type");
			registerHandler(E::type, handler);
		}
		template<typename E, typename R, typename T>
		void registerHandler(R T::*pm, T* obj) {
			static_assert(std::is_base_of<Event, E>::value, "E doit être un event");
			static_assert(E::type != INVALID_EVENT, "E doit définir ses type");
			registerHandler(E::type, std::bind(pm, obj, std::placeholders::_1, std::placeholders::_2, std::placeholders_3));
		}

		void triggerEvent(Entity origin, EventType type, Event* evnt);
		template<typename E>
		void triggerEvent(Entity origin, E* evnt) {
			static_assert(std::is_base_of<Event, E>::value, "E doit être un event");
			static_assert(E::type != INVALID_EVENT, "E doit définir ses type");
			triggerEvent(origin, E::type, evnt);
		}

	private:
		Entity m_next{};

		std::map<Entity, std::set<ComponentType>> m_entities{};
		std::vector<std::shared_ptr<System>> m_systems{};
		std::map<ComponentType, Stock*> m_stocks{};
		std::map<EventType, std::vector<EventHandler>> m_handlers{};
	};
}