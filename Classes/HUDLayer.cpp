#include "HUDLayer.h"

#include "MapLayer.h"
#include "SunstoneLayer.h"

bool HUDLayer::init()
{
    if (!Layer::init())
    {
        return false;
    }
    
    initMenu();
    
    this->scheduleUpdate();
    
    return true;
}

void HUDLayer::initMenu()
{
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    auto closeItem = MenuItemImage::create("buttonSunstone.png",
                                           "buttonSunstone.png",
                                           CC_CALLBACK_1(HUDLayer::sunstoneCallback, this));
    
    closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width*0.5f,
                                origin.y + closeItem->getContentSize().height*0.5f));
    
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);
    
    mDistance = Label::createWithTTF("Distance from center: 0", "fonts/Marker Felt.ttf", 24);
    mDistance->setPosition(Vec2(origin.x + visibleSize.width*0.5f,
                                origin.y + visibleSize.height - mDistance->getContentSize().height));
    mDistance->enableOutline(Color4B::BLACK, 1);
    this->addChild(mDistance, 1);
    
    mDirection = Label::createWithTTF("Go: NONE", "fonts/Marker Felt.ttf", 14);
    mDirection->setPosition(Vec2(origin.x + visibleSize.width*0.5f,
                                 mDistance->getPosition().y - mDistance->getContentSize().height));
    mDirection->enableOutline(Color4B::RED, 1);
    this->addChild(mDirection, 1);
}

void HUDLayer::sunstoneCallback(Ref* pSender)
{
    MapLayer::Instance()->sunstoneCallback(pSender);
}

void HUDLayer::update(float dt)
{
    std::string distance = StringUtils::format("Distance from center: %dm",
                                          static_cast<int>(MapLayer::Instance()->getDistance()));
    mDistance->setString(distance.c_str());
    
    std::string direction = StringUtils::format("Go: %s", MapLayer::Instance()->getDirection().c_str());
    mDirection->setString(direction.c_str());
}
