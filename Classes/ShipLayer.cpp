#include "ShipLayer.h"

ShipLayer* ShipLayer::mInstance = 0;

bool ShipLayer::init()
{
    if (!Layer::init())
    {
        return false;
    }
    
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    mShip = Sprite::create("ship.png");
    mShip->setPosition(Vec2(visibleSize.width*0.5f + origin.x, visibleSize.height*0.5f + origin.y));
    this->addChild(mShip, 1);
    
    mSpeedUpgrade = 0;
    mBonusUpgrade = 0;
    
    return true;
}

void ShipLayer::updateShip(Vec2 touch)
{
    float angle = atan2f(touch.x - mShip->getPosition().x, touch.y - mShip->getPosition().y);
    angle = CC_RADIANS_TO_DEGREES(angle) + 90;
    
    mShip->setRotation(angle);
}
