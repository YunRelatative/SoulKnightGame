#ifndef _KNIGHT_H_
#define _KNIGHT_H_
//确保头文件互相包含不出错

#include "cocos2d.h"

USING_NS_CC;//使用COCOS2D命名空间

class Weapon;//武器，进行协调更改

class Knight:public Sprite
{
	static constexpr float moveSpeed = 200.0f;//移动速度，constexpr用于C++ 11后，表示常量

public:
	Knight();
	~Knight();

	static Knight* create(const std::string& filename);
	virtual bool init();

	unsigned int getGold() const;//获取金钱
	void setGold(unsigned int newGold);//设置金钱

	unsigned int getHP() const;//获取HP
	void setHP(unsigned int newHP);//设置HP

	unsigned int getArmor() const;//获取护甲
	void set_Armor(unsigned int newArmor);//设置护甲

	unsigned int getMP() const;//获取MP
	void setMP(unsigned int newMP);//设置MP
	
	void addKeyboardEvents();//键盘事件监听
	void moveUpdateD(float tmd);//每帧移动
	void moveUpdateA(float tmd);//每帧移动
	void moveUpdateW(float tmd);//每帧移动
	void moveUpdateS(float tmd);//每帧移动

private:
	int gold = 0;//金钱

	unsigned int maxHP = 5;//最大生命值
	unsigned int HP = maxHP;//当前生命值
	bool is_Live = true;//用于判定是否被击杀

	unsigned int maxArmor = 5;//最大护甲值
	unsigned int armor = maxArmor;//当前护甲值

	unsigned int maxMP = 200;//最大子弹数
	unsigned int MP = maxMP;//当前子弹数

	Weapon* weapon = nullptr;//获取当前武器
	unsigned int damage = 0;//伤害
	float attackSpeed = 0;//攻击速度，调用武器进行赋值

	float moveSpeedX = 0.0f;  //x方向移动速度
	float moveSpeedY = 0.0f; //y方向移动速度

};

#endif