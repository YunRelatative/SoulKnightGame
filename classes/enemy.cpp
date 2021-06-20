#include "enemy.h"


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
	auto listener = EventListenerKeyboard::create();
	listener->onKeyPressed = [&](EventKeyboard::KeyCode code, Event*)
	{
		switch (code) {
		case EventKeyboard::KeyCode::KEY_D:
		{
			scheduleUpdate();
			break;
		}
		case EventKeyboard::KeyCode::KEY_A:
		{
			scheduleUpdate();
			break;
		}
		case EventKeyboard::KeyCode::KEY_W:
		{
			scheduleUpdate();
			break;
		}
		case EventKeyboard::KeyCode::KEY_S:
		{
			scheduleUpdate();
			break;
		}
		default:
			break;
		}
	};

	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
	/*Enemy->schedule(moveUpdate,0.1f);*/

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

void Enemy::update(Knight* knight, const SafeScene* battleRoom)
{
	aiOfEnemy(knight, battleRoom);
}

void Enemy::aiOfEnemy(Knight* knight, const SafeScene* battleRoom) {
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
			double time = disBetweenEnemyAndKnight / 3.0f;
			var action= this->moveTo(knightPos);
			var actionEX = action.easing(this->easeOut(time));
			this->runAction(actionEX);
		}
		else {
			attackTheKnight(knight, disBetweenEnemyAndKnight, battleRoom);
		}
	}
	/*if (HP == 0)
	{


		this->unschedule(SEL_SCHEDULE((Enemy::moveUpdate(Knight * knight, const SafeScene * battleRoom)));
	}*/

}

void Enemy::attackTheKnight(Knight* knight,float disBetweenEnemyAndKnight, const SafeScene* battleRoom) {
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
	firebullet->shoot(target);
}

void Enemy::crashAttack(Knight* knight, float disBetweenEnemyAndKnight, const SafeScene* battleRoom)
{
	auto enemyPos = this->getPosition();
	auto knightPos = knight->getPosition();
	moveSpeedX = 6.0f * (knightPos.x - enemyPos.x) / disBetweenEnemyAndKnight;
	moveSpeedY = 6.0f * (knightPos.y - enemyPos.y) / disBetweenEnemyAndKnight;
	double time = disBetweenEnemyAndKnight / 6.0f;
	var action = this->moveTo(knightPos);
	var actionEX = action.easing(this->easeOut(time));
	this->runAction(actionEX);
}


void Enemy::magicAttack(Knight* knight, float disBetweenEnemyAndKnight)
{
	bullet* firebullet = bullet::create("enemybullet2.png");
	Vec2 target = knight->getPosition() - this->getPosition();
	fireSpeed = 6.0f;
	firebullet->setPosition(this->getPosition());
	firebullet->setSpeed(fireSpeed);
	firebullet->shoot(target);
}

void Enemy::gunnerAttack(Knight* knight, float disBetweenEnemyAndKnight)
{
	bullet* firebullet = bullet::create("enemybullet2.png");
	Vec2 target = knight->getPosition() - this->getPosition();
	fireSpeed = 2.0f;
	firebullet->setPosition(this->getPosition());
	firebullet->setSpeed(fireSpeed);
	firebullet->shoot(target);

}
