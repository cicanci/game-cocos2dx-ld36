#include "MessageLayer.h"

#include "ShipLayer.h"

MessageLayer* MessageLayer::mInstance = 0;

bool MessageLayer::init()
{
    if (!Layer::init())
    {
        return false;
    }
    
    initMessage();
    
    return true;
}

void MessageLayer::initMessage()
{
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    mMessageBox = Sprite::create("messageBox.png");
    mMessageBox->setPosition(Vec2(visibleSize.width*0.5f + origin.x, visibleSize.height*0.5f + origin.y));
    this->addChild(mMessageBox, 0);
    
    mAddSpeed = MenuItemImage::create("buttonAdd.png", "buttonAdd.png",
                                      CC_CALLBACK_1(MessageLayer::addSpeedCallback, this));
    mAddSpeed->setPosition(mMessageBox->getPosition() + Vec2(50, 0));
    
    mAddBonus = MenuItemImage::create("buttonAdd.png", "buttonAdd.png",
                                      CC_CALLBACK_1(MessageLayer::addBonusCallback, this));
    mAddBonus->setPosition(mMessageBox->getPosition() + Vec2(50, -50));
    
    mCloseMessage = MenuItemImage::create("buttonClose.png", "buttonClose.png",
                                      CC_CALLBACK_1(MessageLayer::closeCallback, this));
    mCloseMessage->setPosition(Vec2(mMessageBox->getPosition().x + mMessageBox->getContentSize().width*0.5f - 25,
                                    mMessageBox->getPosition().y + mMessageBox->getContentSize().height*0.5f - 25));
    
    auto menu = Menu::create(mAddSpeed, mAddBonus, mCloseMessage, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);
    
    createLabel(24, Color4B::BLACK, "Upgrade your ship", mMessageBox->getPosition() - Vec2(50, -50));
    mCurrentSpeed = createLabel(24, Color4B::BLACK, "Speed: +0", mMessageBox->getPosition() - Vec2(50, 0));
    mCurrentBonus = createLabel(24, Color4B::BLACK, "Bonus: +0", mMessageBox->getPosition() - Vec2(50, 50));
}

Label* MessageLayer::createLabel(int size, Color4B border, std::string text, Vec2 position)
{
    auto label = Label::createWithTTF(text.c_str(), "fonts/Marker Felt.ttf", size);
    label->enableOutline(border, 1);
    label->setPosition(position);
    this->addChild(label, 1);
    return label;
}

void MessageLayer::addSpeedCallback(Ref *pSender)
{
    ShipLayer::Instance()->addSpeedUpgrade();
    mAddSpeed->setVisible(false);
    mAddBonus->setVisible(false);
    mCloseMessage->setVisible(true);
    
    std::string speed = StringUtils::format("Speed: +%d", ShipLayer::Instance()->getSpeedUpgrade());
    mCurrentSpeed->setString(speed.c_str());
}

void MessageLayer::addBonusCallback(Ref *pSender)
{
    ShipLayer::Instance()->addBonusUpgrade();
    mAddBonus->setVisible(false);
    mAddSpeed->setVisible(false);
    mCloseMessage->setVisible(true);
    
    std::string bonus = StringUtils::format("Bonus: +%d", ShipLayer::Instance()->getBonusUpgrade());
    mCurrentBonus->setString(bonus.c_str());
}

void MessageLayer::closeCallback(Ref *pSender)
{
    closeMessage();
}

void MessageLayer::showMessage()
{
    this->setVisible(true);
    mAddBonus->setVisible(true);
    mAddSpeed->setVisible(true);
    mCloseMessage->setVisible(false);
}

void MessageLayer::closeMessage()
{
    this->setVisible(false);
}
