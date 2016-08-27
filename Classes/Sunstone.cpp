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
    
    std::vector<Vec2> possiblePositions(8);
    possiblePositions[0] = Vec2(0, 0);
    possiblePositions[1] = Vec2(0, visibleSize.height*0.5f);
    possiblePositions[2] = Vec2(0, visibleSize.height);
    possiblePositions[3] = Vec2(visibleSize.width*0.5f, visibleSize.height);
    possiblePositions[4] = Vec2(visibleSize.width, visibleSize.height);
    possiblePositions[5] = Vec2(visibleSize.width, visibleSize.height*0.5f);
    possiblePositions[6] = Vec2(visibleSize.width, 0);
    possiblePositions[7] = Vec2(visibleSize.width*0.5f, 0);
    
    int dice_roll = random(0, 8);
    mSunPosition = possiblePositions[dice_roll];
    log("Sun is at [%d] %f, %f", dice_roll, mSunPosition.x, mSunPosition.y);
    
    mSunstone = Sprite::create("sunstone.png");
    this->addChild(mSunstone, 0);
    
    mDotUp = Sprite::create("dot.png");
    this->addChild(mDotUp, 1);
    
    mDotDown = Sprite::create("dot.png");
    this->addChild(mDotDown, 1);
    
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    updateOpacity(Vec2(visibleSize.width*0.5f + origin.x, visibleSize.height*0.5f + origin.y));
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

void Sunstone::updateOpacity(Vec2 position)
{
    float opacityX = 255 - std::abs(mSunPosition.x - position.x);
    float opacityY = 255 - std::abs(mSunPosition.y - position.y);
    
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
    
    log("Touch: (%f, %f) Opacity: (%f, %f)", position.x, position.y, opacityX, opacityY);
    mDotUp->setOpacity(opacityX);
    mDotDown->setOpacity(opacityY);
    
    mSunstone->setPosition(position);
    mDotUp->setPosition(Vec2(mSunstone->getPosition().x - mDotUp->getContentSize().width,
                             mSunstone->getPosition().y + mDotUp->getContentSize().height*0.5f));
    mDotDown->setPosition(Vec2(mSunstone->getPosition().x - mDotDown->getContentSize().width,
                               mSunstone->getPosition().y));
}

void Sunstone::touchEvent(Touch* touch)
{
    updateOpacity(touch->getLocation());
}
