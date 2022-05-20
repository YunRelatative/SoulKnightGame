#include "boss.h"
#include "2d/CCActionGrid.h"
#include "cocos2d.h"
#include "Knight.h"
//#include "1stScene.h"
#include "weapon.h"
#include "SafeScene.h"
#include "BGM.h"
Boss::Boss() {}
Boss::~Boss() {}

Boss* Boss::create(const std::string& filename)
{
	Boss* boss = new(std::nothrow) Boss();
	if (boss && boss->initWithFile(filename))
	{
		boss->autorelease();
		return boss;
	}
	CC_SAFE_DELETE(boss);
	return nullptr;
}

bool Boss::init()
{
	isKilled = false;
	isAdded = true;
	
	BGM::playBGM("bossbgm.mp3");
	setType();
	return true;
}



bool Boss::isCrash(Knight* knight) {

	Rect entityRect = knight->getBoundingBox();

	Point bossPosition = getPosition();

	return entityRect.containsPoint(bossPosition);
}

void Boss::setType() {

	maxHP = HP = 100;


}



/*bool Boss::inRoom(const SoulKnight* battleRoom, Point myPos) {
	Point upLeftPos = battleRoom->getUpleftVertex();
	Point downRightPos = battleRoom->getDownRightVertex();
	if (myPos.x >= upLeftPos.x && myPos.x <= downRightPos.x &&
		myPos.y >= downRightPos.y && myPos.y <= upLeftPos.y) {
		return true;
	}
	return false;
}*/

void Boss::spriteChangeDirection() {
	if (moveSpeedX == 0) {
		return;
	}
	if (moveSpeedX < 0) {
		this->getSprite()->setFlippedX(true);
	}
	else {
		this->getSprite()->setFlippedX(false);
	}
}

void Boss::update(Knight* knight, const Scene* battleRoom)
{
	this->aiOfBoss(knight, battleRoom);
}

void Boss::aiOfBoss(Knight* knight, const Scene* battleRoom) {
	if (knight == nullptr || battleRoom == nullptr) {
		return;
	}
	const Point bossPos = this->getPosition();
	const Point knightPos = knight->getPosition();
	const float disBetweenBossAndKnight =
		bossPos.getDistance(knightPos);  //获取二者距离，用于后续判断


	bossShout++;
	if (bossShout >= 60 * 1)
	{
		if (bossShout <= 60 * 58)
		{
			magicAttack(knight, disBetweenBossAndKnight);
		}
		else if (bossShout <= 60 * 86)
		{
			simpleAttack(knight, disBetweenBossAndKnight);
		}
		else if (bossShout <= 60 * 101)
		{
			magicAttack(knight, disBetweenBossAndKnight);
		}
		else if (bossShout <= 60 * 203)
		{
			gunnerAttack(knight, disBetweenBossAndKnight);
		}
		else
		{
			bossShout = 60 * 60 * 4;
			return;
		}
	}


}


void Boss::simpleAttack(Knight* knight, float disBetweenBossAndKnight)
{
	Vec2 target;
	if (bossShout % 6==0)
	{
		for (int i = 0; i <= 5; i++)
		{
			bullet* firebullet = bullet::create("enemybullet1.png");
			this->getParent()->addChild(firebullet);
			fireSpeed = 7.0f;
			firebullet->setPosition(this->getPosition());
			firebullet->setSpeed(fireSpeed);
			target.x = 450 * cos(3.14 / 3.0 * (i % 6) + 3.14 / 5 * (bossShout % 5));
			target.y = 450 * sin(3.14 / 3.0 * (i % 6) + 3.14 / 5 * (bossShout % 5));
			firebullet->shoot(target);
			vecBossbullet.pushBack(firebullet);
		}
	}

}



