#ifndef _STATSSLIDER_H_
#define _STATSSLIDER_H_
//ȷ��ͷ�ļ��������������
#include "ui/CocosGUI.h"
#include "cocos2d.h"
#include "Actor/Knight.h"
USING_NS_CC;//ʹ��COCOS2D�����ռ�
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
