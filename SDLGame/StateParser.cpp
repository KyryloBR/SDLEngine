#include "StateParser.h"
#include "Log.h"
#include "TextureManager.h"
#include "Game.h"
#include "ObjectFactory.h"
#include <xmllite.h>
//#include <RapidXML\rapidxml.hpp>


bool StateParser::loadState(const std::string &  stateFile, const std::string & stateID,
	std::vector<GameObject*> *pObjects, std::vector<std::string> * pTexturesID)
{
	rapidxml::xml_document<> * doc = new rapidxml::xml_document<>();
	rapidxml::xml_node<> * pNodeFirst;
	
	std::ifstream xmlFile(stateFile);
	std::vector<char> buffer((std::istreambuf_iterator<char>(xmlFile)), std::istreambuf_iterator<char>());
	buffer.push_back('\0');
	doc->parse<0>(&buffer[0]);

	pNodeFirst = doc->first_node(stateID.c_str());

	rapidxml::xml_node<> * pTextureNode = nullptr;
	for (rapidxml::xml_node<> * element = pNodeFirst->first_node(); element; element = element->next_sibling())
	{
		if (element->name() == std::string("TEXTURES"))
		{
			pTextureNode = element;
		}
	}
	parserTexture(pTextureNode, pTexturesID);
	rapidxml::xml_node<> * pObjectNode = nullptr;
	for (rapidxml::xml_node<> * element = pNodeFirst->first_node(); element; element = element->next_sibling())
	{
		if (element->name() == std::string("OBJECTS"))
		{
			pObjectNode = element;
		}
	}
	parserObject(pObjectNode, pObjects);
	delete doc;
	return true;
}

void StateParser::parserTexture(rapidxml::xml_node<> * pTextureNode, std::vector<std::string> * pTexturesID)
{
	for (rapidxml::xml_node<> * element = pTextureNode->first_node(); element; element = element->next_sibling())
	{
		std::string filename = element->first_attribute("filename")->value();
		std::string textureID = element->first_attribute("id")->value();

		pTexturesID->push_back(textureID);
		TextureManager::Instance()->load(textureID, filename, Game::Instance()->getRenderer());
		Log::Instance()->write("Filename = " + filename + " texture = " + textureID);
	}
}

void StateParser::parserObject(rapidxml::xml_node<> * pObjectNode, std::vector<GameObject*> *pObjects)
{
	for (rapidxml::xml_node<> * element = pObjectNode->first_node(); element; element = element->next_sibling())
	{
		int x, y, width, height;
		std::string textureID,type;

		x = atoi(element->first_attribute("x")->value());
		y = atoi(element->first_attribute("y")->value());
		width = atoi(element->first_attribute("width")->value());
		height = atoi(element->first_attribute("height")->value());
		textureID = element->first_attribute("id")->value();
		type = element->first_attribute("type")->value();

		GameObject * pObject = ObjectFactory::Instance()->create(type);
		pObject->load(new LoaderParams(x, y, width, height, textureID));
		pObjects->push_back(pObject);
	}
} 
