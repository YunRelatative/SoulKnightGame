#ifndef __SAFE_SCENE_H__
#define __SAFE_SCENE_H__

#include "cocos2d.h"
#include "Knight.h"
#include "weapon.h"
USING_NS_CC;

class SafeScene : public cocos2d::Scene
{
public:
  static cocos2d::Scene* createScene();

  virtual bool init();
  bool onContactBegin(cocos2d::PhysicsContact& contact);
  bool onTouchBegan(Touch* touch, Event* unused_event);
  CREATE_FUNC(SafeScene);
  
protected:
  Knight* player;
  shotGun* aWeapon;
};

#endif 