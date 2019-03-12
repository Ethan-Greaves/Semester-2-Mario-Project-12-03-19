#include "SoundEffect.h"

SoundEffect::SoundEffect()
{
	
}

SoundEffect::~SoundEffect()
{

}

void SoundEffect::LoadWAV(Mix_Chunk * SE, std::string path)
{
	SE = Mix_LoadWAV(path.c_str());

	if (SE == NULL)
		std::cout << "Failed to load Sound effect! ERROR: " << Mix_GetError();
}

void SoundEffect::Play(Mix_Chunk * SE)
{
	if (Mix_PlayChannel(-1, SE, 0) == -1)
		std::cout << "Sound Effect not playing. ERROR: " << Mix_GetError() << std::endl;

	//todo This is causing issues. No sounds playing. 
}

void SoundEffect::FreeAudio(Mix_Chunk * SE)
{
	Mix_FreeChunk(SE);
	SE = NULL;
}
