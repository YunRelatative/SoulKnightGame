#include "Knight.h"

Knight::Knight() {}
Knight::~Knight() {}

Knight* Knight::create(const std::string& filename)
{
	Knight* knight = new(std::nothrow)Knight();
	if (knight && knight->initWithFile(filename))
	{
		knight->autorelease();
		return knight;
	}
	CC_SAFE_DELETE(knight);
	return nullptr;
}

unsigned int Knight::getGold() const { return this->gold; }
void Knight::setGold(unsigned int newGold) 
{ 
	if (newGold < 0)
		this->gold=0;
	else
		this->gold = newGold; 
}

unsigned int Knight::getHP() const { return this->HP; }
void Knight::setHP(unsigned int newHP)
{
	if (newHP > this->maxHP)
		this->HP = this->maxHP;
	else if (newHP < 0)
		this->HP = 0;
	else
		this->HP = newHP;
	if (this->HP == 0)
		this->is_Live = false;
}

unsigned int Knight::getArmor() const { return this->armor; }
void Knight::set_Armor(unsigned int newArmor)
{
	if (newArmor > this->maxArmor)
		this->armor = this->maxArmor;
	else if (newArmor < 0)
		this->armor = 0;
	else
		this->armor = newArmor;
}

unsigned int Knight::getMP() const { return this->MP; }
void Knight::setMP(unsigned int newMP)
{
	if (newMP > this->maxMP)
		this->MP = this->maxMP;
	else if (newMP < 0)
		this->MP = 0;
	else
		this->MP = newMP;
}

bool Knight::init() {
	this->HP = this->maxHP = 5;
	this->armor = this->maxArmor = 5;
	this->MP = this->maxMP = 200;
	this->gold = 0;
	this->moveSpeedX = 0, this->moveSpeedY = 0;

	//this->weapon = Weapon::create();
	//this->weapon->weaponInit(24.0f, 2, 0, 1, true, 11);
	//this->weapon->setPosition(Vec2(40, 20));
	//this->addChild(weapon, TOP);

	addKeyboardEvents();

	return true;
}

void Knight::addKeyboardEvents()
{
	auto listener = EventListenerKeyboard::create();

	listener->onKeyPressed = [&](EventKeyboard::KeyCode code, Event*)
	{
		switch (code) {
			case EventKeyboard::KeyCode::KEY_D:
			{
				this->schedule(CC_SCHEDULE_SELECTOR(Knight::moveUpdateD));
				this->setFlippedX(false);
				break;
			}
			case EventKeyboard::KeyCode::KEY_A:
			{
				this->schedule(CC_SCHEDULE_SELECTOR(Knight::moveUpdateA));
				this->setFlippedX(true);
				break;
			}
			case EventKeyboard::KeyCode::KEY_W:
			{
				this->schedule(CC_SCHEDULE_SELECTOR(Knight::moveUpdateW));
				break;
			}
			case EventKeyboard::KeyCode::KEY_S:
			{
				this->schedule(CC_SCHEDULE_SELECTOR(Knight::moveUpdateS));
				break;
			}
			default:
				break;
		}
	};

	listener->onKeyReleased = [&](EventKeyboard::KeyCode code, Event*) {
		switch (code) {
			case EventKeyboard::KeyCode::KEY_D:
				this->unschedule(CC_SCHEDULE_SELECTOR(Knight::moveUpdateD));
				this->stopAllActions();
				break;

			case EventKeyboard::KeyCode::KEY_A:
				this->unschedule(CC_SCHEDULE_SELECTOR(Knight::moveUpdateA));
				this->stopAllActions();
				break;

			case EventKeyboard::KeyCode::KEY_W:
				this->unschedule(CC_SCHEDULE_SELECTOR(Knight::moveUpdateW));
				this->stopAllActions();
				break;

			case EventKeyboard::KeyCode::KEY_S:
				this->unschedule(CC_SCHEDULE_SELECTOR(Knight::moveUpdateS));
				this->stopAllActions();
				break;
		}
	};

	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}

void Knight::moveUpdateD(float tmd)
{
	float trueSpeed = moveSpeed / 60.0f;
	Vec2 direction;
	direction.set(trueSpeed, 0);
	auto moveBy = MoveBy::create(1 / 60.0f, direction);
	this->runAction(Sequence::create(moveBy, nullptr));
}
void Knight::moveUpdateA(float tmd)
{
	float trueSpeed = moveSpeed / 60.0f;
	Vec2 direction;
	direction.set(-trueSpeed, 0);
	auto moveBy = MoveBy::create(1 / 60.0f, direction);
	this->runAction(Sequence::create(moveBy, nullptr));
}
void Knight::moveUpdateW(float tmd)
{
	float trueSpeed = moveSpeed / 60.0f;
	Vec2 direction;
	direction.set( 0,trueSpeed);
	auto moveBy = MoveBy::create(1/60.0f, direction);
	this->runAction(Sequence::create(moveBy, nullptr));
}
void Knight::moveUpdateS(float tmd)
{
	float trueSpeed = moveSpeed / 60.0f;
	Vec2 direction;
	direction.set(0,-trueSpeed );
	auto moveBy = MoveBy::create(1 / 60.0f, direction);
	this->runAction(Sequence::create(moveBy, nullptr));
}
