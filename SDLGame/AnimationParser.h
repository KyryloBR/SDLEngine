#ifndef ANIMATION_PARSER_H_
#define ANIMATION_PARSER_H_

#include "stdafx.h"
#include <boost\property_tree\detail\rapidxml.hpp>
#include <boost\assert.hpp>
#include "LoopAnimation.h"

using namespace boost::property_tree::detail::rapidxml;

class AnimationParser
{
public:
	void parseAnimation(Animation * pAnimation, const std::string & filename);
	void parseAnimation(std::map<std::string, Animation*> & Animations, const std::string & filename);
	void parseAnimation(std::map<std::string, LoopAnimation*> & Animations, const std::string & filename, const std::string & type);

private:
	void parseFrame(Animation * pAnimation, xml_node<> * pElement);
};

#endif // ANIMATION_PARSER_H_