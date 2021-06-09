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
    void pauseBGmusic(); // ��ͣ��������
    void playBGmusic();  // ���ű�������
    void turnOnEffectMusic();  //������Ч
    void turnOffEffectMusic();  //�ر���Ч
    bool BGmusic();  //�жϱ��������Ƿ���
    bool effectMusic();  //�ж���Ч�ܷ���
    void playEffectMusic();

    void BGmusicSelectedEvent(Ref* pSender, cocos2d::ui::CheckBox::EventType type);
    void effectMusicSelectedEvent(Ref* pSender, cocos2d::ui::CheckBox::EventType type);
  //  void NewGameEvent(Ref*,TouchEventType type);
private:
    void initBGimage();  // ��ʼ������ͼƬ
    void initBGmusic();  // ��ʼ����������
    void loadUI();       // ����UI
    bool isBGmusicplaying;
    bool isEffecMusicTurnOn;
};
#endif
