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