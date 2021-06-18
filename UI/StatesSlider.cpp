#include "StatesSlider.h"

bool StatesSlider::init(Knight* const newPlayer)
{
	//»æÖÆ
	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto StatesView = Sprite::create("CharacterStates.png");
	this->addChild(StatesView,0);
	HPSlider = Slider::create();
	HPSlider->loadBarTexture("Slider/StatsSlider_Background.png");
	HPSlider->loadProgressBarTexture("Slider/HPSlider_Progress.png");
	HPSlider->setPercent(100);
	HPSlider->setPosition(Vec2(14.5, 30.5));
	this->addChild(HPSlider,1);
	ArmorSlider = Slider::create();
	ArmorSlider->loadBarTexture("Slider/StatsSlider_Background.png");
	ArmorSlider->loadProgressBarTexture("Slider/ArmorSlider_Progress.png");
	ArmorSlider->setPercent(100);
	ArmorSlider->setPosition(Vec2(14.5, 2.3));
	this->addChild(ArmorSlider,1);
	MPSlider = Slider::create();
	MPSlider->loadBarTexture("Slider/StatsSlider_Background.png");
	MPSlider->loadProgressBarTexture("Slider/MPSlider_Progress.png");
	MPSlider->setPercent(100);
	MPSlider->setPosition(Vec2(14.5, -24.5));
	this->addChild(MPSlider,1);
	this->setPosition(Vec2(StatesView->getContentSize().width / 2, visibleSize.height - StatesView->getContentSize().height / 2));
	//°ó¶¨Knight
	player = newPlayer;
	HPLabel = Label::createWithTTF(Value(player->getHP()).asString() + "/" + Value(player->getMAXHP()).asString(),
		"fonts/Marker Felt.ttf", fontSize+2);
	HPLabel->setPosition(14.5, 29);
	this->addChild(HPLabel, 2);
	ArmorLabel = Label::createWithTTF(Value(player->getArmor()).asString() + "/" + Value(player->getMAXArmor()).asString(),
		"fonts/Marker Felt.ttf", fontSize+2);
	ArmorLabel->setPosition(14.5, 1.3);
	this->addChild(ArmorLabel, 2);
	MPLabel = Label::createWithTTF(Value(player->getMP()).asString() + "/" + Value(player->getMAXMP()).asString(),
		"fonts/Marker Felt.ttf", fontSize);
	MPLabel->setPosition(14.5, -26);
	this->addChild(MPLabel, 2);

	this->schedule(CC_SCHEDULE_SELECTOR(StatesSlider::statesUpdate));
	return true;
}

StatesSlider* StatesSlider::create(Knight* const newPlayer)
{
	StatesSlider* pRet = new StatesSlider();
	if (pRet && pRet->init(newPlayer))
	{
		pRet->autorelease();
		return pRet;
	}
	else
	{
		delete pRet;
		pRet = NULL;
		return NULL;
	}
}

void StatesSlider::statesUpdate(float tmd)
{
	HPSlider->setPercent(player->getHP() *100/ player->getMAXHP());
	HPLabel->setString(Value(player->getHP()).asString() + "/" + Value(player->getMAXHP()).asString());
	ArmorSlider->setPercent(player->getArmor() *100/ player->getMAXArmor());
	ArmorLabel->setString(Value(player->getArmor()).asString() + "/" + Value(player->getMAXArmor()).asString());
	MPSlider->setPercent(player->getMP() * 100 / player->getMAXMP());
	MPLabel->setString(Value(player->getMP()).asString() + "/" + Value(player->getMAXMP()).asString());
}