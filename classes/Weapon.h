#pragma once
#include "cocos2d.h"
#include "bullet.h"
class weapon :public cocos2d::Sprite
{
public:
	static weapon* create(const std::string& filename);
	bullet* getWeaponBullet();
	void setMP(float mp);
	float getMP();

protected:
	bullet* weaponBullet = bullet::create("Projectile.png");
	float theMp = 0;
};

class rifle : public weapon
{
public:
	static rifle* create();
	void init(cocos2d::Vec2 position);
protected:
	bullet* bullet1 = bullet::create("Projectile.png");
};

class shotGun :public weapon
{
public:
	static shotGun* create();

	void shoot1(cocos2d::Vec2 position, cocos2d::Vec2 offset);
	
protected:
};

