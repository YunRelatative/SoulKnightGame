#ifndef _STATSSLIDER_H_
#define _STATSSLIDER_H_
//确保头文件互相包含不出错
#include "ui/CocosGUI.h"
#include "cocos2d.h"
#include "Actor/Knight.h"
USING_NS_CC;//使用COCOS2D命名空间
using namespace ui;

class StatesSlider :public Node
{
private:
	float fontSize=14;
	Knight* player;
	Slider* HPSlider;
	Slider* ArmorSlider;
	Slider* MPSlider;
	Label* HPLabel;
	Label* ArmorLabel;
	Label* MPLabel;
public:
	static StatesSlider* create(Knight* const newPlayer);
	virtual bool init(Knight* const newPlayer);
	void statesUpdate(float tmd);
};

#endif
