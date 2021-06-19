#ifndef _KNIGHT_H_
#define _KNIGHT_H_
//ȷ��ͷ�ļ��������������
#include "Weapon/weapon.h"
#include "cocos2d.h"

USING_NS_CC;//ʹ��COCOS2D�����ռ�

typedef void (*InteractMethod)();

class Knight :public Node
{
	static constexpr float moveSpeed = 300.0f;//�ƶ��ٶȣ�constexpr����C++ 11�󣬱�ʾ����

public:
	Knight();
	~Knight();

	TMXTiledMap* map=nullptr;
	cocos2d::TMXLayer* _meta = nullptr;//�ϰ���
	void readMap(TMXTiledMap* newMap);

	Animate* animateStand=nullptr;
	Animate* animateWalk=nullptr;
	void initAnimation();

	static Knight* create(weapon* const initialWeapon);
	virtual bool init(weapon* const initialWeapon);

	unsigned int getGold() const;//��ȡ��Ǯ
	void setGold(unsigned int newGold);//���ý�Ǯ

	unsigned int getHP() const;//��ȡHP
	unsigned int getMAXHP() const;
	void setHP(unsigned int newHP);//����HP

	unsigned int getArmor() const;//��ȡ����
	unsigned int getMAXArmor() const;
	void set_Armor(unsigned int newArmor);//���û���

	unsigned int getMP() const;//��ȡMP
	unsigned int getMAXMP() const;
	void setMP(unsigned int newMP);//����MP

	void beHit(int damage);

	Sprite* getSprite() const;//��ȡsprite���ڶ�ȡ��С��

	weapon* getWeapon() const;
	void setWeapon(weapon* const newWeapon);

	void isInteract(InteractMethod newMethod);//����ɽ�����Ʒ�Ӵ�ʱ��ʹ�øú���������һ��void����������ʱ�������¼�
	void unInteract();

	void addKeyboardEvents();//�����¼�����
	void moveUpdateD(float tmd);//ÿ֡�ƶ�
	void moveUpdateA(float tmd);//ÿ֡�ƶ�
	void moveUpdateW(float tmd);//ÿ֡�ƶ�
	void moveUpdateS(float tmd);//ÿ֡�ƶ�
	void moveUpdate(float tmd);//ÿ֡�ƶ�

	void animateUpdate(float tmd);//վ��/���߶����л�

	void armorResumeUpdate(float tmd);//�Զ��ظ�����

	bool IfCollidable(Point position);
	Point tileCoordForPosition(Point position);

	static void die();

private:
	ActionManager* actionManager;//������

	bool is_Live = true;//�����ж��Ƿ񱻻�ɱ

	int gold = 0;//��Ǯ

	unsigned int maxHP = 6;//�������ֵ
	unsigned int HP = maxHP;//��ǰ����ֵ

	unsigned int maxArmor = 5;//��󻤼�ֵ
	unsigned int armor = maxArmor;//��ǰ����ֵ
	float armorResumeTimeStart=5.0f;
	float armorResumeTimeEach=1.0f;

	unsigned int maxMP = 200;//����ӵ���
	unsigned int MP = maxMP;//��ǰ�ӵ���

	Sprite* knightView=nullptr;//���ڶ�ȡ��С
	Sprite* knightStand = nullptr;//��ʾվ������
	Sprite* knightWalk = nullptr;//��ʾ���߶���

	weapon* equipedWeapon = nullptr;//��ȡ��ǰ����
	unsigned int damage = 0;//�˺�
	float attackSpeed = 0;//�����ٶȣ������������и�ֵ

	float moveSpeedX = 0.0f;  //x�����ƶ��ٶ�
	float moveSpeedY = 0.0f; //y�����ƶ��ٶ�

	bool is_MoveUP = false;
	bool is_MoveLeft = false;
	bool is_MoveRight = false;
	bool is_MoveDown = false;
	bool is_Moving = false;

	bool is_Interact = false;//�ɷ���н���
	InteractMethod method;
};

#endif
