#include "LevelParser.h"
#include "TextureManager.h"
#include "Game.h"
#include "TileLayer.h"
#include "base64.h"
#include "ObjectLayer.h"
#include "ObjectFactory.h"
#include "CollisionManager.h"

Level * LevelParser::parseLevel(const std::string & levelFile)
{
	xml_document<> * document = new xml_document<>();
	xml_node<> *pNode;

	std::ifstream xmlFile(levelFile);
	std::vector<char> buffer((std::istreambuf_iterator<char>(xmlFile)), std::istreambuf_iterator<char>());
	buffer.push_back('\0');
	document->parse<0>(&buffer[0]);

	pNode = document->first_node();
	Level * pLevel = new Level();

	m_width = std::atoi(pNode->first_attribute("width")->value());
	m_height = std::atoi(pNode->first_attribute("height")->value());
	m_tileSize = std::atoi(pNode->first_attribute("tileheight")->value());

	for (xml_node<> * element = pNode->first_node(); element; element = element->next_sibling())
	{
		if (element->name() == std::string("tileset"))
		{
			parseTilesets(element, pLevel->getTilesets());
		}
	}

	for (xml_node<> * element = pNode->first_node(); element; element = element->next_sibling())
	{
		if (element->name() == std::string("properties"))
		{
			parseTexture(element);
		}
	}

	for (xml_node<> * element = pNode->first_node(); element; element = element->next_sibling())
	{
		if (element->name() == std::string("layer"))
		{
			parseTileLayer(element, pLevel->getLayers(), *pLevel->getTilesets());
		}
	}

	for (xml_node<> * element = pNode->first_node(); element; element = element->next_sibling())
	{
		if (element->name() == std::string("objectgroup"))
		{
			parseObject(element, pLevel->getLayers(), pLevel);
		}
	}
	CollisionManager::Instance()->setLevel(pLevel);
	return pLevel;
}

void LevelParser::parseTilesets(xml_node<> * pTilesetRoot, std::vector<Tileset> * pTilesets)
{
	Tileset tileset;
	std::string filename;
	for (xml_node<> * pNode = pTilesetRoot->first_node(); pNode; pNode = pNode->next_sibling())
	{
		if (pNode->name() == std::string("image"))
		{
			tileset.height = std::atoi(pNode->first_attribute("height")->value());
			tileset.width = std::atoi(pNode->first_attribute("width")->value());
			tileset.margin = 0;
			tileset.spacing = 0;
			filename = pNode->first_attribute("source")->value();
		}
	}

	tileset.firstGridID = std::atoi(pTilesetRoot->first_attribute("firstgid")->value());
	tileset.tileHeight = std::atoi(pTilesetRoot->first_attribute("tilewidth")->value());
	tileset.tileWidth = std::atoi(pTilesetRoot->first_attribute("tileheight")->value());
	tileset.spacing = 0;
	tileset.margin = 0; 
	tileset.name = pTilesetRoot->first_attribute("name")->value();
	tileset.numColumns = tileset.width / (tileset.tileWidth + tileset.spacing);

	TextureManager::Instance()->load(tileset.name, filename, Game::Instance()->getRenderer());

	pTilesets->push_back(tileset);
}

void LevelParser::parseTileLayer(xml_node<> * pTileLayerRoot, std::vector<Layer*> * pLayers,const std::vector<Tileset> & pTileset)
{
	TileLayer * pTileLayer = new TileLayer(m_tileSize, pTileset);
	pTileLayer->setNameLayer(pTileLayerRoot->first_attribute("name")->value());

	std::vector<std::vector<int>> data;
	/*uLongf*/int numGids = m_width * m_height * sizeof(int);
	std::vector<unsigned> gids;
	gids.reserve(numGids);
	for (xml_node<> * element = pTileLayerRoot->first_node(); element; element = element->next_sibling())
	{
		if (element->name() == std::string("data"))
		{
			for (xml_node<> * tile = element->first_node("tile"); tile; tile = tile->next_sibling("tile"))
			{
					gids.push_back(std::atoi(tile->first_attribute()->value()));
			}
		}
	}
	std::vector<int> layerRow(m_width);

	for (int i = 0; i < m_height; ++i)
	{
		data.push_back(layerRow);
	}
	int gid = 0;
	for (int rows = 0; rows < m_height; ++rows)
	{
		for (int col = 0; col < m_width; ++col)
		{
			data[rows][col] = gids[gid];
			gid++;
		}
	}
	pTileLayer->setTileIDs(data);
	pLayers->push_back(pTileLayer);
}

void LevelParser::parseTexture(xml_node<> * pTileTextureRoot)
{
	for (xml_node<> * property = pTileTextureRoot->first_node(); property; property = property->next_sibling())
	{
		if (property->name() == std::string("property"))
		{
			std::string filename;
			std::string textureID;
			for (xml_attribute<> * attr = property->first_attribute(); attr; attr = attr->next_attribute())
			{		
				if (attr->name() == std::string("name"))
				{
					textureID = attr->value();
				}
				else if (attr->name() == std::string("value"))
				{
					filename = attr->value();
				}
			}
			TextureManager::Instance()->load(textureID, filename, Game::Instance()->getRenderer());
		}
	}
}

void LevelParser::parseObject(xml_node<> * pTileObject, std::vector<Layer*> * pLayers, Level * pLevel)
{
	ObjectLayer * pObjectLayer = new ObjectLayer();
	for (xml_node<> * object = pTileObject->first_node("object"); object; object = object->next_sibling("object"))
	{
		std::string id, type;
		int x, y, width, height;
		for (xml_attribute<> * attr = object->first_attribute(); attr; attr = attr->next_attribute())
		{
			if (attr->name() == std::string("name"))
			{
				id = attr->value();
			}
			if (attr->name() == std::string("type"))
			{
				type = attr->value();
			}
			if (attr->name() == std::string("x"))
			{
				x = std::atoi(attr->value());
			}
			if (attr->name() == std::string("y"))
			{
				y = std::atoi(attr->value());
			}
			if (attr->name() == std::string("width"))
			{
				width = std::atoi(attr->value());
			}
			if (attr->name() == std::string("height"))
			{
				height = std::atoi(attr->value());
			}
		}
		GameObject * pObject = ObjectFactory::Instance()->create(type);
		pObject->load(new LoaderParams(x, y, width, height, id));
		pObjectLayer->getObjects()->push_back(pObject);
		if (type == std::string("Player"))
		{
			pLevel->setPlayer(dynamic_cast<Player*>(pObject));
		}
	}
	pLayers->push_back(pObjectLayer);
}