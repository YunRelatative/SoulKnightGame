
#include "1stScene.h"

USING_NS_CC;

Scene* SoulKnight::createScene()
{
   // auto scene = Scene::create();
  //  auto layer = SoulKnight::create();
  //  scene->addChild(layer);

    return SoulKnight::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in SoulKnightScene.cpp\n");
}
//
//void SoulKnight::setViewPointCenter(const Point& position, TMXTiledMap* _tiledMap)
//{
//    ;
//    //float duration = 0.f;
//    //Size visibleSize = Director::getInstance()->getVisibleSize();
//    //const int tag = 10;
//    ////��ͼ������ƶ�
//    //float x = (float)MAX(position.x, visibleSize.width / 2);
//    //float y = (float)MAX(position.y, visibleSize.height / 2);
//    //��ȡ��ͼ��ĵ�ͼ
//   // auto tiledMap =_;
//
//   // auto tiledMap = m_pMapLayer->getTiledMap();
//    //TMXLayer* wall = _tileMap->getLayer("wall");
//   // TMXLayer* wall = _tileMap->getLayer("wall");
//    //auto tileSize = tiledMap->getTileSize();
//    //auto mapSize = tiledMap->getMapSize();
//    //auto mapSizePixel = Size(tileSize.width * mapSize.width, tileSize.height * mapSize.height);
//    ////������ʾ���򳬹���ͼ�ı߽�
//    //x = (float)MIN(x, (mapSizePixel.width - visibleSize.width / 2.f));
//    //y = (float)MIN(y, (mapSizePixel.height - visibleSize.height / 2.f));
//    ////ʵ���ƶ���λ��
//    //Point actualPosition = Point(x, y);
//    ////��Ļ����λ������
//    //Point centerOfView = Point(visibleSize.width / 2, visibleSize.height / 2);
//
//    //Point delta = centerOfView - actualPosition;
//
//    //Action* action = nullptr;
//
//    ////��ͼ�˶�
//    //if (duration < FLT_EPSILON)
//    //{
//    //    action = Place::create(delta);
//    //}
//    //else
//    //{
//    //    action = MoveTo::create(duration, delta);
//    //}
//    //action->setTag(tag);
//
//    //if (tiledMap->getActionByTag(tag) != nullptr)
//    //{
//    //    tiledMap->stopActionByTag(tag);
//    //}
//    //tiledMap->runAction(action);
//}
// on "init" you need to initialize your instance
//void SoulKnight::setViewpointCenter(Point position)
//{
//
//    // �����Ļ�ķ�Χ������͸�  
//    Size winSize = Director::sharedDirector()->getWinSize();
//    //��ʾ��Ļ���ĵ�����������Ļ��͸ߵ�һ��  
//    int x = MAX(position.x, winSize.width / 2);
//    int y = MAX(position.y, winSize.height / 2);
//
//    //�������������Ƭ��ͼ�Ŀ�  
//    //_tileMap->getMapSize().width��Ƭ��ͼ�����ж��ٸ���Ƭ  
//    //_tileMap->getTileSize().widthÿһ����Ƭ�Ŀ��  
//    int mapWidth = _tileMap->getMapSize().width * _tileMap->getTileSize().width;
//
//
//    //�������������Ƭ��ͼ�ĸ�  
//    //_tileMap->getMapSize().height��Ƭ��ͼ�����ж��ٸ���Ƭ  
//    //_tileMap->getTileSize().heightÿһ����Ƭ�ĸ߶�  
//
//    int mapHeight = _tileMap->getMapSize().height * _tileMap->getTileSize().height;
//
//    x = MIN(x, mapWidth - winSize.width / 2);
//    y = MIN(y, mapHeight - winSize.height / 2);
//
//    //Ŀ���  
//    CCPoint actualPoint = ccp(x, y);
//
//    //��Ļ�����ĵ�  
//    CCPoint viewCenterPoint = ccp(winSize.width / 2, winSize.height / 2);
//    //�����������ʾ��Ļ�����ĵ�  
//    //ccpSub ���ص���viewCenterPoint.x - actualPoint.x��viewCenterPoint.y - actualPoint.y  
//    CCPoint viewPoint = ccpSub(viewCenterPoint, actualPoint);
//    //������ʾ��Ļ�����ĵ�  
//    this->setPosition(viewPoint);
//
//}
bool SoulKnight::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Scene::init())
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    ///////////////////////////
  //   2. add a menu item with "X" image, which is clicked to quit the program
  //      you may modify it.
  //   add a "close" icon to exit the progress. it's an autorelease object
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(SoulKnight::menuCloseCallback, this));

    if (closeItem == nullptr ||
        closeItem ->getContentSize().width <= 0 ||
        closeItem->getContentSize().height <= 0)
    {
        problemLoading("'CloseNormal.png' and 'CloseSelected.png'");
    }
    else
    {
        float x = origin.x + visibleSize.width - closeItem->getContentSize().width/2;
        float y = origin.y + closeItem->getContentSize().height/2;
        closeItem->setPosition(Vec2(x,y));
    }

    //// create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    ///////////////////////////////
    //// 3. add your codes below...
    //// add a label shows "Hello World"
    //// create and initialize a label

    auto label = Label::createWithTTF("SoulKnight", "fonts/cube.ttf", 36);
    if (label == nullptr)
    {
        problemLoading("'fonts/cube.ttf'");
    }
    else
    {
        // position the label on the center of the screen
        label->setPosition(Vec2(origin.x + visibleSize.width/2,
                                origin.y + visibleSize.height - label->getContentSize().height));

        // add the label as a child to this layer
        this->addChild(label, 1);
    }
    
    TMXTiledMap* _tileMap = TMXTiledMap::create("new-level-1.tmx");
    _tileMap->setPosition(-900,-2500);
        addChild(_tileMap);
    //  //  TMXLayer* wall = _tileMap->getLayer("wall");
         auto _player = Sprite::create("Knight.png");
         _player->setPosition(1470, 2925);
        /*auto objectsValue = _tileMap->getObjectGroup("player");
        auto spawnPoint = objectsValue->getObject("player");
        Point heroPoint;
        heroPoint.x = spawnPoint.at("x").asFloat();
        heroPoint.y = spawnPoint.at("y").asFloat();*/
    //  // _player->setAnchorPoint(Point(0, 0));
    ////    _player->setPosition(heroPoint);
         _tileMap->addChild(_player);
     //   SoulKnight::setViewPointCenter(_player->getPosition(),_tileMap);
    return true;
}

void SoulKnight::SetCenterPoint(Point center, TMXTiledMap* _tileMap)
{
    cocos2d::Size winSize = cocos2d::Director::getInstance()->getWinSize();
    int x =MAX(center.x, winSize.width) / 2;
    int y = MAX(center.y, winSize.height) / 2;
    int mapSize = center.x / _tileMap->getContentSize().width * _tileMap->getMapSize().width;
    //x = MIN(x, mapSize.width * tileSize.width - winSize.width / 2);
    //y = MIN(y, mapSize.height * tileSize.height - winSize.height / 2);
}
void SoulKnight::menuCloseCallback(Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();
}
