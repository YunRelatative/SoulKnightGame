#include "Enemy.h"
#include "Knight.h"
#include "BattleRoom.h"
#include "BattleScene.h"
Enemy::Enemy() {}
Enemy::~Enemy() {}

/*Enemy* Enemy::create(const std::string& filename)
{
	Enemy* Enemy = new(std::nothrow)Enemy();
	if (Enemy && Enemy->initWithFile(filename))
	{
		Enemy->autorelease();
		return Enemy;
	}
	CC_SAFE_DELETE(Enemy);
	return nullptr;
}*/

bool Enemy::init() {
	isKilled = isAdded = false;
	this->weapon = Weapon::create();
	this->weapon->bindSprite(Sprite::create(), LayerPlayer + 1);
	this->weapon->setWeaponState(true);
	this->weapon->setMPConsumption(0);
	this->addChild(weapon);
	this->weapon->setVisible(false);
	return true;
}


bool Enemy::isCrash(Knight* knight) {

	Rect entityRect = knight->getBoundingBox();

	Point enemyPosition = getPosition();

	
	return entityRect.containsPoint(enemyPosition);
}

void Enemy::setType(int type) {
	enemyType = type;
	/*setAttackRange();*/
	switch (type) {
	case 0: //会射弹幕的妖精
		maxHP = HP = 8 ;
		/*this->weapon->setAttack(4);
		this->weapon->setBulletType(1);
		this->weapon->setFireSpeed(8.0f);*/
		break;
	case 1: //只会撞的小怪
		maxHP = HP = 10 ;
		this->weapon = nullptr;
		break;
	case 2: //攻击距离较长的小怪
		maxHP = HP = 10;
		this->weapon = nullptr;
		break;
	case 3: //攻击距离最长的小怪
		maxHP = HP = 9;
		/*this->weapon->setAttack(3);
		this->weapon->setFireSpeed(6.0f);
		this->weapon->setBulletType(2);*/
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

/*bool Enemy::inRoom(const BattleRoom* battleRoom, Point myPos) {
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
		this->getSprite()->setFlipX(true);
	}
	else {
		this->getSprite()->setFlipX(false);
	}
}

void Enemy::moveUpdate(float tmd, float moveSpeedX, float moveSpeedY)
{
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

	if (inRoom(battleRoom, Point(enemyPos.x + moveSpeedX, enemyPos.y + moveSpeedY))) {
		this->setPosition(enemyPos.x + moveSpeedX, enemyPos.y + moveSpeedY);
		spriteChangeDirection();
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


void simpleAttack(Knight* knight, float disBetweenEnemyAndKnight)
{


}

void crashAttack(Knight* knight, float disBetweenEnemyAndKnight, const BattleRoom* battleRoom)
{


}


void magicAttack(Knight* knight, float disBetweenEnemyAndKnight)
{

}

void gunnerAttack(Knight* knight, float disBetweenEnemyAndKnight)
{


}
