#ifndef LEVEL_MANAGER_H_
#define LEVEL_MANAGER_H_

#include "Level.h"
#include "GameStateMachine.h"

class LevelManager
{
public:
	LevelManager(const std::string & firstLevel);
	~LevelManager();
	void setCurrentLevel(Level * pLevel) { if (pLevel) m_pCurrentLevel = pLevel; }
	void setCurrentLevel(const std::string & nameLevel);
	Level * getCurrentLevel() const { return m_pCurrentLevel; }
	bool nextLevel();
	virtual void update();
	virtual void draw() {}
	virtual void clean(){}

private:
	Level * m_pCurrentLevel;
	LevelParser * m_pParser;
	std::string m_nextLevelName;
};

#endif // LEVEL_MANAGER_H_