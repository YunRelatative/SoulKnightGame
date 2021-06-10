#ifndef _ENEMY_H_
#define _ENEMY_H_
//确保头文件互相包含不出错
#ifndef __ACTION_CCGRID3D_ACTION_H__
#define __ACTION_CCGRID3D_ACTION_H__
#include "2d/CCActionGrid.h"
#include "cocos2d.h"
USING_NS_CC;//使用COCOS2D命名空间

class Weapon;//武器，进行协调更改

class Enemy :public Sprite
{
	static constexpr INT32 SIGHTRANGE = 340;
	INT32 ATTACKRANGE = 0;
public:
	Enemy();
	~Enemy();

	static Enemy* create(const std::string& filename);
	virtual bool init();
	Sprite* sprite;
	unsigned int getHP() const;//获取HP
	void setHP(unsigned int newHP);//设置HP

	unsigned int getArmor() const;//获取护甲
	void set_Armor(unsigned int newArmor);//设置护甲

	unsigned int getMP() const;//获取MP
	void setMP(unsigned int newMP);//设置MP
	bool isCrash(Knight* knight);
	void spriteChangeDirection();
	void setType(int type);
	void addEvent();
	Sprite* getSprite() { return this->sprite; }
	void bindSprite(Sprite* sprite, INT32 layer) {
		this->sprite = sprite;
		this->sprite->setGlobalZOrder(layer);

		//将entity中心和sprite中心重合
		Size size = this->sprite->getContentSize();
		this->setContentSize(size); //设置大小

		this->setAnchorPoint(Point(0.5f, 0.5f)); //设置锚点
		setPosition(Point(.0f, .0f));


		this->addChild(sprite);
		sprite->setPosition(Point(size.width / 2, size.height / 2));
	}
	void aiOfEnemy(Knight* knight, const BattleRoom* battleRoom);
	void addKeyboardEvents();//键盘事件监听
	void moveUpdate(Knight* knight, const BattleRoom* battleRoom);


private:
	int gold = 0;//金钱
	void attackTheKnight(Knight* knight, float disBetweenEnemyAndKnight, const BattleRoom* battleRoom);//++++
	unsigned int maxHP = 5;//最大生命值
	unsigned int HP = maxHP;//当前生命值
	bool is_Live = true;//用于判定是否被击杀
	void setAttackRange();
	void simpleAttack(Knight* knight, float disBetweenEnemyAndKnight);
	float fireSpeed=2.0f;
	void crashAttack(Knight* knight, float disBetweenEnemyAndKnight, const BattleRoom* battleRoom);


	void magicAttack(Knight* knight, float disBetweenEnemyAndKnight);

	void gunnerAttack(Knight* knight, float disBetweenEnemyAndKnight);

	Weapon* weapon = nullptr;//获取当前武器
	unsigned int damage = 0;//伤害
	float attackSpeed = 0;//攻击速度，调用武器进行赋值

	float moveSpeedX = 0.0f;  //x方向移动速度
	float moveSpeedY = 0.0f; //y方向移动速度
	INT32 enemyType = 0;
	bool isAdded;  
	bool isKilled;
	bool inRoom(const BattleRoom* battleRoom, Point myPos);//*************
};

#endif
#endif