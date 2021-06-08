#include "bullet.h"
bullet* bullet::create(const std::string& filename)
{
	bullet* sprite = new (std::nothrow) bullet();
	if (sprite && sprite->initWithFile(filename))
	{
		sprite->autorelease();
		return sprite;
	}
	CC_SAFE_DELETE(sprite);
	return nullptr;
}
void bullet::setSpeed(float theSpeed)
{
	this->speed = theSpeed;
}
void bullet::shoot(bullet* theBullet, cocos2d::Vec2 offset)
{
	offset.normalize();
	auto shootAmount = offset * 1000;
	auto realDest = shootAmount + theBullet->getPosition();
	auto actionMove = cocos2d::MoveTo::create(this->speed, realDest);
	auto actionRemove = cocos2d::RemoveSelf::create();
	theBullet->runAction(cocos2d::Sequence::create(actionMove, actionRemove, nullptr));
}
void bullet::setPhy(bullet* theBullet)
{
	auto physicsBody = cocos2d::PhysicsBody::createBox(theBullet->getContentSize(), cocos2d::PhysicsMaterial(0.0f, 0.0f, 0.0f));
	physicsBody->setDynamic(false);
	physicsBody->setContactTestBitmask(0xFFFFFFFF);
	theBullet->setPhysicsBody(physicsBody);
	theBullet->setTag(10);
}


