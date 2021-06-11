#include "enemy.h"
#include "Knight.h"
#include "BattleRoom.h"
#include "BattleScene.h"
#include "weapon.h"
#include "bullet.h"

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
	addEvent();
	return true;
}
void Enemy::addEvent() 
{
	this->schedule(SEL_SCHEDULE(Enemy::moveUpdate),1.0f);

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
		ATTACKRANGE = 250;
		break;
	case 1:
		ATTACKRANGE = SIGHTRANGE;
		break;
	case 2:
		ATTACKRANGE = 50;
		break;
	case 3:
		ATTACKRANGE = 350;
		break;
	default:
		break;
	}
}

bool Enemy::inRoom(const BattleRoom* battleRoom, Point myPos) {
	Point upLeftPos = battleRoom->getUpleftVertex();
	Point downRightPos = battleRoom->getDownRightVertex();
	if (myPos.x >= upLeftPos.x && myPos.x <= downRightPos.x &&
		myPos.y >= downRightPos.y && myPos.y <= upLeftPos.y) {
		return true;
	}
	return false;
}

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

void Enemy::moveUpdate(Knight* knight, const BattleRoom* battleRoom)
{
	aiOfEnemy(knight, battleRoom);
	float trueSpeedX = moveSpeedX / 60.0f;
	float trueSpeedY = moveSpeedY / 60.0f;
	Vec2 direction;
	direction.set(trueSpeedX, trueSpeedY);
	auto moveBy = MoveBy::create(1 / 60.0f, direction);
	this->runAction(Sequence::create(moveBy, nullptr));
}

void Enemy::aiOfEnemy(Knight* knight, const BattleRoom* battleRoom) {
	if (knight == nullptr || battleRoom == nullptr) {
		return;
	}

	const Point enemyPos = this->getPosition();
	const Point knightPos = knight->getPosition();
	const float disBetweenEnemyAndKnight =
		enemyPos.getDistance(knightPos);  //获取二者距离，用于后续判断

	if (disBetweenEnemyAndKnight > SIGHTRANGE) {
		/*patrolRoute(battleRoom, knight);*/

	}
	else {
		if (disBetweenEnemyAndKnight > ATTACKRANGE) {
			moveSpeedX = 3.0f * (knightPos.x - enemyPos.x) / disBetweenEnemyAndKnight;
			moveSpeedY = 3.0f * (knightPos.y - enemyPos.y) / disBetweenEnemyAndKnight;
		}
		else {
			attackTheKnight(knight, disBetweenEnemyAndKnight, battleRoom);
		}
	}
	if (HP == 0)
	{
		this->unschedule(SEL_SCHEDULE(Enemy::moveUpdate));
	}

}

void Enemy::attackTheKnight(Knight* knight,float disBetweenEnemyAndKnight, const BattleRoom* battleRoom) {
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
	bullet* firebullet = bullet::create("enemybullet1.png");
	Vec2 target = knight->getPosition() - this->getPosition();
	fireSpeed = 8.0f;
	firebullet->setPosition(this->getPosition());
	firebullet->setSpeed(fireSpeed);
	firebullet->shoot(firebullet, target);
}

void Enemy::crashAttack(Knight* knight, float disBetweenEnemyAndKnight, const BattleRoom* battleRoom)
{
	auto enemyPos = this->getPosition();
	auto knightPos = knight->getPosition();
	moveSpeedX = 6.0f * (knightPos.x - enemyPos.x) / disBetweenEnemyAndKnight;
	moveSpeedY = 6.0f * (knightPos.y - enemyPos.y) / disBetweenEnemyAndKnight;

}


void Enemy::magicAttack(Knight* knight, float disBetweenEnemyAndKnight)
{
	bullet* firebullet = bullet::create("enemybullet2.png");
	Vec2 target = knight->getPosition() - this->getPosition();
	fireSpeed = 6.0f;
	firebullet->setPosition(this->getPosition());
	firebullet->setSpeed(fireSpeed);
	firebullet->shoot(firebullet, target);
}

void Enemy::gunnerAttack(Knight* knight, float disBetweenEnemyAndKnight)
{
	bullet* firebullet = bullet::create("enemybullet2.png");
	Vec2 target = knight->getPosition() - this->getPosition();
	fireSpeed = 2.0f;
	firebullet->setPosition(this->getPosition());
	firebullet->setSpeed(fireSpeed);
	firebullet->shoot(firebullet, target);

}
