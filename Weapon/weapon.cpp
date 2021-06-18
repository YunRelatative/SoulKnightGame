#include "weapon.h"
weapon* weapon::create(const std::string& filename)
{
	weapon* sprite = new (std::nothrow)weapon();
	if (sprite && sprite->initWithFile(filename))
	{
		sprite->autorelease();
		return sprite;
	}
	CC_SAFE_DELETE(sprite);
	return nullptr;
}
bullet* weapon::getWeaponBullet()
{
	return this->weaponBullet;
}
void weapon::setMP(float mp)
{
	this->theMp = mp;
}
float weapon::getMP()
{
	return this->theMp;
}


//rifle
rifle* rifle::create()
{
	const char* pszFileName = "Gun0.png";
	rifle* rifleA = new rifle();
	if (rifleA && rifleA->initWithFile(pszFileName))
	{
		rifleA->autorelease();
		return rifleA;
	}
	CC_SAFE_DELETE(rifleA);
	return nullptr;
}
void rifle::init(cocos2d::Vec2 position)
{
	this->bullet1->setPosition(position);
}


//shotGun
shotGun* shotGun::create()
{
	const char* pszFileName = "shotGun.png";
	shotGun* shotGunA = new shotGun();
	if (shotGunA && shotGunA->initWithFile(pszFileName))
	{
		shotGunA->autorelease();
		return shotGunA;
	}
	CC_SAFE_DELETE(shotGunA);
	return nullptr;
}


void shotGun::shoot1(cocos2d::Vec2 position,cocos2d::Vec2 offset)
{
	bullet* bullet1 = bullet::create("Projectile.png");
	bullet1->setPosition(position);
	bullet1->setSpeed(2.0f);
	bullet1->setPhy();
	this->getParent()->addChild(bullet1);

	cocos2d::Vec2 offset1;
	offset1.x = offset.x * cos(3.14 / 6.0) - offset.y * sin(3.14 / 6.0);
	offset1.y = offset.x * sin(3.14 / 6.0) - offset.y * cos(3.14 / 6.0);
	offset1.normalize();

	auto shoot2 = [=]() {
		bullet* bullet2 = bullet::create("bigBullet.png");
		bullet2->setPosition(position);
		bullet2->setSpeed(2.0f);
		bullet2->setPhy();
		this->getParent()->addChild(bullet2);

		auto shootAmount = offset1 * 1000;
		auto realDest = shootAmount + bullet2->getPosition();
		auto actionMove = cocos2d::MoveTo::create(2.0f, realDest);
		auto actionRemove = cocos2d::RemoveSelf::create();
		bullet2->runAction(cocos2d::Sequence::create(actionMove, nullptr));
		//别忘记加remove
	};
	
	auto callFunc = cocos2d::CallFunc::create(shoot2);

	auto shootAmount = offset * 1000;
	auto realDest = shootAmount + bullet1->getPosition();
	auto actionMove = cocos2d::MoveTo::create(2.0f, realDest);
	auto actionRemove = cocos2d::RemoveSelf::create();
	//别忘记加remove
	auto mySpawn = cocos2d::Spawn::createWithTwoActions(actionMove, callFunc);
	bullet1->runAction(cocos2d::Sequence::create(mySpawn,nullptr));
}

//shotGun
knife* knife::create()
{
	const char* pszFileName = "knife1.png";
	knife* knifeA = new knife();
	if (knifeA && knifeA->initWithFile(pszFileName))
	{
		knifeA->autorelease();
		return knifeA;
	}
	CC_SAFE_DELETE(knifeA);
	return nullptr;
}

void knife::attack()
{
	SpriteFrameCache* frameCache = SpriteFrameCache::getInstance();
	frameCache->addSpriteFramesWithFile("bigknife/BigKnife.plist", "bigknife/BigKnife.png");
	Animation* animation = Animation::create();
	
	char nameBuf[100];
	for (int i = 0; i < 8; i++)
	{
		memset(nameBuf, 0, sizeof(nameBuf));
		sprintf(nameBuf, "BigKnife%d.png", i );
		animation->addSpriteFrame(frameCache->getSpriteFrameByName(nameBuf));
	}
	
	animation->setDelayPerUnit(0.05f);
	animation->setLoops(1);
	animation->setRestoreOriginalFrame(true);
	Animate* animate = Animate::create(animation);

	this->runAction(animate);

}