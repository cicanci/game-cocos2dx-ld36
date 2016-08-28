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
    
    return true;
}

void HUDLayer::initMenu()
{
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    auto closeItem = MenuItemImage::create("buttonSunstone.png",
                                           "buttonSunstone.png",
                                           CC_CALLBACK_1(HUDLayer::sunstoneCallback, this));
    
    closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
                                origin.y + closeItem->getContentSize().height/2));
    
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);
    
    auto label = Label::createWithTTF("Sunstone - A Cloudy Day", "fonts/Marker Felt.ttf", 24);
    label->setPosition(Vec2(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - label->getContentSize().height));
    this->addChild(label, 1);
}

void HUDLayer::sunstoneCallback(Ref* pSender)
{
    MapLayer::Instance()->sunstoneCallback(pSender);
}