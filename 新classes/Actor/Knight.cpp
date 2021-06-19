#define AnimateEachTime 0.35f

#include "Actor/Knight.h"
#include "ui/CocosGUI.h"


using namespace ui;

Knight::Knight() {}
Knight::~Knight() {}

bool LessThan(const Point a, Point b) {
	if (a.x < b.x && a.y < b.y)
		return 1;
	return 0;
}
bool MoreThan(Point a, Point b) {
	if (a.x > b.x && a.y > b.y)
		return 1;
	return 0;
}

Knight* Knight::create(weapon* const initialWeapon)//分别输入图像名/初始武器
{
	Knight* knight = new Knight();
	if (knight && knight->init(initialWeapon))
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
		this->gold = 0;
	else
		this->gold = newGold;
}

unsigned int Knight::getHP() const { return this->HP; }
unsigned int Knight::getMAXHP() const { return this->maxHP; };
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
unsigned int Knight::getMAXArmor() const { return this->maxArmor; };
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
unsigned int Knight::getMAXMP() const { return this->maxMP; };
void Knight::setMP(unsigned int newMP)
{
	if (newMP > this->maxMP)
		this->MP = this->maxMP;
	else if (newMP < 0)
		this->MP = 0;
	else
		this->MP = newMP;
}

Sprite* Knight::getSprite() const { return this->knightView; };

weapon* Knight::getWeapon() const { return this->equipedWeapon; }
void Knight::setWeapon(weapon* const newWeapon)
{
	equipedWeapon = newWeapon;
}

void Knight::beHit(int damage)
{
	this->unschedule(CC_SCHEDULE_SELECTOR(Knight::armorResumeUpdate));
	this->schedule(CC_SCHEDULE_SELECTOR(Knight::armorResumeUpdate), armorResumeTimeStart, CC_REPEAT_FOREVER, armorResumeTimeEach);
	if (damage <= armor)
	{
		armor -= damage;
	}
	else if (damage > armor)
	{
		damage -= armor;
		armor = 0;
		if (damage < HP)
		{
			HP -= damage;
		}
		else if (damage >= HP)
		{
			HP = 0;
			is_Live = false;
			die();
		}
	}
}

void Knight::isInteract(InteractMethod newMethod)
{
	is_Interact = true;
	method = newMethod;
}
void Knight::unInteract() { is_Interact = false; }

void Knight::readMap(TMXTiledMap* newMap)
{
	map = newMap;
	_meta=map->getLayer("meta");
}

void Knight::initAnimation()
{
	auto animationStand = Animation::create();
	char nameSizeStand[30] = { 0 };
	for (int i = 1; i <= 2; i++)
	{
		sprintf(nameSizeStand, "KnightImage/Stand%d.png", i);
		animationStand->addSpriteFrameWithFile(nameSizeStand);
	}
	animationStand->setDelayPerUnit(AnimateEachTime);
	animationStand->setLoops(-1);
	animationStand->setRestoreOriginalFrame(true);
	animateStand = Animate::create(animationStand);
	
	auto animationWalk = Animation::create();
	char nameSizeWalk[30] = { 0 };
	for (int i = 1; i <= 4; i++)
	{
		sprintf(nameSizeWalk, "KnightImage/Walk%d.png", i);
		animationWalk->addSpriteFrameWithFile(nameSizeWalk);
	}
	animationWalk->setDelayPerUnit(AnimateEachTime/2);
	animationWalk->setLoops(-1);
	animationWalk->setRestoreOriginalFrame(true);
	animateWalk = Animate::create(animationWalk);
}

bool Knight::init(weapon* const initialWeapon)
{
	actionManager = Director::getInstance()->getActionManager();
	this->HP = this->maxHP = 5;
	this->armor = this->maxArmor = 5;
	this->MP = this->maxMP = 200;
	this->gold = 0;
	this->moveSpeedX = 0, this->moveSpeedY = 0;

	this->knightView = Sprite::create("KnightImage/Stand1.png");
	this->knightView->setPosition(Vec2::ZERO);
	this->addChild(knightView,0);
	this->knightView->setVisible(false);

	this->knightStand = Sprite::create("KnightImage/Stand1.png");
	this->knightWalk = Sprite::create("KnightImage/Walk1.png");
	this->knightStand->setPosition(Vec2::ZERO);
	this->knightWalk->setPosition(Vec2::ZERO);
	this->addChild(knightStand, 0);
	this->addChild(knightWalk, 0);
	this->knightWalk->setVisible(false);

	this->setWeapon(initialWeapon);
	this->equipedWeapon->setPosition(Vec2(10,-14));
	this->addChild(equipedWeapon,1);

	this->initAnimation();
	this->knightStand->runAction(animateStand);
	this->knightWalk->runAction(animateWalk);
	this->schedule(CC_SCHEDULE_SELECTOR(Knight::animateUpdate));

	this->schedule(CC_SCHEDULE_SELECTOR(Knight::armorResumeUpdate), armorResumeTimeStart, CC_REPEAT_FOREVER,armorResumeTimeEach );

	addKeyboardEvents();

	return true;
}

