#pragma once
#include "Knight.h"
class props :cocos2d::Sprite
{
public:
	int getPropIndex();
	void setPropIndex(int index);
	void useProps(Knight* knight);

protected:
	int propIndex;
};

