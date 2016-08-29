#include "HUDLayer.h"

#include "MapLayer.h"
#include "SunLayer.h"
#include "SunstoneLayer.h"

HUDLayer* HUDLayer::mInstance = 0;

bool HUDLayer::init()
{
    if (!Layer::init())
    {
        return false;
    }
    
    initMenu();
    initText();
    
    this->scheduleUpdate();
    
    return true;
}

void HUDLayer::initMenu()
{
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    auto sunstone = MenuItemImage::create("buttonSunstone.png",
                                           "buttonSunstone.png",
                                           CC_CALLBACK_1(HUDLayer::sunstoneCallback, this));
    
    sunstone->setPosition(Vec2(origin.x + visibleSize.width - sunstone->getContentSize().width*0.5f,
                                origin.y + sunstone->getContentSize().height*0.5f));
    
    auto reload = MenuItemImage::create("buttonReload.png",
                                        "buttonReload.png",
                                        CC_CALLBACK_1(HUDLayer::reloadCallback, this));
    
    reload->setPosition(Vec2(origin.x + reload->getContentSize().width*0.5f,
                               origin.y + reload->getContentSize().height*0.5f));
    
    auto menu = Menu::create(sunstone, reload, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);
}

void HUDLayer::initText()
{
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    mDirection = createLabel(24, Color4B::RED);
    mDirection->setPosition(Vec2(origin.x + visibleSize.width*0.5f,
                                 origin.y + visibleSize.height - mDirection->getContentSize().height));
    
    mDistance = createLabel(14, Color4B::BLACK);
    mDistance->setPosition(Vec2(origin.x + visibleSize.width*0.5f,
                                mDirection->getPosition().y - mDirection->getContentSize().height));
    
    mTime = createLabel(14, Color4B::BLACK);
    mTime->setPosition(Vec2(origin.x + visibleSize.width*0.5f,
                            mDistance->getPosition().y - mDistance->getContentSize().height));
    
    updateText();
}

void HUDLayer::updateText()
{
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
    MapLayer::Instance()->showSunstone();
}

void HUDLayer::reloadCallback(Ref* pSender)
{
    MapLayer::Instance()->reloadLevel();
}

void HUDLayer::update(float dt)
{
    std::string distance = StringUtils::format("Distance from center: %dm",
                                          MapLayer::Instance()->getDistanceFromCenter());
    mDistance->setString(distance.c_str());
}
