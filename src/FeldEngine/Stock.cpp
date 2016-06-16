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
#include <FeldEngine/ECS/Stock.h>
namespace FECS
{

	bool Stock::has(Entity e)
	{
		auto it{ m_stock.find(e) };
		return it != m_stock.end();
	}

	Component * FECS::Stock::get(Entity e)
	{
		auto it{ m_stock.find(e) };
		return (it == m_stock.end() ? nullptr : it->second);
	}

	bool Stock::add(Entity e, Component * c)
	{
		auto retour{ m_stock.insert(std::make_pair(e, c)) };
		return retour.second;
	}

	bool Stock::remove(Entity e)
	{
		auto count{ m_stock.erase(e) };
		return count > 0;
	}

	std::set<Entity> Stock::getEntities() const
	{
		std::set<Entity> retour{};

		for (auto elt : m_stock) {
			retour.insert(elt.first);
		}

		return retour;
	}

}