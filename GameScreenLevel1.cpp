#include "GameScreenLevel1.h"

GameScreenLevel1::GameScreenLevel1(SDL_Renderer * renderer) : GameScreen(renderer)
{
	SetUpLevel();
}

GameScreenLevel1::~GameScreenLevel1()
{
	delete mBackgroundTexture;
	mBackgroundTexture = NULL;

	delete myCharacter;
	myCharacter = NULL;

	delete PlayerTwo;
	PlayerTwo = nullptr;

	delete mPowBlock;
	mPowBlock = NULL;

	mEnemies.clear();

	Attack->FreeAudio(SE);
	delete Attack;
	Attack = NULL;

	delete Coin;
	Coin = NULL;

	mLevelMap = nullptr;
}

bool GameScreenLevel1::SetUpLevel()
{
	//Load the background texture 
	mBackgroundTexture = new Texture2D(mRenderer);
	if (!mBackgroundTexture->LoadFromFile("Images/BackgroundMB.png"))
	{
		std::cout << "Failed to load background texture";
		return false;
	}

	//Create the level map tiles 
	SetLevelMap();

	//set up player Characters
	myCharacter = new CharacterMario(mRenderer, "Images/Mario.png", Vector2D(64, 330), mLevelMap);
	PlayerTwo = new CharacterLuigi(mRenderer, "Images/Luigi.png", Vector2D(120, 330), mLevelMap);
	//todo make them spawn in random locations

	//set up POW block
	mPowBlock = new PowBlock(mRenderer, mLevelMap);

	//Set up Koopas
	CreateKoopa(Vector2D(150, 32), FACING_RIGHT, KOOPA_SPEED);
	CreateKoopa(Vector2D(325, 32), FACING_LEFT, KOOPA_SPEED);

	//Set up coins
	Coin = new CharacterCoin(mRenderer, "Images/Coin.png", Vector2D(180, 360), mLevelMap);

	//Set up audio
	SE = new Mix_Chunk();
	Attack = new SoundEffect();
	Attack->LoadWAV(SE, "SoundEffects/again.wav");

	RespawnTimer = 10.0f;

	return true;
}

void GameScreenLevel1::Render()
{
	//Load/Render/Draw everything
	mBackgroundTexture->Render(Vector2D(0, mBackgroundYPos), SDL_FLIP_NONE);
	
	for (unsigned int i = 0; i < mEnemies.size(); i++)
	{
			mEnemies[i]->Render();
	}
	myCharacter->Render();
	PlayerTwo->Render();
	mPowBlock->Render();
	Coin->Render();
}

void GameScreenLevel1::Update(float deltaTime, SDL_Event e)
{
	//------------------------------
	//Do the Screenshake if required
	//------------------------------
	if (mScreenshake)
	{
		mScreenshakeTime -= deltaTime;
		mWobble++;
		mBackgroundYPos = sin(mWobble);
		mBackgroundYPos *= 3.0f;

		//End the screenshake after the duration
		if (mScreenshakeTime <= 0.0f)
		{
			mScreenshake = false;
			mBackgroundYPos = 0.0f;
		}
	}

	//Update The Player 1
	myCharacter->Update(deltaTime, e);
	myCharacter->UpdateKeyboardInput(e);
	Collisions::instance()->WindowCollision(myCharacter);

	//Update The Player 2
	PlayerTwo->Update(deltaTime, e);
	PlayerTwo->UpdateKeyboardInput(e);
	Collisions::instance()->WindowCollision(PlayerTwo);

	//Bounding Box
	if (Collisions::instance()->Box(myCharacter->GetCollisionBox(), PlayerTwo->GetCollisionBox()))
	{
		std::cout << "Collison occurred between Mario & Luigi" << std::endl;
	}

	UpdatePowBlock();
	UpdateEnemies(deltaTime, e);

	Coin->Update(deltaTime, e);
}

