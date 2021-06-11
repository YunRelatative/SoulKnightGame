#ifndef _KNIGHT_H_
#define _KNIGHT_H_
//ȷ��ͷ�ļ��������������

#include "cocos2d.h"

USING_NS_CC;//ʹ��COCOS2D�����ռ�

class Weapon;//����������Э������

class Knight:public Sprite
{
	static constexpr float moveSpeed = 200.0f;//�ƶ��ٶȣ�constexpr����C++ 11�󣬱�ʾ����

public:
	Knight();
	~Knight();

	static Knight* create(const std::string& filename);
	virtual bool init();

	unsigned int getGold() const;//��ȡ��Ǯ
	void setGold(unsigned int newGold);//���ý�Ǯ

	unsigned int getHP() const;//��ȡHP
	void setHP(unsigned int newHP);//����HP

	unsigned int getArmor() const;//��ȡ����
	void set_Armor(unsigned int newArmor);//���û���

	unsigned int getMP() const;//��ȡMP
	void setMP(unsigned int newMP);//����MP
	
	void addKeyboardEvents();//�����¼�����
	void moveUpdateD(float tmd);//ÿ֡�ƶ�
	void moveUpdateA(float tmd);//ÿ֡�ƶ�
	void moveUpdateW(float tmd);//ÿ֡�ƶ�
	void moveUpdateS(float tmd);//ÿ֡�ƶ�

private:
	int gold = 0;//��Ǯ

	unsigned int maxHP = 5;//�������ֵ
	unsigned int HP = maxHP;//��ǰ����ֵ
	bool is_Live = true;//�����ж��Ƿ񱻻�ɱ

	unsigned int maxArmor = 5;//��󻤼�ֵ
	unsigned int armor = maxArmor;//��ǰ����ֵ

	unsigned int maxMP = 200;//����ӵ���
	unsigned int MP = maxMP;//��ǰ�ӵ���

	Weapon* weapon = nullptr;//��ȡ��ǰ����
	unsigned int damage = 0;//�˺�
	float attackSpeed = 0;//�����ٶȣ������������и�ֵ

	float moveSpeedX = 0.0f;  //x�����ƶ��ٶ�
	float moveSpeedY = 0.0f; //y�����ƶ��ٶ�

};

#endif