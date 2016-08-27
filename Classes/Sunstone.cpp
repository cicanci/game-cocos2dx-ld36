#include "Sunstone.h"

#include "Sun.h"

Sunstone* Sunstone::mInstance = 0;

bool Sunstone::init()
{
    if (!Layer::init())
    {
        return false;
    }
    
    initTouchEvent();
    initSprites();
    setInitialPosition();
    
    return true;
}

void Sunstone::initTouchEvent()
{
    mTouchListener = EventListenerTouchOneByOne::create();
//    mTouchListener->setSwallowTouches(true);
    mTouchListener->retain();
    
    mTouchListener->onTouchBegan = [](Touch* touch, Event* event)
    {
        log("Sunstone::touchBegan");
        return true;
    };
    
    mTouchListener->onTouchMoved = [=](Touch* touch, Event* event)
    {
        Sunstone::touchEvent(touch);
    };
    
    mTouchListener->onTouchEnded = [=](Touch* touch, Event* event)
    {
        log("Sunstone::touchEnd");
    };
}

void Sunstone::initSprites()
{
    mSunstone = Sprite::create("sunstone.png");
    this->addChild(mSunstone, 0);
    
    mDotUp = Sprite::create("dot.png");
    this->addChild(mDotUp, 1);
    
    mDotDown = Sprite::create("dot.png");
    this->addChild(mDotDown, 1);
}

void Sunstone::setInitialPosition()
{
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    Vec2 initialPosition = Vec2(visibleSize.width*0.5f + origin.x, visibleSize.height*0.5f + origin.y);
    updateOpacity(initialPosition, mSunPosition);
}

void Sunstone::updateOpacity(Vec2 touch, Vec2 sun)
{
    float opacityX = 255 - std::abs(sun.x - touch.x);
    float opacityY = 255 - std::abs(sun.y - touch.y);
    
    if (opacityX < 0)
    {
        opacityX = 0;
    }
    else if (opacityX > 255)
    {
        opacityX = 255;
    }
    
    if (opacityY < 0)
    {
        opacityY = 0;
    }
    else if (opacityY > 255)
    {
        opacityY = 255;
    }
    
    log("Touch: (%f, %f) Opacity: (%f, %f)", touch.x, touch.y, opacityX, opacityY);
    mDotUp->setOpacity(opacityX);
    mDotDown->setOpacity(opacityY);
    
    mSunstone->setPosition(touch);
    mDotUp->setPosition(Vec2(mSunstone->getPosition().x - mDotUp->getContentSize().width,
                             mSunstone->getPosition().y + mDotUp->getContentSize().height*0.5f));
    mDotDown->setPosition(Vec2(mSunstone->getPosition().x - mDotDown->getContentSize().width,
                               mSunstone->getPosition().y));
}

void Sunstone::touchEvent(Touch* touch)
{
    updateOpacity(touch->getLocation(), mSunPosition);
}

void Sunstone::show(Vec2 sun)
{
    mSunPosition = sun;
    this->setVisible(!this->isVisible());

    if (this->isVisible())
    {
        setInitialPosition();
        _eventDispatcher->addEventListenerWithSceneGraphPriority(mTouchListener, this);
    }
    else
    {
        _eventDispatcher->removeEventListener(mTouchListener);
    }
}