#ifndef _WEAPON_H_
#define _WEAPON_H_

#include "cocos2d.h"
#include "Bullet/bullet.h"

USING_NS_CC;

class weapon :public cocos2d::Sprite
{
public:
	static weapon* create(const std::string& filename);
	bullet* getWeaponBullet();
	void setMP(float mp);
	float getMP();
	virtual void attack(cocos2d::Vec2 position, cocos2d::Vec2 offset);
protected:
	bullet* weaponBullet = bullet::create("Projectile.png");
	float theMp = 0;
};

class rifle : public weapon
{
public:
	static rifle* create();
	void attack(cocos2d::Vec2 position, cocos2d::Vec2 offset);
protected:
};

class shotGun :public weapon
{
public:
	static shotGun* create();
	void attack(cocos2d::Vec2 position, cocos2d::Vec2 offset);
protected:
};

class knife :public weapon
{
public:
	static knife* create();
	void knife::attack();
protected:
};

#endif