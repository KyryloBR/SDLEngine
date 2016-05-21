#include "TileLayer.h"
#include "Game.h"

TileLayer::TileLayer(int tileSize, const std::vector<Tileset> & tilesets) : m_tileSize(tileSize), m_tilesets(&tilesets),
m_position(0, 0), m_velocity(0, 0), m_nColumnIncrement(0)
{
	m_nColumns = (Game::Instance()->getWindowWidth() / m_tileSize);
	m_nRows = (Game::Instance()->getWindowHeight() / m_tileSize);
}

void TileLayer::setTileIDs(const std::vector<std::vector<int>> & data)
{
	m_tileIDs = data;
}

void TileLayer::setTileSize(int nSize)
{
	m_tileSize = nSize;
}

void TileLayer::update()
{
	m_position += m_velocity;
	
}

void TileLayer::render()
{

	for (int i = 0; i < m_nRows; ++i)
	{
		for (int j = m_nColumnIncrement; j < m_nColumns + m_nColumnIncrement; ++j)
		{
			int id = m_tileIDs[i][j];
			if (id != 0)
			{
				Tileset tileset = getTilesetByID(id);
				TextureManager::Instance()->drawTile(tileset.name, id, tileset, i, j, m_nColumnIncrement, Game::Instance()->getRenderer());
			}
		}
	}
}

Tileset TileLayer::getTilesetByID(int tileID)
{
	for (int i = 0; i < m_tilesets->size(); ++i)
	{
		if (i + 1 <= m_tilesets->size() - 1)
		{
			if (tileID >= m_tilesets->at(i).firstGridID && tileID < m_tilesets->at(i + 1).firstGridID)
			{
				return m_tilesets->at(i);
			}
		}
		else
		{
			return m_tilesets->at(i);
		}
	}

	Tileset t;
	return t;
}