#include "enemy.h"
#include "2d/CCActionGrid.h"
#include "cocos2d.h"
#include "Knight.h"
//#include "1stScene.h"
#include "weapon.h"
#include "SafeScene.h"

Enemy::Enemy() {}
Enemy::~Enemy() {}

Enemy* Enemy::create(const std::string& filename)
{
	Enemy* enemy = new(std::nothrow) Enemy();
	if (enemy && enemy->initWithFile(filename))
	{
		enemy->autorelease();
		return enemy;
	}
	CC_SAFE_DELETE(enemy);
	return nullptr;
}

bool Enemy::init() 
{
	isKilled = false;
	isAdded = true;
	setType(enemyType);
	setAttackRange();
	return true;
}



bool Enemy::isCrash(Knight* knight) {

	Rect entityRect = knight->getBoundingBox();

	Point enemyPosition = getPosition();

	return entityRect.containsPoint(enemyPosition);
}

void Enemy::setType(int type) {
	enemyType = type;
	setAttackRange();
	switch (type) {
	case 0: //会射弹幕的妖精
		maxHP = HP = 8 ;

		break;
	case 1: //只会撞的小怪
		maxHP = HP = 10 ;

		break;
	case 2: //攻击距离较长的小怪
		maxHP = HP = 10;
		break;
	case 3: //攻击距离最长的小怪
		maxHP = HP = 9;
		
		break;
	}
}

void Enemy::setAttackRange() {
	switch (enemyType)
	{
	case 0:
		ATTACKRANGE = 300;
		break;
	case 1:
		ATTACKRANGE = SIGHTRANGE;
		break;
	case 2:
		ATTACKRANGE = 400;
		break;
	case 3:
		ATTACKRANGE = 350;
		break;
	default:
		break;
	}
}

/*bool Enemy::inRoom(const SoulKnight* battleRoom, Point myPos) {
	Point upLeftPos = battleRoom->getUpleftVertex();
	Point downRightPos = battleRoom->getDownRightVertex();
	if (myPos.x >= upLeftPos.x && myPos.x <= downRightPos.x &&
		myPos.y >= downRightPos.y && myPos.y <= upLeftPos.y) {
		return true;
	}
	return false;
}*/

