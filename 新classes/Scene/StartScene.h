#ifndef __START_SCENE_H__
#define __START_SCENE_H__

#include "cocos2d.h"
USING_NS_CC;

class StartScene : public cocos2d::Scene
{
private:
    MenuItemImage* startItem;
    Menu* menu;
    Sprite* StartPicture;
    Sprite* Logo;
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    void menuSystemCallback(Ref* pSender);
    void menuSceneChangeCallback(cocos2d::Ref* pSender);

    CREATE_FUNC(StartScene);
};

#endif 