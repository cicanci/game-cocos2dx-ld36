#include "MapLayer.h"

#include "SunstoneLayer.h"

bool MapLayer::init()
{
    if (!Layer::init())
    {
        return false;
    }
    
    initMenu();
    initTouchEvent();
    
    mSun = Sun::create();
    mSun->retain();
    
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    mShip = Sprite::create("ship.png");
    mShip->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
    this->addChild(mShip, 0);
    
    this->scheduleUpdate();
    
    return true;
}

void MapLayer::initMenu()
{
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    auto closeItem = MenuItemImage::create("buttonSunstone.png",
                                           "buttonSunstone.png",
                                           CC_CALLBACK_1(MapLayer::sunstoneCallback, this));
    
    closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
                                origin.y + closeItem->getContentSize().height/2));
    
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);
    
    auto label = Label::createWithTTF("Sunstone - A Cloudy Day", "fonts/Marker Felt.ttf", 24);
    label->setPosition(Vec2(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - label->getContentSize().height));
    this->addChild(label, 1);
    
    auto sprite = Sprite::create("HelloWorld.png");
    sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
    this->addChild(sprite, 0);
}

void MapLayer::sunstoneCallback(Ref* pSender)
{
    if (!SunstoneLayer::Instance()->isVisible())
    {
        _eventDispatcher->removeEventListener(mTouchListener);
    }
    else
    {
        _eventDispatcher->addEventListenerWithSceneGraphPriority(mTouchListener, this);
    }

    SunstoneLayer::Instance()->show(mSun->getSunPosition());
}

void MapLayer::initTouchEvent()
{
    mTouchListener = EventListenerTouchOneByOne::create();
    //mTouchListener->setSwallowTouches(true);
    mTouchListener->retain();
    
    mTouchListener->onTouchBegan = CC_CALLBACK_2(MapLayer::onTouchBegan, this);
    mTouchListener->onTouchMoved = CC_CALLBACK_2(MapLayer::onTouchMoved, this);
    mTouchListener->onTouchEnded = CC_CALLBACK_2(MapLayer::onTouchEnded, this);
    mTouchListener->onTouchCancelled = CC_CALLBACK_2(MapLayer::onTouchCancelled, this);

    _eventDispatcher->addEventListenerWithSceneGraphPriority(mTouchListener, this);
}

bool MapLayer::onTouchBegan(Touch* touch, Event* event)
{
    log("MapLayer::touchBegan");
    return true;
}

void MapLayer::onTouchMoved(Touch *touch, Event *event)
{
    
}

void MapLayer::onTouchEnded(Touch *touch, Event *event)
{
    log("MapLayer::touchEnd");
}

void MapLayer::onTouchCancelled(Touch *touch, Event *event)
{
    onTouchEnded(touch, event);
}

void MapLayer::update(float dt)
{
    
}