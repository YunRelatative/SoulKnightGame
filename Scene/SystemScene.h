#ifndef __SYSTEM_SCENE_H__
#define __SYSTEM_SCENE_H__

#include "ui/CocosGUI.h"
#include "cocos2d.h"

USING_NS_CC;
using namespace ui;

class SystemScene : public cocos2d::Scene
{
private:
    Slider* VolumeSlider;
    MenuItemImage* BGMItem;
    MenuItemImage* SEItem;
    MenuItemImage* BGMClosedItem;
    MenuItemImage* SEClosedItem;
public:
    static cocos2d::Scene* createScene();

    virtual bool init();

    CREATE_FUNC(SystemScene);

    void menuReturnCallback(Ref* pSender);
    void menuBGMOnCallback(Ref* pSender);
    void menuSEOnCallback(Ref* pSender);
    void menuBGMClosedCallback(Ref* pSender);
    void menuSEClosedCallback(Ref* pSender);
    void sliderCallback(cocos2d::Ref* ref, cocos2d::ui::Slider::EventType type);
};

#endif 