void Knight::addKeyboardEvents()
{
	auto listener = EventListenerKeyboard::create();

	listener->onKeyPressed = [&](EventKeyboard::KeyCode code, Event*)
	{
		switch (code) 
		{
			case EventKeyboard::KeyCode::KEY_SPACE:
			{
				if (is_Interact)
				{
					(*method)();
				}
				break;
			}
			case EventKeyboard::KeyCode::KEY_J:
			{
				this->setHP(1);
				break;
			}
			case EventKeyboard::KeyCode::KEY_D:
			{
				is_MoveRight = true;
				this->schedule(CC_SCHEDULE_SELECTOR(Knight::moveUpdateD));
				this->knightStand->setFlippedX(false);
				this->knightWalk->setFlippedX(false);
				this->getWeapon()->setFlippedX(false);
				this->getWeapon()->setPosition(Vec2(10, -14));
				break;
			}
			case EventKeyboard::KeyCode::KEY_A:
			{
				is_MoveLeft = true;
				this->schedule(CC_SCHEDULE_SELECTOR(Knight::moveUpdateA));
				this->knightStand->setFlippedX(true);
				this->knightWalk->setFlippedX(true);
				this->getWeapon()->setFlippedX(true);
				this->getWeapon()->setPosition(Vec2(-10, -14));
				break;
			}
			case EventKeyboard::KeyCode::KEY_W:
			{
				is_MoveUP = true;
				this->schedule(CC_SCHEDULE_SELECTOR(Knight::moveUpdateW));
				break;
			}
			case EventKeyboard::KeyCode::KEY_S:
			{
				is_MoveDown = true;
				this->schedule(CC_SCHEDULE_SELECTOR(Knight::moveUpdateS));
				break;
			}
			default:
				break;
		}
	};

	listener->onKeyReleased = [&](EventKeyboard::KeyCode code, Event*) 
	{
		switch (code)
		{
			case EventKeyboard::KeyCode::KEY_D:
			{
				is_MoveRight = false;
				this->unschedule(CC_SCHEDULE_SELECTOR(Knight::moveUpdateD));
				break;
			}
			case EventKeyboard::KeyCode::KEY_A:
			{
				is_MoveLeft = false;
				this->unschedule(CC_SCHEDULE_SELECTOR(Knight::moveUpdateA));
				break;
			}
			case EventKeyboard::KeyCode::KEY_W:
			{
				is_MoveUP = false;
				this->unschedule(CC_SCHEDULE_SELECTOR(Knight::moveUpdateW));
				break;
			}
			case EventKeyboard::KeyCode::KEY_S:
			{
				is_MoveDown = false;
				this->unschedule(CC_SCHEDULE_SELECTOR(Knight::moveUpdateS));
				break;
			}
		}
	};

	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}

