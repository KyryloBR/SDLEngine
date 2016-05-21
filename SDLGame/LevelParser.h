#ifndef LEVELPARSER_H_
#define LEVELPARSER_H_

// DOXYGEN.exe

#include "stdafx.h"
#include "Level.h"
#include <boost\property_tree\detail\rapidxml.hpp>

using namespace boost::property_tree::detail::rapidxml;

class LevelParser
{
public:
	Level * parseLevel(const std::string & levelFile);

private:
	void parseTilesets(xml_node<> * pTilesetRoot, std::vector<Tileset> * pTilesets);
	void parseTileLayer(xml_node<> * pTileLayerRoot, std::vector<Layer*> * pLayers, const std::vector<Tileset> & pTileset);
	void parseTexture(xml_node<> * pTileTextureRoot);
	void parseObject(xml_node<> * pTileObject, std::vector<Layer*> * pLayers, Level * pLevel);

	int m_tileSize;
	int m_width;
	int m_height;
};

#endif // LEVELPARSER_H_