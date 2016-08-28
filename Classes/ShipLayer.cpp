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
    mShip->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
    this->addChild(mShip, 1);
    
    return true;
}

void ShipLayer::updateShip(Vec2 touch)
{
    float angle = atan2f(touch.y - mShip->getPosition().y, touch.x - mShip->getPosition().x);
    angle = CC_RADIANS_TO_DEGREES(angle);
    
    if (angle < 0)
    {
        angle += 360;
    }
    
    //    angle += (touch->getLocation().x - mShip->getPosition().x) < 0 ? 90 : -90;
    log("angle: %f", angle);
    
    //    auto rotateTo = RotateBy::create(0.5f, angle);
    //    mShip->runAction(rotateTo);
    mShip->setRotation(angle);
}