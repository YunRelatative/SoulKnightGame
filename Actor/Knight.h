#ifndef _KNIGHT_H_
#define _KNIGHT_H_
//确保头文件互相包含不出错
#include "Weapon/weapon.h"
#include "cocos2d.h"

USING_NS_CC;//使用COCOS2D命名空间

typedef void (*InteractMethod)();

class Knight :public Node
{
	static constexpr float moveSpeed = 300.0f;//移动速度，constexpr用于C++ 11后，表示常量

public:
	Knight();
	~Knight();

	TMXTiledMap* map=nullptr;
	cocos2d::TMXLayer* _meta = nullptr;//障碍物
	void readMap(TMXTiledMap* newMap);

	Animate* animateStand=nullptr;
	Animate* animateWalk=nullptr;
	void initAnimation();

	static Knight* create(weapon* const initialWeapon);
	virtual bool init(weapon* const initialWeapon);

	unsigned int getGold() const;//获取金钱
	void setGold(unsigned int newGold);//设置金钱

	unsigned int getHP() const;//获取HP
	unsigned int getMAXHP() const;
	void setHP(unsigned int newHP);//设置HP

	unsigned int getArmor() const;//获取护甲
	unsigned int getMAXArmor() const;
	void set_Armor(unsigned int newArmor);//设置护甲

	unsigned int getMP() const;//获取MP
	unsigned int getMAXMP() const;
	void setMP(unsigned int newMP);//设置MP

	void beHit(int damage);

	Sprite* getSprite() const;//获取sprite用于读取大小等

	weapon* getWeapon() const;
	void setWeapon(weapon* const newWeapon);

	void isInteract(InteractMethod newMethod);//当与可交互物品接触时，使用该函数，传入一个void函数代表交互时发生的事件
	void unInteract();

	void addKeyboardEvents();//键盘事件监听
	void moveUpdateD(float tmd);//每帧移动
	void moveUpdateA(float tmd);//每帧移动
	void moveUpdateW(float tmd);//每帧移动
	void moveUpdateS(float tmd);//每帧移动
	void moveUpdate(float tmd);//每帧移动

	void animateUpdate(float tmd);//站立/行走动画切换

	void armorResumeUpdate(float tmd);//自动回复护甲

	bool IfCollidable(Point position);
	Point tileCoordForPosition(Point position);

	static void die();

private:
	ActionManager* actionManager;//管理动画

	bool is_Live = true;//用于判定是否被击杀

	int gold = 0;//金钱

	unsigned int maxHP = 6;//最大生命值
	unsigned int HP = maxHP;//当前生命值

	unsigned int maxArmor = 5;//最大护甲值
	unsigned int armor = maxArmor;//当前护甲值
	float armorResumeTimeStart=5.0f;
	float armorResumeTimeEach=1.0f;

	unsigned int maxMP = 200;//最大子弹数
	unsigned int MP = maxMP;//当前子弹数

	Sprite* knightView=nullptr;//用于读取大小
	Sprite* knightStand = nullptr;//显示站立动画
	Sprite* knightWalk = nullptr;//显示行走动画

	weapon* equipedWeapon = nullptr;//获取当前武器
	unsigned int damage = 0;//伤害
	float attackSpeed = 0;//攻击速度，调用武器进行赋值

	float moveSpeedX = 0.0f;  //x方向移动速度
	float moveSpeedY = 0.0f; //y方向移动速度

	bool is_MoveUP = false;
	bool is_MoveLeft = false;
	bool is_MoveRight = false;
	bool is_MoveDown = false;
	bool is_Moving = false;

	bool is_Interact = false;//可否进行交互
	InteractMethod method;
};

#endif
