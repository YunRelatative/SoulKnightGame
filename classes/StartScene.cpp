#include "StartScene.h"

#include "ui/CocosGUI.h"
#include "1stScene.h"
using namespace CocosDenshion;

Scene* StartScene::createScene()
{
    auto scene = Scene::create();
    auto layer = StartScene::create();
    scene->addChild(layer);
    return scene;
}

bool StartScene::init()
{
    if (!Scene::init()){
        return false;
    }
    Size visibleSize = Director::getInstance()->getVisibleSize();

    /* ÓÎÏ·±êÌâÍ¼Æ¬ */
    Sprite* titleSprite = Sprite::create("StartTitle.png");
    titleSprite->setPosition(Point(visibleSize.width/5, visibleSize.height-40));
    this->addChild(titleSprite, 2);

    /* ³õÊ¼»¯±³¾°Í¼Æ¬ */
    this->initBGimage();

    /* ³õÊ¼»¯±³¾°ÒôÀÖ */
    this->initBGmusic();

    /* ¼ÓÔØUI */
    loadUI();

    return true;
}

void StartScene::initBGimage() {
    Size visibleSize = Director::getInstance()->getVisibleSize();

    Sprite* bgImage = Sprite::create("StartScene0.png");
    bgImage->setPosition(Point(visibleSize.width / 2, visibleSize.height / 2));
    this->addChild(bgImage,0);
}
void StartScene::initBGmusic() {
    CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("StartSceneBGmusic.wav", true);
    isBGmusicplaying = true;
}

void StartScene::turnOnEffectMusic() {
    isEffecMusicTurnOn = true;
}
void StartScene::turnOffEffectMusic() {
    isEffecMusicTurnOn = false;
}

void StartScene::playBGmusic() {
    CocosDenshion::SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
    isBGmusicplaying = true;
   // initBGmusic();
}

void StartScene::pauseBGmusic() {
    CocosDenshion::SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
    isBGmusicplaying = false;
}

void StartScene::playEffectMusic() {
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("Button.mp3");
}

void StartScene::loadUI() {
    Size visibleSize = Director::getInstance()->getVisibleSize();

    /*±³¾°ÒôÀÖ°´Å¥*/
    auto Btn_BGmusic = CheckBox::create("Btn_backgroundmusic.png",
        "Btn_backgroundmusic_PressDown.png");
    Btn_BGmusic->setPosition(Point(visibleSize.width/15, visibleSize.height/14));
    this->addChild(Btn_BGmusic,3);
    Btn_BGmusic->addEventListener(CC_CALLBACK_2(StartScene::BGmusicSelectedEvent, this));

    /*ÒôÐ§°´Å¥*/
    auto Btn_effectMusic = CheckBox::create("Btn_effect.png",
        "Btn_effect_PressDown.png");
    Btn_effectMusic->setPosition(Point(visibleSize.width / 15, visibleSize.height / 5));
    this->addChild(Btn_effectMusic,3);
    Btn_effectMusic->addEventListener(CC_CALLBACK_2(StartScene::effectMusicSelectedEvent, this));

    /*ÐÂÓÎÏ·°´Å¥*/
    Button* Btn_NewGame = Button::create("NewGame.png",
        "NewGame_PressDown.png");
    Btn_NewGame->setPosition(Point(visibleSize.width / 2, visibleSize.height / 10));
    this->addChild(Btn_NewGame,3);
    Btn_NewGame->addTouchEventListener(this, toucheventselector(StartScene::NewGameEvent));

    /*¶ÁÈ¡´æµµ*/
    //TODO:









}

void StartScene::BGmusicSelectedEvent(Ref* pSender, cocos2d::ui::CheckBox::EventType type) {
    switch (type)
    {
        case cocos2d::ui::CheckBox::EventType::SELECTED: {
            if (isEffecMusicTurnOn)
                playEffectMusic();
            pauseBGmusic();
         }break;
        case cocos2d::ui::CheckBox::EventType::UNSELECTED: {
            if (isEffecMusicTurnOn)
                playEffectMusic();
            playBGmusic();
         }break;
    }
}

void StartScene::effectMusicSelectedEvent(Ref* pSender, cocos2d::ui::CheckBox::EventType type)
{
    switch (type) {
    case cocos2d::ui::CheckBox::EventType::SELECTED:
        playEffectMusic();
        isEffecMusicTurnOn = false;
        break;
    case cocos2d::ui::CheckBox::EventType::UNSELECTED:
        isEffecMusicTurnOn = true;
        break;
    }
}

void StartScene::NewGameEvent(Ref*,TouchEventType type)
{
    switch (type) {
        case TouchEventType::TOUCH_EVENT_BEGAN: {
             if (isEffecMusicTurnOn)
                playEffectMusic();
             Size visibleSize = CCDirector::getInstance()->getVisibleSize();
             Sprite* bgImage = Sprite::create("StartScene1.png");
             bgImage->setPosition(Point(visibleSize.width / 2, visibleSize.height / 2));
             this->addChild(bgImage, 1);
            }break;
        case TouchEventType::TOUCH_EVENT_ENDED: {
            //TODO:

             Director::getInstance()->replaceScene(SafeRoomScene::createScene());
			

        }
    }
}

bool StartScene::BGmusic(){
    return isBGmusicplaying;
}
bool StartScene::effectMusic() {
    return isEffecMusicTurnOn;
}