void Boss::magicAttack(Knight* knight, float disBetweenBossAndKnight)
{

	Vec2 target;
	stopAllActions();
	if (bossShout % 60 == 1)
	{

		for (int i = 0; i <= 11; i++)
		{
			bullet* firebullet = bullet::create("enemybullet9.png");
			this->getParent()->addChild(firebullet);			
			target.x = 450 * cos(3.14 / 6.0 * i+ 3.14 / 5.0* (bossShout/60))+ (this->getPosition()).x;
			target.y = 450 * sin(3.14 / 6.0 * i + 3.14 / 5.0 * (bossShout /60 ))+ (this->getPosition()).y;
			fireSpeed = 6.0f;
			firebullet->setPosition(target);
			firebullet->setSpeed(fireSpeed);
			Vec2 targetA = this->getPosition()- target;
			firebullet->shoot(targetA);
			vecBossbullet.pushBack(firebullet);
		}

	}

}

void Boss::gunnerAttack(Knight* knight, float disBetweenBossAndKnight)
{
	Vec2 target;
	if (bossShout % 10 == 1)
	{
		int shout = bossShout/10%10 + 1;
		for (int i = 0; i <= 4; i++)
		{
			bullet* firebullet = bullet::create("enemybullet01.png");
			this->getParent()->addChild(firebullet);
			if (i == 0) {
				target.x = (this->getPosition()).x+200;
				target.y = (this->getPosition()).y;
			}
			else if (i == 1) {
				target.x = (this->getPosition()).x-200;
				target.y = (this->getPosition()).y;
			}
			else if (i == 2) {
				target.x = (this->getPosition()).x+400;
				target.y = (this->getPosition()).y+200;
			}
			else if (i == 3) {
				target.x = (this->getPosition()).x-400;
				target.y = (this->getPosition()).y+200;
			}
			fireSpeed = 6.0f;
			firebullet->setPosition(target);
			firebullet->setSpeed(fireSpeed);
			if (shout  <= 5)
			{
				target.x = 450 * cos(3.14 / 180.0 * 255.0 + 3.14 / 30.0 * shout );
				target.y = 450 * sin(3.14 / 180.0 * 255.0 + 3.14 / 30.0 * shout );
			}
			else if (shout  >5)
			{
				target.x = 450 * cos(3.14 / 180.0 * 285 - 3.14 / 30.0 * (shout-5.0));
				target.y = 450 * sin(3.14 / 180.0 * 285 - 3.14 / 30.0 * (shout-5.0));
			}
			firebullet->shoot(target);
			vecBossbullet.pushBack(firebullet);
		}
	}
	if (bossShout % 3 == 1)
	{
		bullet* firebullet1 = bullet::create("enemybullet01.png");
		this->getParent()->addChild(firebullet1);
		target.x = (this->getPosition()).x ;
		target.y = (this->getPosition()).y;
		fireSpeed = 6.0f;
		firebullet1->setPosition(target);
		firebullet1->setSpeed(fireSpeed);
		target.x = 450 * cos(3.14 / 180.0 * 285 + 3.14 / 30.0 * bossShout);
		target.y = 450 * sin(3.14 / 180.0 * 285 +3.14 / 30.0 * bossShout);
		firebullet1->shoot(target);
		vecBossbullet.pushBack(firebullet1);
	}
	if (bossShout % 60 >= 39 && bossShout % 10 == 9)
	{
		bullet* firebullet = bullet::create("enemybullet0.png");
		target = knight->getPosition() - this->getPosition();
		this->getParent()->addChild(firebullet);
		fireSpeed = 8.0f;
		firebullet->setPosition(this->getPosition());
		firebullet->setSpeed(fireSpeed);
		firebullet->shoot(target);
		vecBossbullet.pushBack(firebullet);

	}
	
}
void Boss::bulletadd()
{
	int bulletNum;
	bulletNum = vecBossbullet.size();
	for (auto it = vecBossbullet.rbegin(); it != vecBossbullet.rbegin() + bulletNum; it++)
	{
		(*it)->life++;
	}


}

void Boss::bulletmove()
{
	for (INT32 i = 0; i < vecBossbullet.size(); ++i)
	{
		auto bullet = vecBossbullet.at(i);
		if (bullet->life >= 60*6)
		{
			bullet->removeFromParent();
			auto actionRemove = RemoveSelf::create();
			bullet->runAction(Sequence::create(actionRemove, nullptr));
			vecBossbullet.eraseObject(bullet);
			--i;
			continue;
		}
	}
}