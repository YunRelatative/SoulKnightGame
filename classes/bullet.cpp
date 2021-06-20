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
void bullet::shoot(cocos2d::Vec2 offset)
{
	offset.normalize();
	auto shootAmount = offset * 1000;
	auto realDest = shootAmount + this->getPosition();
	auto actionMove = cocos2d::MoveTo::create(this->speed, realDest);
	auto actionRemove = cocos2d::RemoveSelf::create();
	this->runAction(cocos2d::Sequence::create(actionMove->clone(), actionRemove, nullptr));
	
}
void bullet::setPhy()
{
	auto physicsBody = cocos2d::PhysicsBody::createBox(this->getContentSize(), cocos2d::PhysicsMaterial(0.0f, 0.0f, 0.0f));
	physicsBody->setDynamic(false);
	physicsBody->setContactTestBitmask(0xFFFFFFFF);
	this->setPhysicsBody(physicsBody);
	this->setTag(10);
}





