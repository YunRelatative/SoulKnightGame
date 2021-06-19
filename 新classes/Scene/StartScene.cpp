#include "Scene/StartScene.h"
#include "HelloWorldScene.h"
#include "Scene/SafeScene.h"
#include "Scene/SystemScene.h"
#include "BGM/BGM.h"
USING_NS_CC;

Scene* StartScene::createScene()
{
    return StartScene::create();
}

static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in StartScene.cpp\n");
}

bool StartScene::init()
{
    if (!Scene::init())
    {
        return false;
    }
    BGM::playBGM("bkMusic.mp3");
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    MenuItemImage* startItem = MenuItemImage::create(
        "NewGame.png",
        "NewGameSelected.png",
        CC_CALLBACK_1(StartScene::menuSceneChangeCallback, this));

    if (startItem == nullptr ||
        startItem->getContentSize().width <= 0 ||
        startItem->getContentSize().height <= 0)
    {
        problemLoading("'NewGame.png' and 'NewGameSelected.png'");
    }
    else
    {
        float x = origin.x + visibleSize.width/2 ;
        float y = origin.y + startItem->getContentSize().height / 2+40;
        startItem->setPosition(Vec2(x, y));
    }

    auto stopItem = MenuItemImage::create(
      "StopButton.png",
      "StopButtonPressed.png",
      CC_CALLBACK_1(StartScene::menuSystemCallback, this));
    stopItem->setPosition(Vec2(visibleSize.width - stopItem->getContentSize().width / 2, visibleSize.height - stopItem->getContentSize().height / 2));

    Menu* menu = Menu::create(startItem, stopItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    Sprite* StartPicture = Sprite::create("StartPicture.png");
    if (StartPicture == nullptr)
    {
        problemLoading("'StartPicture.png'");
    }
    else
    {
        float x = origin.x + visibleSize.width - StartPicture->getContentSize().width / 2;
        float y = origin.y + StartPicture->getContentSize().height / 2;
        StartPicture->setPosition(Vec2(x, y));

        this->addChild(StartPicture, 0);
    }

    Sprite* Logo = Sprite::create("Logo.png");
    if (Logo == nullptr)
    {
        problemLoading("'Logo.png'");
    }
    else
    {
        float x = origin.x + Logo->getContentSize().width / 2;
        float y = origin.y + visibleSize.height - Logo->getContentSize().height / 2;
        Logo->setPosition(Vec2(x, y));

        this->addChild(Logo, 0);
    }

    
    return true;
}

void StartScene::menuSceneChangeCallback(Ref* pSender)
{
    Director::getInstance()->replaceScene(SafeScene::createScene());
}

void StartScene::menuSystemCallback(Ref* pSender)
{
  Director::getInstance()->pushScene(SystemScene::create());
}
