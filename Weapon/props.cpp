#include "props.h"
int props::getPropIndex()
{
	return this->propIndex;
}
void props::setPropIndex(int index)
{
	this->propIndex = index;
}
void props::useProps(Knight* knight)
{
	switch (this->propIndex)
	{
		case 1:
			INT32 curHP;
			curHP = knight->getHP() + 2;
			knight->setHP(curHP);
			break;
		case 2:
			INT32 curMP;
			curMP = knight->getMP() + 20;
			knight->setMP(curMP);
			break;
		//case 3:
			//knight->addGold(5);
			//break;
		//case 4:
			//knight->set_Armor(knight->getMaxArmor());
	}
}