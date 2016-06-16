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
#include <set>

#include <FeldEngine/ECS/Entity.h>
#include <FeldEngine/ECS/Component.h>

namespace FECS
{
	class World;

	class System
	{
	public:
		System(int priority, std::set<ComponentType> needed, World *world) : m_priority(priority), m_needed(needed), m_world(world) {}
		virtual ~System() {}

		int getPriority() const { return m_priority; }
		std::set<ComponentType> getNeededComponents() const { return m_needed; }
		World* getWorld() const { return m_world; }

		virtual bool addEntity(Entity e) = 0;
		virtual bool removeEntity(Entity e) = 0;

		virtual void preUpdate(float deltaTime) {}
		virtual void update(float deltaTime) {}
		virtual void postUpdate(float deltaTime) {}

	private:
		const int m_priority{};
		const std::set<ComponentType> m_needed{};

		World* const m_world{};
	};
}