void Enemy::spriteChangeDirection() {
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

void Enemy::update(Knight* knight, const Scene* battleRoom)
{
	this->aiOfEnemy(knight, battleRoom);
}

void Enemy::aiOfEnemy(Knight* knight, const Scene* battleRoom) {
	if (knight == nullptr || battleRoom == nullptr) {
		return;
	}
	if (enemyShout >= 600)
		enemyShout = 0;
	const Point enemyPos = this->getPosition();
	const Point knightPos = knight->getPosition();
	const float disBetweenEnemyAndKnight =
		enemyPos.getDistance(knightPos);  //获取二者距离，用于后续判断

	if (disBetweenEnemyAndKnight <0) {
		stopAllActions();
	}
	else {
		if (disBetweenEnemyAndKnight > ATTACKRANGE) {
			moveSpeedX = 3.0f * (knightPos.x - enemyPos.x) / disBetweenEnemyAndKnight;
			moveSpeedY = 3.0f * (knightPos.y - enemyPos.y) / disBetweenEnemyAndKnight;
			float time = disBetweenEnemyAndKnight /40.0f;
			auto moveBy = MoveBy::create(1/60.0f,Vec2((knightPos.x - enemyPos.x)/ time/30.0f, (knightPos.y - enemyPos.y)/ time/30.0f));
			this->runAction(moveBy);
		}
		else {
			enemyShout++;
			attackTheKnight(knight, disBetweenEnemyAndKnight, battleRoom);
		}
	}


}

void Enemy::attackTheKnight(Knight* knight,float disBetweenEnemyAndKnight, const Scene* battleRoom) {
	if (disBetweenEnemyAndKnight < ATTACKRANGE) {
		switch (enemyType)
		{
		case 0:
			simpleAttack(knight, disBetweenEnemyAndKnight);
			break;
		case 1:
			crashAttack(knight, disBetweenEnemyAndKnight, battleRoom);
			break;
		case 2:
			magicAttack(knight, disBetweenEnemyAndKnight);
			break;
		case 3:
			gunnerAttack(knight, disBetweenEnemyAndKnight);
			break;
		default:
			break;
		}
	}
}


void Enemy::simpleAttack(Knight* knight, float disBetweenEnemyAndKnight)
{
	bullet* firebullet = bullet::create("enemybullet2.png");
	Vec2 target = knight->getPosition()-this->getPosition();
	stopAllActions();
	if (enemyShout % 60 == 1)
	{
		this->getParent()->addChild(firebullet);
		fireSpeed = 8.0f;
		firebullet->setPosition(this->getPosition());
		firebullet->setSpeed(fireSpeed);
	    firebullet->shoot(target);
		vecEnemybullet.pushBack(firebullet);
	}
		
}

void Enemy::crashAttack(Knight* knight, float disBetweenEnemyAndKnight, const Scene* battleRoom)
{
	if (enemyShout % 240 == 1)
	{
		auto enemyPos = this->getPosition();
		auto knightPos = knight->getPosition();
		float time = disBetweenEnemyAndKnight / 60.0f;
		auto moveBy = MoveBy::create(1, Vec2((knightPos.x - enemyPos.x) , (knightPos.y - enemyPos.y)));
		this->runAction(moveBy);
	}
}


void Enemy::magicAttack(Knight* knight, float disBetweenEnemyAndKnight)
{
	
	Vec2 target;
	stopAllActions();
	if (enemyShout %240==121)
	{
	
		for (int i = 0; i <= 11; i++)
		{
			bullet* firebullet = bullet::create("enemybullet2.png");
			this->getParent()->addChild(firebullet);
			fireSpeed = 6.0f;
			firebullet->setPosition(this->getPosition());
			firebullet->setSpeed(fireSpeed);
			target.x = 450 * cos(3.14 / 6.0 * i);
			target.y = 450 * sin(3.14 / 6.0 * i);
			firebullet->shoot(target);
			vecEnemybullet.pushBack(firebullet);
		}

	}
	
}

void Enemy::gunnerAttack(Knight* knight, float disBetweenEnemyAndKnight)
{
	Vec2 target;
	stopAllActions();
	if (enemyShout % 240 >= 121 && enemyShout % 240 <= 131)
	{
		for (int i = 0; i <= 5; i++)
		{
			bullet* firebullet = bullet::create("enemybullet6.png");
			this->getParent()->addChild(firebullet);
			fireSpeed = 6.0f;
			firebullet->setPosition(this->getPosition());
			firebullet->setSpeed(fireSpeed);
			target.x = 450 * cos(3.14 / 3.0 * (i % 6) + 3.14 / 45.0 * (enemyShout % 12));
			target.y = 450 * sin(3.14 / 3.0 * (i % 6) + 3.14 / 45.0 * (enemyShout % 12));
			firebullet->shoot(target);
			vecEnemybullet.pushBack(firebullet);
		}
	}
	else
	{
		if (enemyShout % 60 >= 39 && enemyShout % 10 == 9)
		{
			bullet* firebullet = bullet::create("enemybullet8.png");
			target = knight->getPosition() - this->getPosition();
			this->getParent()->addChild(firebullet);
			fireSpeed = 8.0f;
			firebullet->setPosition(this->getPosition());
			firebullet->setSpeed(fireSpeed);
			firebullet->shoot(target);
			vecEnemybullet.pushBack(firebullet);
		}



	}
}
void Enemy::bulletadd()
{
	int bulletNum;
	bulletNum = vecEnemybullet.size();
	for (auto it = vecEnemybullet.rbegin(); it != vecEnemybullet.rbegin() + bulletNum; it++)
	{
		(*it)->life++;
	}


}

void Enemy::bulletmove()
{
	for (INT32 i = 0; i < vecEnemybullet.size(); ++i)
	{
		auto bullet = vecEnemybullet.at(i);
		if (bullet->life >= 60 * 6)
		{
			bullet->removeFromParent();
			auto actionRemove = RemoveSelf::create();
			bullet->runAction(Sequence::create(actionRemove, nullptr));
			vecEnemybullet.eraseObject(bullet);
			--i;
			continue;
		}
	}
}