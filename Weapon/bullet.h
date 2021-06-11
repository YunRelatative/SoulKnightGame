#pragma once
#include "cocos2d.h"
#include "AudioEngine.h"
class bullet : public cocos2d::Sprite
{
public:
	static bullet* create(const std::string& filename);
	void setSpeed(float theSpeed);
	void shoot(cocos2d::Vec2 offset);
	void setPhy();
	//void init();
protected:
	float speed;
};

