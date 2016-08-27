#include "Sunstone.h"

Sunstone::Sunstone()
{
    initTouchEvent();
    initSprites();
}

Sunstone::~Sunstone()
{
    
}

void Sunstone::initSprites()
{
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    mSunstone = Sprite::create("sunstone.png");
    mSunstone->setPosition(Vec2(visibleSize.width*0.5f + origin.x, visibleSize.height*0.5f + origin.y));
    this->addChild(mSunstone, 0);
    
    mDotUp = Sprite::create("dot.png");
    mDotUp->setPosition(Vec2(mSunstone->getPosition().x - mDotUp->getContentSize().width*2,
                             mSunstone->getPosition().y + mDotUp->getContentSize().height*0.5f));
    this->addChild(mDotUp, 1);
    
    mDotDown = Sprite::create("dot.png");
    mDotDown->setPosition(Vec2(mSunstone->getPosition().x - mDotDown->getContentSize().width*2,
                               mSunstone->getPosition().y));
    this->addChild(mDotDown, 1);
    
    mSunPosition = Vec2(0, 0);
}

void Sunstone::initTouchEvent()
{
    auto listener1 = EventListenerTouchOneByOne::create();
    
    listener1->onTouchBegan = [](Touch* touch, Event* event)
    {
        return true;
    };
    
    listener1->onTouchMoved = [=](Touch* touch, Event* event)
    {
        Sunstone::touchEvent(touch);
    };
    
    listener1->onTouchEnded = [=](Touch* touch, Event* event)
    {

    };
    
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener1, this);
}

void Sunstone::touchEvent(Touch* touch)
{
    auto visibleSize = Director::getInstance()->getVisibleSize();

    float opacityX = 255 - ((255 * touch->getLocation().x) / (visibleSize.width - mSunPosition.x));
    float opacityY = 255 - ((255 * touch->getLocation().y) / (visibleSize.height - mSunPosition.y));
    
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
    
    log("Touch: (%f, %f) (%f, %f)", touch->getLocation().x, touch->getLocation().y, opacityX, opacityY);
    mDotUp->setOpacity(opacityX);
    mDotDown->setOpacity(opacityY);
    
    mSunstone->setPosition(touch->getLocation());
    mDotUp->setPosition(Vec2(mSunstone->getPosition().x - mDotUp->getContentSize().width,
                             mSunstone->getPosition().y + mDotUp->getContentSize().height*0.5f));
    mDotDown->setPosition(Vec2(mSunstone->getPosition().x - mDotDown->getContentSize().width,
                               mSunstone->getPosition().y));
}
