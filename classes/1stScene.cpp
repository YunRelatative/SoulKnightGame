
#include "1stScene.h"
#include "Weapon.h"
#include "Knight.h"
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
//    ////地图跟随点移动
//    //float x = (float)MAX(position.x, visibleSize.width / 2);
//    //float y = (float)MAX(position.y, visibleSize.height / 2);
//    //获取地图层的地图
//   // auto tiledMap =_;
//
//   // auto tiledMap = m_pMapLayer->getTiledMap();
//    //TMXLayer* wall = _tileMap->getLayer("wall");
//   // TMXLayer* wall = _tileMap->getLayer("wall");
//    //auto tileSize = tiledMap->getTileSize();
//    //auto mapSize = tiledMap->getMapSize();
//    //auto mapSizePixel = Size(tileSize.width * mapSize.width, tileSize.height * mapSize.height);
//    ////不让显示区域超过地图的边界
//    //x = (float)MIN(x, (mapSizePixel.width - visibleSize.width / 2.f));
//    //y = (float)MIN(y, (mapSizePixel.height - visibleSize.height / 2.f));
//    ////实际移动的位置
//    //Point actualPosition = Point(x, y);
//    ////屏幕中心位置坐标
//    //Point centerOfView = Point(visibleSize.width / 2, visibleSize.height / 2);
//
//    //Point delta = centerOfView - actualPosition;
//
//    //Action* action = nullptr;
//
//    ////地图运动
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
//    // 求出屏幕的范围包括宽和高  
//    Size winSize = Director::sharedDirector()->getWinSize();
//    //显示屏幕中心点的坐标大于屏幕宽和高的一半  
//    int x = MAX(position.x, winSize.width / 2);
//    int y = MAX(position.y, winSize.height / 2);
//
//    //求出的是整个瓦片地图的宽  
//    //_tileMap->getMapSize().width瓦片地图横向有多少个瓦片  
//    //_tileMap->getTileSize().width每一个瓦片的宽度  
//    int mapWidth = _tileMap->getMapSize().width * _tileMap->getTileSize().width;
//
//
//    //求出的是整个瓦片地图的高  
//    //_tileMap->getMapSize().height瓦片地图纵向有多少个瓦片  
//    //_tileMap->getTileSize().height每一个瓦片的高度  
//
//    int mapHeight = _tileMap->getMapSize().height * _tileMap->getTileSize().height;
//
//    x = MIN(x, mapWidth - winSize.width / 2);
//    y = MIN(y, mapHeight - winSize.height / 2);
//
//    //目标点  
//    CCPoint actualPoint = ccp(x, y);
//
//    //屏幕的中心点  
//    CCPoint viewCenterPoint = ccp(winSize.width / 2, winSize.height / 2);
//    //计算出重置显示屏幕的中心点  
//    //ccpSub 返回的是viewCenterPoint.x - actualPoint.x和viewCenterPoint.y - actualPoint.y  
//    CCPoint viewPoint = ccpSub(viewCenterPoint, actualPoint);
//    //重置显示屏幕的中心点  
//    this->setPosition(viewPoint);
//
//}
bool SoulKnight::init()
{
    //////////////////////////////
    // 1. super init first
    if (!Scene::init())
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
        closeItem->getContentSize().width <= 0 ||
        closeItem->getContentSize().height <= 0)
    {
        problemLoading("'CloseNormal.png' and 'CloseSelected.png'");
    }
    else
    {
        float x = origin.x + visibleSize.width - closeItem->getContentSize().width / 2;
        float y = origin.y + closeItem->getContentSize().height / 2;
        closeItem->setPosition(Vec2(x, y));
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
        label->setPosition(Vec2(origin.x + visibleSize.width / 2,
            origin.y + visibleSize.height - label->getContentSize().height));

        // add the label as a child to this layer
        this->addChild(label, 1);
    }

    map = TMXTiledMap::create("new-level-1.tmx");
    map->setPosition(-900, -2500);
    addChild(map);
    scheduleUpdate();
    //meta=                               
    _player = Knight::create("Knight.png");
    _player->init();
    _player->setPosition(1470, 2925);
    map->addChild(_player);

    rifle* aWeapon = rifle::create();
    map->addChild(aWeapon);
    aWeapon->setPosition(_player->getPosition());

    return true;
}

void SoulKnight::update(float dt)
{
    cocos2d::Size winSize = cocos2d::Director::getInstance()->getWinSize();
    auto actualPosition = _player->getPosition();
    auto ViewPoint = Point(-900, -2500) - (actualPosition - Point(1470, 2925));
    map->setPosition(ViewPoint);
}

void SoulKnight::menuCloseCallback(Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();
}
