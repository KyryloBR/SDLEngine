#include "LevelManager.h"
#include "LevelParser.h"
#include "TileLayer.h"

LevelManager::LevelManager(const std::string & filename)
{
	m_pParser = new LevelParser();
	m_pParser->parseLevel(filename);
}

void LevelManager::update()
{
	
}