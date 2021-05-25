#include "bullet.h"
#include "cocos2d.h"
cocos2d::Sprite* bullet::bulletInit(cocos2d::Vec2 _player)
{
	auto bullet = cocos2d::Sprite::create("Projectile.png");
	bullet->setPosition(_player);

  auto physicsBody = cocos2d::PhysicsBody::createBox(bullet->getContentSize(), cocos2d::PhysicsMaterial(0.0f, 0.0f, 0.0f));
  physicsBody->setDynamic(false);
  physicsBody->setContactTestBitmask(0xFFFFFFFF);
  bullet->setPhysicsBody(physicsBody);
  bullet->setTag(10);

  return bullet;
}