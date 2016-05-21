#ifndef LEVEL_H_
#define LEVEL_H_

#include "Tileset.h"
#include "Layer.h"
#include "Player.h"

class Level
{
public:
	Level();
	~Level() {}

	void update();
	void render();

	Player * getPlayer() { return m_pPlayer; }
	void setPlayer(Player * pPlayer) 
	{
		if (pPlayer)
		{
			m_pPlayer = pPlayer;
		}
	}

	std::vector<Tileset> * getTilesets() { return &m_tilesets; }
	std::vector<Layer*> * getLayers() { return &m_layers; }

private:
	std::vector<Tileset> m_tilesets;
	std::vector<Layer*> m_layers;
	
	void scrollObjects();

	Player * m_pPlayer;

	friend class LevelParser;
};

#endif // LEVEL_H