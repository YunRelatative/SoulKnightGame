#ifndef _ENEMY_H_
#define _ENEMY_H_
//ȷ��ͷ�ļ��������������
#ifndef __ACTION_CCGRID3D_ACTION_H__
#define __ACTION_CCGRID3D_ACTION_H__
#include "2d/CCActionGrid.h"
#include "cocos2d.h"
USING_NS_CC;//ʹ��COCOS2D�����ռ�

class Weapon;//����������Э������

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
	unsigned int getHP() const;//��ȡHP
	void setHP(unsigned int newHP);//����HP

	unsigned int getArmor() const;//��ȡ����
	void set_Armor(unsigned int newArmor);//���û���

	unsigned int getMP() const;//��ȡMP
	void setMP(unsigned int newMP);//����MP
	bool isCrash(Knight* knight);
	void spriteChangeDirection();
	void setType(int type);
	void addEvent();
	Sprite* getSprite() { return this->sprite; }
	void bindSprite(Sprite* sprite, INT32 layer) {
		this->sprite = sprite;
		this->sprite->setGlobalZOrder(layer);

		//��entity���ĺ�sprite�����غ�
		Size size = this->sprite->getContentSize();
		this->setContentSize(size); //���ô�С

		this->setAnchorPoint(Point(0.5f, 0.5f)); //����ê��
		setPosition(Point(.0f, .0f));


		this->addChild(sprite);
		sprite->setPosition(Point(size.width / 2, size.height / 2));
	}
	void aiOfEnemy(Knight* knight, const BattleRoom* battleRoom);
	void addKeyboardEvents();//�����¼�����
	void moveUpdate(Knight* knight, const BattleRoom* battleRoom);


private:
	int gold = 0;//��Ǯ
	void attackTheKnight(Knight* knight, float disBetweenEnemyAndKnight, const BattleRoom* battleRoom);//++++
	unsigned int maxHP = 5;//�������ֵ
	unsigned int HP = maxHP;//��ǰ����ֵ
	bool is_Live = true;//�����ж��Ƿ񱻻�ɱ
	void setAttackRange();
	void simpleAttack(Knight* knight, float disBetweenEnemyAndKnight);
	float fireSpeed=2.0f;
	void crashAttack(Knight* knight, float disBetweenEnemyAndKnight, const BattleRoom* battleRoom);


	void magicAttack(Knight* knight, float disBetweenEnemyAndKnight);

	void gunnerAttack(Knight* knight, float disBetweenEnemyAndKnight);

	Weapon* weapon = nullptr;//��ȡ��ǰ����
	unsigned int damage = 0;//�˺�
	float attackSpeed = 0;//�����ٶȣ������������и�ֵ

	float moveSpeedX = 0.0f;  //x�����ƶ��ٶ�
	float moveSpeedY = 0.0f; //y�����ƶ��ٶ�
	INT32 enemyType = 0;
	bool isAdded;  
	bool isKilled;
	bool inRoom(const BattleRoom* battleRoom, Point myPos);//*************
};

#endif
#endif