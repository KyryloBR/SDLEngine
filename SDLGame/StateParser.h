#ifndef STATEPARSER_H_
#define STATEPARSER_H_

#include "stdafx.h"
#include "GameObject.h"
#include <boost\property_tree\detail\rapidxml.hpp>

using namespace boost::property_tree::detail;

class StateParser
{
public:
	bool loadState(const std::string &  stateFile,const std::string & stateID,
		std::vector<GameObject*> *pObjects,std::vector<std::string> * pTexturesID);

private:
	void parserObject(rapidxml::xml_node<> * pObjectNode, std::vector<GameObject*> *pObjects);
	void parserTexture(rapidxml::xml_node<> * pTextureNode, std::vector<std::string> * pTexturesID);
};

#endif // STATEPARSER_H_