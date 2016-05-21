#ifndef SOUND_MANAGER_H_
#define SOUND_MANAGER_H_

#include "stdafx.h"

enum sound_type
{
	SOUND_MUSIC = 0,
	SOUND_SFX = 1
};

class SoundManager
{
public:
	static SoundManager * Instance();
	bool load(const std::string & id, const std::string & filename, sound_type type);
	void playMusic(const std::string & id, int loop);
	void playSound(const std::string & id, int loop);

private:
	static SoundManager * s_pInstance;
	
	SoundManager();
	~SoundManager();

	std::map<std::string, Mix_Chunk*> m_Sfxs;
	std::map<std::string, Mix_Music*> m_Music;
};

#endif // SOUND_MANAGER_H_