void GameScreenLevel1::SetLevelMap()
{
	int map[MAP_HEIGHT][MAP_WIDTH] = {  { 2,2,0,0,0,0,0,0,0,0,0,0,0,0,2,2 }, 
										{ 2,2,0,0,0,0,0,0,0,0,0,0,0,0,2,2 },
										{ 1,1,1,1,1,1,0,0,0,0,1,1,1,1,1,1 },
										{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
										{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
										{ 0,0,0,0,1,1,1,1,1,1,1,1,0,0,0,0 },
										{ 1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1 },
										{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
										{ 0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0 },
										{ 1,1,1,1,1,1,0,0,0,0,1,1,1,1,1,1 },
										{ 2,2,0,0,0,0,0,0,0,0,0,0,0,0,2,2 },
										{ 2,2,0,0,0,0,0,0,0,0,0,0,0,0,2,2 },
										{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 } };

	//Clear up any old map
	if (mLevelMap != nullptr || mLevelMap != NULL)
		delete mLevelMap;

	//Set the new one 
	mLevelMap = new LevelMap(map);
}

void GameScreenLevel1::UpdatePowBlock()
{
	if (Collisions::instance()->Box(myCharacter->GetCollisionBox(), mPowBlock->GetCollisionBox()))
	{
		if (mPowBlock->GetHits() > 0)
		{
			//Collided whilst jumping
			if (myCharacter->IsJumping())
			{
				DoScreenShake();
				mPowBlock->TakeAHit();
				myCharacter->CancelJump();
				Attack->Play(SE);
			}
		}
	}
}

void GameScreenLevel1::UpdateEnemies(float deltaTime, SDL_Event e)
{

	RespawnTimer -= deltaTime;
	if (RespawnTimer <= 0.0f)
	{
		CreateKoopa(Vector2D(325, 128), FACING_LEFT, KOOPA_SPEED);
		RespawnTimer = 10.0f;
	}

	if (!mEnemies.empty())
	{
		int enemyIndexToDelete = -1;
		for (unsigned int i = 0; i < mEnemies.size(); i++)
		{
			//Check if enemy is on the bottom row of tile as they fall to the ground when they die
			if (mEnemies[i]->GetPosition().y > 300.0f)
			{
				//is the enememy off screen to the left / right?
				if (mEnemies[i]->GetPosition().x < (float)(-mEnemies[i]->GetCollisionBox().width
					* 0.5f) || mEnemies[i]->GetPosition().x > SCREEN_WIDTH - (float)(mEnemies[i]->
						GetCollisionBox().width * 0.55))
				{
					//mEnemies[i]->SetAlive(false); //todo set alive to respawn the enemy once they are off the screen
				}
			}
				//Do the update
				mEnemies[i]->Update(deltaTime, e);

				//check for collision with player
				if( (mEnemies[i]->GetPosition().y > 300.0f || mEnemies[i]->GetPosition().y <= 64.0f)
					&& (mEnemies[i]->GetPosition().x < 64.0f || mEnemies[i]->GetPosition().x > SCREEN_WIDTH - 96.0f))
				{
					mEnemies[i]->SetDead();
					//TODO ignore collision if enemy is behind a pipe
				}
				else
				{
					if (Collisions::instance()->Circle(mEnemies[i], myCharacter))
					{
						//myCharacter->SetState(CHARACTER_STATE_PLAYER_DEATH); //todo mario dies when hitting koopa
						if (mEnemies[i]->IsInjured())
						{
							std::cout << "collided with injured koopa" << std::endl;
							mEnemies[i]->SetDead();
						}
						else 
						{
							std::cout << "Mario dead" << std::endl;
						}
					}
				}

				//If enemy is no longer alive, the schedule it for deletion.
				if (mEnemies[i]->GetDead()) 
				{
					enemyIndexToDelete = i;
				}
		}

		//Remove dead enemies, -1 each update
		if (enemyIndexToDelete != -1)
		{
			mEnemies.erase(mEnemies.begin() + enemyIndexToDelete);
		}
	}
}

void GameScreenLevel1::CreateKoopa(Vector2D position, FACING direction, float speed)
{
	koopaCharacter = new CharacterKoopa(mRenderer, "Images/Koopa.png", position, mLevelMap, direction, speed);
	mEnemies.push_back(koopaCharacter);
}

void GameScreenLevel1::DoScreenShake()
{
	mScreenshake = true;
	mScreenshakeTime = SCREENSHAKE_DURATION;
	mWobble = 0.0f;

	for (unsigned int i = 0; i < mEnemies.size(); i++)
	{
		mEnemies[i]->TakeDamage();
	}

}


