#pragma once
#include ".\\T_Engine\\T_Sprite.h"
class ZombieHand : public T_Sprite
{
public:
	ZombieHand(wstring imgPath, int frameWidth, int frameHeight);
	~ZombieHand();

public:
	void init();
	bool LoopFrameOnce(bool ahead);
	void reset();
};

