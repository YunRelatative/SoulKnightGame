#ifndef __StartScene_H__
#define __StartScene_H__

#include "cocos2d.h"
#include "editor-support/cocostudio/CCSGUIReader.h"
#include "cocos-ext.h"
#include "ui/CocosGUI.h"
using namespace cocos2d::ui;
using namespace cocostudio;
using namespace cocos2d;
USING_NS_CC_EXT;

class StartScene : public Scene {
public:
    static Scene* createScene();
    virtual bool init();
    CREATE_FUNC(StartScene);
    void pauseBGmusic(); // ‘›Õ£±≥æ∞“Ù¿÷
    void playBGmusic();  // ≤•∑≈±≥æ∞“Ù¿÷
    void turnOnEffectMusic();  //ø™∆Ù“Ù–ß
    void turnOffEffectMusic();  //πÿ±’“Ù–ß
    bool BGmusic();  //≈–∂œ±≥æ∞“Ù¿÷ «∑Òø™∆Ù
    bool effectMusic();  //≈–∂œ“Ù–ß ‹∑Òø™∆Ù
    void playEffectMusic();

    void BGmusicSelectedEvent(Ref* pSender, cocos2d::ui::CheckBox::EventType type);
    void effectMusicSelectedEvent(Ref* pSender, cocos2d::ui::CheckBox::EventType type);
  //  void NewGameEvent(Ref*,TouchEventType type);
private:
    void initBGimage();  // ≥ı ºªØ±≥æ∞Õº∆¨
    void initBGmusic();  // ≥ı ºªØ±≥æ∞“Ù¿÷
    void loadUI();       // º”‘ÿUI
    bool isBGmusicplaying;
    bool isEffecMusicTurnOn;
};
#endif
