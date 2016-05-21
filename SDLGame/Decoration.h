#ifndef _DECORATION_H_
#define _DECORATION_H_

#include "EGameObject.h"
#include "AnimationParser.h"

class Decoration : public EGameObject
{
public:
	virtual std::string getType() { return "Decoration"; }
	virtual ~Decoration() {}
	virtual void draw();
	virtual void update();
	virtual void load(const LoaderParams * pParams);
	virtual void clean() {}

private:
	LoopAnimation * m_pCurrentAnimation;
};

#endif // _DECORATION_H_