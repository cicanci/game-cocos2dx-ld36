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
    initDirection();

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
    mStartPosition = Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y);
    
    auto sprite = Sprite::create("sea.png");
    sprite->setPosition(mStartPosition);
    sprite->setScale(2);
    this->addChild(sprite, 0);
}

void MapLayer::initDirection()
{
    std::vector<std::string> directions(4);
    directions[0] = "EAST";
    directions[1] = "WEST";
    directions[2] = "NORTH";
    directions[3] = "SOUTH";
    
    mCardinalDirection = static_cast<CardinalDirection>(random(0, 3));
    mDirectionName = directions[mCardinalDirection];
}

void MapLayer::sunstoneCallback(Ref* pSender)
{
    SunLayer::Instance()->generate();
    
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

float MapLayer::getDistance()
{
    return mStartPosition.distance(this->getPosition());
}
