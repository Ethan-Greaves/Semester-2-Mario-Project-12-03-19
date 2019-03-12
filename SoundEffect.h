#pragma once
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include "SDL.h"
#include "SDL_mixer.h"

class SoundEffect
{
public:
	SoundEffect();
	~SoundEffect();

	void LoadWAV(Mix_Chunk * SE, std::string path);
	void Play(Mix_Chunk * SE);
	void FreeAudio(Mix_Chunk * SE);
};