void Knight::moveUpdateD(float tmd)
{
	int offset = 3;
	if (this->IfCollidable(this->getPosition()))
	{
		stopAllActions();
		float x = this->getPositionX();				//获得hero的x坐标位置
		float y = this->getPositionY();				//获得hero的y坐标位置
		this->setPosition(x - offset, y);
		return;
	}
	float trueSpeed = moveSpeed / 60.0f;
	Vec2 direction;
	direction.set(trueSpeed, 0);
	auto moveBy = MoveBy::create(1 / 60.0f, direction);
	this->runAction(Sequence::create(moveBy, nullptr));
}
void Knight::moveUpdateA(float tmd)
{
	int offset = 3;
	if (this->IfCollidable(this->getPosition()))
	{
		stopAllActions();
		float x = this->getPositionX();				//获得hero的x坐标位置
		float y = this->getPositionY();				//获得hero的y坐标位置
		this->setPosition(x + offset, y);
		return;
	}
	float trueSpeed = moveSpeed / 60.0f;
	Vec2 direction;
	direction.set(-trueSpeed, 0);
	auto moveBy = MoveBy::create(1 / 60.0f, direction);
	this->runAction(Sequence::create(moveBy, nullptr));
}
void Knight::moveUpdateW(float tmd)
{
	int offset = 3;
	if (this->IfCollidable(this->getPosition()))
	{
		stopAllActions();
		float x = this->getPositionX();				//获得hero的x坐标位置
		float y = this->getPositionY();				//获得hero的y坐标位置
		this->setPosition(x, y - offset);
		return;
	}
	float trueSpeed = moveSpeed / 60.0f;
	Vec2 direction;
	direction.set(0, trueSpeed);
	auto moveBy = MoveBy::create(1 / 60.0f, direction);
	this->runAction(Sequence::create(moveBy, nullptr));
}
void Knight::moveUpdateS(float tmd)
{
	int offset = 3;
	if (this->IfCollidable(this->getPosition()))
	{
		stopAllActions();
		float x = this->getPositionX();				//获得hero的x坐标位置
		float y = this->getPositionY();				//获得hero的y坐标位置
		this->setPosition(x, y + offset);
		return;
	}
	float trueSpeed = moveSpeed / 60.0f;
	Vec2 direction;
	direction.set(0, -trueSpeed);
	auto moveBy = MoveBy::create(1 / 60.0f, direction);
	this->runAction(Sequence::create(moveBy, nullptr));
}

void Knight::animateUpdate(float tmd)
{
	if (!is_Moving && (is_MoveUP || is_MoveRight || is_MoveLeft || is_MoveDown))
	{
		is_Moving = true;
		this->knightStand->setVisible(false);
		this->knightWalk->setVisible(true);
	}
	else if (is_Moving && (!is_MoveUP && !is_MoveRight && !is_MoveLeft && !is_MoveDown))
	{
		is_Moving = false;
		this->knightStand->setVisible(true);
		this->knightWalk->setVisible(false);
	}
}

void Knight::armorResumeUpdate(float tmd)
{
	if (armor < maxArmor)
		armor++;	
}

Point Knight::tileCoordForPosition(Point position)//转换成地图坐标
{
	int x = position.x / this->getScene()->map->getTileSize().width - 8;
	int y = ((this->getScene()->map->getMapSize().height * this->getScene()->map->getTileSize().height) - position.y) / this->getScene()->map->getTileSize().height;
	return Point(x, y);
}

bool Knight::IfCollidable(Point position)
{
	int x = position.x;
	int y = position.y;
	if (MoreThan(Point(x, y), Point(39, -17)) && LessThan(Point(x, y), Point(52, 1)))//最上房间
		return 0;
	else if (MoreThan(Point(x, y), Point(43, 0.9)) && LessThan(Point(x, y), Point(48.5, 25.1)))//走廊1纵
		return 0;
	else if (MoreThan(Point(x, y), Point(37, 25)) && LessThan(Point(x, y), Point(54.5, 42)))//中庭
		return 0;
	else if (MoreThan(Point(x, y), Point(43, 41.9)) && LessThan(Point(x, y), Point(49, 73.1)))//走廊2纵
		return 0;
	else if (MoreThan(Point(x, y), Point(37, 72.5)) && LessThan(Point(x, y), Point(54.3, 98)))//最下房间
		return 0;
	else if (MoreThan(Point(x, y), Point(52.9, 82)) && LessThan(Point(x, y), Point(82.1, 87.5)))//下右走廊
		return 0;
	else if (MoreThan(Point(x, y), Point(82, 78)) && LessThan(Point(x, y), Point(95, 91)))//下右房间
		return 0;
	else if (MoreThan(Point(x, y), Point(-6, 27)) && LessThan(Point(x, y), Point(5, 40)))//中左房间       
		return 0;
	else if (MoreThan(Point(x, y), Point(4.9, 30.5)) && LessThan(Point(x, y), Point(37.1, 36)))//中左走廊       
		return 0;
	else if (MoreThan(Point(x, y), Point(52.9, 31)) && LessThan(Point(x, y), Point(83.1, 36)))//中右走廊       
		return 0;
	else if (MoreThan(Point(x, y), Point(83, 26)) && LessThan(Point(x, y), Point(109, 41)))//中右房间       
		return 0;

	return 1;
}

void Knight::die()
{
	Director::getInstance()->popScene();//替换为一个死亡场景
}

SoulKnight* Knight::getScene()
{
	Scene* test = this->Sprite::getScene();
	SoulKnight* tested = reinterpret_cast<SoulKnight*>(test);
	return tested;
}