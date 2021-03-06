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
#include <FeldEngine/ECS/System.h>

namespace FECS
{
	class GlobalSystem : public FECS::System
	{
	public:
		GlobalSystem(int priority, std::set<ComponentType> needed, World* world) : System(priority, needed, world) {}

		virtual void update(float deltaTime) override;

		virtual bool addEntity(Entity e) override;
		virtual bool removeEntity(Entity e) override;

		virtual void updateEntity(float deltaTime, Entity e) = 0;

	protected:
		const std::set<Entity>& getEntities() const { return m_entities; }

	private:
		std::set<Entity> m_entities{};

	};

}
