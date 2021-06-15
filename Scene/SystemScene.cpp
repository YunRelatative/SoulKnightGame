#include "SystemScene.h"
#include "AudioEngine.h"
#include "BGM/GlobalSetting.h"
USING_NS_CC;
using namespace ui;

Scene* SystemScene::createScene()
{
    return SystemScene::create();
}

static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in StartScene.cpp\n");
}

bool SystemScene::init()
{
    if (!Scene::init())
    {
        return false;
    }
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    auto VolumeLabel = Label::createWithTTF("Volume : ", "fonts/Marker Felt.ttf", 35);
    VolumeLabel->setPosition(Vec2(visibleSize.width / 2 - 100, visibleSize.height / 2 - 60));
    this->addChild(VolumeLabel);
    //加入进度条控制音量
    VolumeSlider = Slider::create();
    VolumeSlider->loadBarTexture("Slider/Slider_Background.png");
    VolumeSlider->loadProgressBarTexture("Slider/Slider_Progress.png");
    VolumeSlider->loadSlidBallTextures("Slider/SliderButton.png", "Slider/SliderButton.png", "Slider/SliderButton.png");
    VolumeSlider->setPercent(100);
    VolumeSlider->setPosition(Vec2(visibleSize.width / 2+100, visibleSize.height / 2-60));
    VolumeSlider->addEventListener(CC_CALLBACK_2(SystemScene::sliderCallback, this));
    this->addChild(VolumeSlider);
    //返回按钮
    auto returnItem = MenuItemImage::create("ReturnButton.png", "ReturnButtonPressed.png", CC_CALLBACK_1(SystemScene::menuReturnCallback, this));
    returnItem->setPosition(Vec2(origin.x + visibleSize.width / 2, returnItem->getContentSize().height/2+40));

    BGMItem = MenuItemImage::create("BGMButton.png", "BGMButtonClosed.png", CC_CALLBACK_1(SystemScene::menuBGMOnCallback, this));
    BGMItem->setPosition(Vec2(visibleSize.width / 2 - 100, visibleSize.height / 2 + 140));

    SEItem = MenuItemImage::create("SEButton.png", "SEButtonClosed.png", CC_CALLBACK_1(SystemScene::menuSEOnCallback, this));
    SEItem->setPosition(Vec2(visibleSize.width / 2 + 100, visibleSize.height / 2 + 140));

    BGMClosedItem = MenuItemImage::create("BGMButtonClosed.png", "BGMButton.png", CC_CALLBACK_1(SystemScene::menuBGMClosedCallback, this));
    BGMClosedItem->setPosition(Vec2(visibleSize.width / 2 - 100, visibleSize.height / 2 + 140));
    BGMClosedItem->setVisible(false);

    SEClosedItem = MenuItemImage::create("SEButtonClosed.png", "SEButton.png", CC_CALLBACK_1(SystemScene::menuSEClosedCallback, this));
    SEClosedItem->setPosition(Vec2(visibleSize.width / 2 + 100, visibleSize.height / 2 + 140));
    SEClosedItem->setVisible(false);

    auto menu = Menu::create( returnItem,BGMItem,SEItem,BGMClosedItem,SEClosedItem,NULL);
    menu->setPosition(Vec2::ZERO);

    this->addChild(menu, 1);
    return true;
}

void SystemScene::menuReturnCallback(Ref* pSender)
{
    Director::getInstance()->popScene();
}

void SystemScene::menuBGMOnCallback(Ref* pSender)
{
    isPlayBGM = false;
    AudioEngine::pause(BGMID);
    BGMItem->setVisible(false);
    BGMClosedItem->setVisible(true);
}

void SystemScene::menuSEOnCallback(Ref* pSender)
{
    isPlaySE = false;
    SEItem->setVisible(false);
    SEClosedItem->setVisible(true);
}

void SystemScene::menuBGMClosedCallback(Ref* pSender)
{
    isPlayBGM = true;
    AudioEngine::resume(BGMID);
    BGMClosedItem->setVisible(false);
    BGMItem->setVisible(true);
}

void SystemScene::menuSEClosedCallback(Ref* pSender)
{
    isPlaySE = true;
    SEClosedItem->setVisible(false);
    SEItem->setVisible(true);
}

void SystemScene::sliderCallback(cocos2d::Ref* ref, Slider::EventType type)//进度条改变音量事件
{
    switch (type)
    {
        case cocos2d::ui::Slider::EventType::ON_PERCENTAGE_CHANGED:
        {
            int percent = VolumeSlider->getPercent();
            globalVolume = percent / 100.0f;
            AudioEngine::setVolume(BGMID, globalVolume);
        }
        break;
        default:
            break;
    }
}