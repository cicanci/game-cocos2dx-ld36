#include "MapLayer.h"

#include "ShipLayer.h"
#include "SunstoneLayer.h"

MapLayer* MapLayer::mInstance = 0;

bool MapLayer::init()
{
    if (!Layer::init())
    {
        return false;
    }
    
    initTouchEvent();
    initBackground();
    
    mSun = Sun::create();
    mSun->retain();
    
    this->scheduleUpdate();
    
    return true;
}

void MapLayer::initBackground()
{
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    auto sprite = Sprite::create("sea.png");
    sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
    sprite->setScale(2);
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
    ShipLayer::Instance()->updateShip(touch->getLocation());
    
    auto visibleSize = Director::getInstance()->getVisibleSize();
    mMoveRight = (touch->getLocation().x > visibleSize.width*0.5f) ? true : false;
    mMoveUp = (touch->getLocation().y > visibleSize.height*0.5f) ? true : false;
    mIsMoving = true;

    return true;
}

void MapLayer::onTouchMoved(Touch *touch, Event *event)
{

}

void MapLayer::onTouchEnded(Touch *touch, Event *event)
{
    log("MapLayer::touchEnd");
    mIsMoving = false;
}

void MapLayer::onTouchCancelled(Touch *touch, Event *event)
{
    onTouchEnded(touch, event);
}

void MapLayer::update(float dt)
{
    if (mIsMoving)
    {
        Vec2 position = this->getPosition();

        if (mMoveRight)
        {
            position.x -= SPEED * dt;
        }
        else
        {
            position.x += SPEED * dt;
        }
        
        if (mMoveUp)
        {
            position.y -= SPEED * dt;
        }
        else
        {
            position.y += SPEED * dt;
        }
        
        this->setPosition(position);
    }
}
