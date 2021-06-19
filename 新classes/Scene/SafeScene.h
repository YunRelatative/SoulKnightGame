#ifndef __SAFE_SCENE_H__
#define __SAFE_SCENE_H__

#include "cocos2d.h"
#include "Actor/Knight.h"
#include "Weapon/weapon.h"
USING_NS_CC;

class SafeScene : public cocos2d::Scene
{
public:
  static cocos2d::Scene* createScene();
  void update(float fd);
  virtual bool init();
  bool onContactBegin(cocos2d::PhysicsContact& contact);
  //bool onTouchBegan(Touch* touch, Event* unused_event);
  CREATE_FUNC(SafeScene);

protected:
  Knight* player;
};

#endif 