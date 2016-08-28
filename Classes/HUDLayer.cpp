#include "HUDLayer.h"

#include "MapLayer.h"
#include "SunLayer.h"
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
    
    mDirection = createLabel(24, Color4B::RED);
    mDirection->setPosition(Vec2(origin.x + visibleSize.width*0.5f,
                                origin.y + visibleSize.height - mDirection->getContentSize().height));
    
    mDistance = createLabel(14, Color4B::BLACK);
    mDistance->setPosition(Vec2(origin.x + visibleSize.width*0.5f,
                                 mDirection->getPosition().y - mDirection->getContentSize().height));
    
    mTime = createLabel(14, Color4B::BLACK);
    mTime->setPosition(Vec2(origin.x + visibleSize.width*0.5f,
                                mDistance->getPosition().y - mDistance->getContentSize().height));
    
    // Update text
    std::string direction = StringUtils::format("Objective: Go %s, %dm",
                                                SunLayer::Instance()->getDirection().c_str(),
                                                MapLayer::Instance()->getDistanceFromObjective());
    mDirection->setString(direction.c_str());
    
    std::string time = StringUtils::format("Sun position: %s", SunLayer::Instance()->getSunTime().c_str());
    mTime->setString(time.c_str());
}

Label* HUDLayer::createLabel(int size, Color4B border)
{
    auto label = Label::createWithTTF("LABEL", "fonts/Marker Felt.ttf", size);
    label->enableOutline(border, 1);
    this->addChild(label, 1);
    return label;
}

void HUDLayer::sunstoneCallback(Ref* pSender)
{
    MapLayer::Instance()->sunstoneCallback(pSender);
}

void HUDLayer::update(float dt)
{
    std::string distance = StringUtils::format("Distance from center: %dm",
                                          MapLayer::Instance()->getDistanceFromCenter());
    mDistance->setString(distance.c_str());
}
