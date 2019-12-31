#pragma once
#include ".\\T_Engine\\T_Sprite.h"
class Sun :
	public T_Sprite
{
public:
	Sun(wstring imgPath, int frameWidth = 0, int frameHeight = 0);
	~Sun();
	void Draw(HDC hdc);
	void setEndY(int endY) { this->endY = endY; };
	int getEndY() { return endY; }
	void setEndX(int endX) { this->endX = endX; };
	int getEndX() { return endX; }
	void LoopFrame(bool ahead = true);
	int getSunStayTime() { return stayTime; }
	void setSunStayTime(int stayTime) { this->stayTime = stayTime; }
	bool mouseClickSun(int x, int y);
	void setIsGet(bool isGet) { this->isGet = isGet; }
	bool getReached() { return reached; }
	void setReceive(int recievedCount) { this->recievedCount = recievedCount; };
	int getReceive() { return recievedCount; };
private :
	int endY;
	int endX;
	int speedX;
	int speedY;
	bool getSpeed;
	int timeCount;
	bool reached;
	int stayTime;
	bool isGet;
	int recievedCount;
};

