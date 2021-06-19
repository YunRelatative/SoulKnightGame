#pragma once

#ifndef _PROPS_H_
#define _PROPS_H_
#include "Actor/Knight.h"
class props :cocos2d::Sprite
{
public:
	int getPropIndex();
	void setPropIndex(int index);
	void useProps(Knight* knight);

protected:
	int propIndex;
};
#endif
