#include "SafeScene.h"
#include "HelloWorldScene.h"
#include "Knight.h"
#include "1stScene.h"
#include "enemy.h"
#include "weapon.h"
USING_NS_CC;

Scene* SafeScene::createScene()
{
    return SafeScene::create();
}

static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in SafeScene.cpp\n");
}

bool SafeScene::init()
{
    if (!Scene::init())
    {
        return false;
    }

    if (!Scene::initWithPhysics())
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    Sprite* SafePicture = Sprite::create("SafePicture.png");
    if (SafePicture == nullptr)
    {
        problemLoading("'SafePicture.png'");
    }
    else
    {
        float x = origin.x + visibleSize.width/2;
        float y = origin.y + visibleSize.height/2;
        SafePicture->setPosition(Vec2(x, y));

        this->addChild(SafePicture, 0);
    }

    Sprite* SafeToFight = Sprite::create("SafeToFight.png");
    if (SafeToFight == nullptr)
    {
        problemLoading("'SafeToFight.png'");
    }
    else
    {
        float x = origin.x + visibleSize.width / 2;
        float y = origin.y + visibleSize.height - SafeToFight->getContentSize().height / 2;
        SafeToFight->setPosition(Vec2(x, y));

        this->addChild(SafeToFight, 0);
    }
    PhysicsBody* gatePhysicsBody = PhysicsBody::createBox(SafeToFight->getContentSize(), PhysicsMaterial(0.0f, 0.0f, 0.0f));
    gatePhysicsBody->setDynamic(false);
    gatePhysicsBody->setContactTestBitmask(0xFFFFFFFF);
    SafeToFight->setPhysicsBody(gatePhysicsBody);
    SafeToFight->setTag(9);//10-´«ËÍÃÅ


    player = Knight::create("player.png");
    if (player == nullptr)
    {
        problemLoading("'player.png'");
    }
    else
    {
        float x = origin.x + visibleSize.width / 2;
        float y = origin.y + player->getContentSize().height / 2 + 80;
        player->setPosition(Vec2(x, y));

        

        this->addChild(player, 0);
        player->init();
    }
    

    PhysicsBody* physicsBody = PhysicsBody::createBox(player->getContentSize(), PhysicsMaterial(0.0f, 0.0f, 0.0f));
    physicsBody->setDynamic(false);
    physicsBody->setContactTestBitmask(0xFFFFFFFF);
    player->setPhysicsBody(physicsBody);
    player->setTag(1);//1-Ö÷½Ç

    auto contactListener = EventListenerPhysicsContact::create();
    contactListener->onContactBegin = CC_CALLBACK_1(SafeScene::onContactBegin, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(contactListener, this);

    
    aWeapon = shotGun::create();
    aWeapon->setPosition(player->getPosition());
    this->addChild(aWeapon);

    auto eventListener = EventListenerTouchOneByOne::create();
    eventListener->onTouchBegan = CC_CALLBACK_2(SafeScene::onTouchBegan, this);
    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(eventListener, player);
    
    /*Enemy *aenemy = Enemy::create("aenemy.png");
    if (aenemy == nullptr)
    {
      problemLoading("'aenemy.png'");
    }
    else
    {
      float x = origin.x + visibleSize.width / 2;
      float y = origin.y + aenemy->getContentSize().height / 2 ;
      aenemy->setPosition(Vec2(x, y));



      this->addChild(aenemy, 0);
      aenemy->init();
    }*/


    return true;
}

bool SafeScene::onContactBegin(cocos2d::PhysicsContact& contact)
{
    auto nodeA = contact.getShapeA()->getBody()->getNode();
    auto nodeB = contact.getShapeB()->getBody()->getNode();

    if (nodeA && nodeB)
    {
        if (nodeA->getTag() == 9|| nodeB->getTag() == 9)
        {
            Director::getInstance()->replaceScene(SoulKnight::create());
        }
    }

    return true;
}

bool SafeScene::onTouchBegan(Touch* touch, Event* unused_event) {

  Vec2 touchLocation = touch->getLocation();
  Vec2 offset = touchLocation - player->getPosition();
  offset.normalize();

  aWeapon->setPosition(player->getPosition());
  aWeapon->shoot1(player->getPosition(), offset);
  return true;
}