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
    mStartPosition = Vec2(0, 0);

    this->scheduleUpdate();
    
    return true;
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

void MapLayer::initBackground()
{
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    mMapPosition = Vec2(visibleSize.width*0.5f + origin.x, visibleSize.height*0.5f + origin.y);
    
    auto sprite = Sprite::create("sea.png");
    sprite->setPosition(mMapPosition);
    sprite->setScale(2);
    this->addChild(sprite, 0);
    
    mIsland = Sprite::create("island.png");
    mIsland->setVisible(false);
    this->addChild(mIsland, 1);
    
    Vec2 position = Vec2(this->getPosition().x + visibleSize.width*0.5f,
                         this->getPosition().y + visibleSize.height*0.5f + 25);
    Rect ship = Rect(position.x, position.y, 75, 25);
    mShipDebug = Sprite::create("debug.png", ship);
    mShipDebug->setPosition(position);
    mShipDebug->setVisible(false);
    this->addChild(mShipDebug, 2);
}

void MapLayer::showSunstone()
{
    if (!SunstoneLayer::Instance()->isVisible())
    {
        _eventDispatcher->removeEventListener(mTouchListener);
    }
    else
    {
        _eventDispatcher->addEventListenerWithSceneGraphPriority(mTouchListener, this);
    }
    
    SunstoneLayer::Instance()->show(SunLayer::Instance()->getSunPosition());
}

void MapLayer::reloadLevel()
{
    SunLayer::Instance()->generate();
}

bool MapLayer::onTouchBegan(Touch* touch, Event* event)
{
    log("MapLayer::touchBegan");
    onTouchMoved(touch, event);
    return true;
}

void MapLayer::onTouchMoved(Touch *touch, Event *event)
{
    ShipLayer::Instance()->updateShip(touch->getLocation());

    auto visibleSize = Director::getInstance()->getVisibleSize();
    mMoveRight = (touch->getLocation().x > visibleSize.width*0.5f) ? true : false;
    mMoveUp = (touch->getLocation().y > visibleSize.height*0.5f) ? true : false;
    mIsMoving = true;
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
        Vec2 position = Vec2::ZERO;

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
        
        this->setPosition(this->getPosition() + position);
        mShipDebug->setPosition(mShipDebug->getPosition() + ((-1)*position));
        
        checkCollision();
    }
}

void MapLayer::checkCollision()
{
    Rect island = Rect(mIsland->getPosition().x,
                       mIsland->getPosition().y,
                       mIsland->getContentSize().width,
                       mIsland->getContentSize().height);
    
    Rect ship = Rect(mShipDebug->getPosition().x,
                     mShipDebug->getPosition().y,
                     mShipDebug->getContentSize().width,
                     mShipDebug->getContentSize().height);

    if (island.intersectsRect(ship))
    {
        log("BIRL!!!!!!!");
    }
}

int MapLayer::getDistanceFromCenter()
{
    float distance = mStartPosition.distance(this->getPosition());
    return static_cast<int>(distance);
}

int MapLayer::getDistanceFromObjective()
{
    float distance = mStartPosition.distance(mObjectivePosition);
    return static_cast<int>(distance);
}

void MapLayer::setObjectivePosition(Vec2 position)
{
    mObjectivePosition = position - mMapPosition;
    
    if (!mIsland->isVisible())
    {
        mIsland->setVisible(true);
    }
    mIsland->setPosition(position);
}

