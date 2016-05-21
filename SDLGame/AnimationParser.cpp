#include "AnimationParser.h"
#include "LoopAnimation.h"

void AnimationParser::parseAnimation(Animation * pAnimation,const std::string & filename)
{
	xml_document<> * doc = new xml_document<>();
	xml_node<> * pNodeFirst;

	std::ifstream xmlFile(filename);
	std::vector<char> buffer((std::istreambuf_iterator<char>(xmlFile)), std::istreambuf_iterator<char>());
	buffer.push_back('\0');
	doc->parse<0>(&buffer[0]);

	pNodeFirst = doc->first_node();

	xml_node<> * pNode = nullptr;
	for (xml_node<> * baseElement = pNodeFirst->first_node(); baseElement; baseElement = baseElement->next_sibling())
	{
		if (baseElement->name() == std::string("Type"))
		{
			for (xml_node<> * element = baseElement->first_node(); element; element = element->next_sibling())
			{
				if (element->name() == std::string("Animation") && element->first_attribute()->value() == pAnimation->getID())
				{
					parseFrame(pAnimation, element);
				}
			}
		}
	}
	delete doc;
	delete pNode;
}

void AnimationParser::parseFrame(Animation * pAnimation, xml_node<> * pElement)
{
	LoopAnimation * animation = dynamic_cast<LoopAnimation*>(pAnimation);
	int i = 0;
	for (xml_node<> * frame = pElement->first_node(); frame; frame = frame->next_sibling())
	{
		if (animation && frame->name() == std::string("frame"))
		{
			animation->addFrame(i,frame->first_attribute()->value());
			i++;
		}
	}
}

void AnimationParser::parseAnimation(std::map<std::string, Animation*> & Animations, const std::string & filename)
{
	xml_document<> * doc = new xml_document<>();
	xml_node<> * pNodeFirst;

	std::ifstream xmlFile(filename);
	std::vector<char> buffer((std::istreambuf_iterator<char>(xmlFile)), std::istreambuf_iterator<char>());
	buffer.push_back('\0');
	doc->parse<0>(&buffer[0]);

	pNodeFirst = doc->first_node();

	xml_node<> * pNode = nullptr;
	for (xml_node<> * element = pNodeFirst->first_node(); element; element = element->next_sibling())
	{
		if (element->name() == std::string("Animation"))
		{	
			Animation * pAnimation = new LoopAnimation(element->first_attribute()->value());
			parseFrame(pAnimation, element);
			Animations.insert(std::make_pair(pAnimation->getID(), pAnimation));
		}
	}
	delete doc;
	delete pNode;
}

void AnimationParser::parseAnimation(std::map<std::string, LoopAnimation*> & Animations, const std::string & filename, const std::string & type)
{
	xml_document<> * doc = new xml_document<>();
	xml_node<> * pNodeFirst;

	std::ifstream xmlFile(filename);
	std::vector<char> buffer((std::istreambuf_iterator<char>(xmlFile)), std::istreambuf_iterator<char>());
	buffer.push_back('\0');
	doc->parse<0>(&buffer[0]);

	pNodeFirst = doc->first_node();
	
	xml_node<> * pNode = nullptr;

	for (xml_node<> * element = pNodeFirst->first_node(); element; element = element->next_sibling())
	{
		if (element->name() == std::string("Type") && element->first_attribute()->value() == type)
		{
			pNode = element;
		}
	}

	for (xml_node<> * element = pNode->first_node(); element; element = element->next_sibling())
	{
		if (element->name() == std::string("Animation"))
		{
			LoopAnimation * pAnimation = new LoopAnimation(element->first_attribute()->value());
			parseFrame(pAnimation, element);
			Animations.insert(std::make_pair(pAnimation->getID(), pAnimation));
		}
	}
}