#include "Game.h"

int main(int argc, char * argv[])
{
	if (!Game::Instance()->init("TEST",100,100,640,480,0))
	{
		return 0;
	}
	while (Game::Instance()->running())
	{
		Game::Instance()->handleEvents();
		Game::Instance()->update();
		Game::Instance()->render();	
	}
	Game::Instance()->clean();
	return 0;
}