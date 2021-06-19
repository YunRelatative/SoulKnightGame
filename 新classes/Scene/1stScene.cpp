#include "Scene/1stScene.h"
USING_NS_CC;
using namespace std;
Scene* SoulKnight::createScene()
{
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

    weapon* aWeapon = shotGun::create();
     _player = Knight::create(aWeapon);

    map->setPosition(-900, -3100);
    addChild(map);
    _meta->setVisible(false);
    _player->setScale(0.6);
   // map->setScale(1.4);
   // _player->setPosition(1470, 2925);
    // Inside the init method, after setting "_background =" 
    CCASSERT(NULL != objects, "'Objects' object group not found");
    auto spawnPoint = objects->getObject("SpawnPoint");
    CCASSERT(!spawnPoint.empty(), "SpawnPoint object not found");
    int x = spawnPoint["x"].asInt();
    int y = spawnPoint["y"].asInt();
    _player->setPosition(x, y);
  //  setViewPointCenter(_player->getPosition());
    map->addChild(_player);
    
    //aWeapon->setScale(0.6);
    //aWeapon->setPosition(x + 13, y - 13);
    //map->addChild(aWeapon);
    //_player->addChild(aWeapon);
    scheduleUpdate();
    return true;
}
void SoulKnight::collisionStand()
{
    float x = this->getPositionX();				//���hero��x����λ��
    float y = this->getPositionY();				//���hero��y����λ��
    int offset = 2;								//�����ϰ�����ֹ��������΢С�ƶ���ƫ����
    ////��ֹͣʱ�����ﱳ������΢�ƶ�2����,��ֹ������ͼ���п���.
    //if (hState == LEFT)
    //	this->setPosition(x + offset, y);
    //else if (hState == UP)
    //	this->setPosition(x, y - offset);
    //else if (hState == RIGHT)
    //	this->setPosition(x - offset, y);
    //else if (hState == DOWN)
    //	this->setPosition(x, y + offset);
    //hState = STAND;								//��������״̬Ϊվ��
 //   _player->stopAllActions();					//ֹͣ�����߶�����
    _player->stopAllActions();						//ֹͣ�����߶�����

}
void SoulKnight::update(float dt)
{
    cocos2d::Size winSize = cocos2d::Director::getInstance()->getWinSize();
    auto actualPosition = _player->getPosition();
    Point ViewPoint = Point(-900, -2500) - (actualPosition - Point(1470, 2925));
    map->setPosition(ViewPoint);

    //aWeapon->setPosition(_player->getPosition());

    // if (this->isTilePosBlocked(_player->getPosition()))
   /* if (this->IfCollidable(_player->getPosition()))
        collisionStand();*/
  //  Point tileCoord = SoulKnight::tileCoordForPosition(_player->getPosition());
}
//Point SoulKnight::tileCoordForPosition(Point position)//ת���ɵ�ͼ����
//{
//    int x = position.x / map->getTileSize().width - 8;
//    int y = ((map->getMapSize().height * map->getTileSize().height) - position.y) / map->getTileSize().height+17;
//    return Point(x, y);
//}

 Point SoulKnight::tilePosFromLocation(Point l)
{
    int x = l.x / map->getTileSize().width;
    int y = l.y / map->getTileSize().height;

    y = y - map->getMapSize().height;
    return Vec2(x, y);
}
//�жϸ���Ƭ�Ƿ�Ϊ�ϰ�
bool SoulKnight::isTilePosBlocked(Point l)
{
    //�жϵ�ǰ���Ƿ�Ϊ��ײ��
    Point tilpos = tilePosFromLocation(l);				//�����������תΪ������
    //TMXLayer* clayer = ->layerNamed("collision");		//ͨ�������ֻ�øò����
    //clayer->setVisible(true);
    int tileGID = _meta->getTileGIDAt(tilpos);				//��øÿ��GID��ʶ��
    auto properties = map->getPropertiesForGID(1).asValueMap();
    if (tileGID != 0)
    {

        if (properties["Collidable"].asString()== "True")//������ײ��meta��
            return true;
    }
    return false;
}

//bool SoulKnight::IfCollidable(Point position)
//{
//    position = tileCoordForPosition(position);
//    int tileGid = _meta->getTileGIDAt(position);
//    if (tileGid ==14338|| tileGid == 14354)//����ǽ��
//        return 1;
//    else 
//    return 0;
//}


void SoulKnight::menuCloseCallback(Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();
}
