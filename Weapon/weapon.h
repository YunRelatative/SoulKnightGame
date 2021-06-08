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
protected:
};

class shotGun :public weapon
{
public:
	static shotGun* create();
protected:
};

