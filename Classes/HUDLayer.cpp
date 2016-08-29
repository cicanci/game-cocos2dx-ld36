#include "HUDLayer.h"

#include "MapLayer.h"
#include "ShipLayer.h"
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
    mCounter = GAME_TIME;
    mScoreValue = 0;
    
    this->scheduleUpdate();
    
    return true;
}

void HUDLayer::initMenu()
{
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    mSunstoneButton = MenuItemImage::create("buttonSunstone.png",
                                           "buttonSunstone.png",
                                           CC_CALLBACK_1(HUDLayer::sunstoneCallback, this));
    
    mSunstoneButton->setPosition(Vec2(origin.x + visibleSize.width - mSunstoneButton->getContentSize().width*0.5f,
                                origin.y + mSunstoneButton->getContentSize().height*0.5f));
    
    mReloadButton = MenuItemImage::create("buttonReload.png",
                                        "buttonReload.png",
                                        CC_CALLBACK_1(HUDLayer::reloadCallback, this));
    
    mReloadButton->setPosition(Vec2(origin.x + mReloadButton->getContentSize().width*0.5f,
                               origin.y + mReloadButton->getContentSize().height*0.5f));
    
    auto menu = Menu::create(mSunstoneButton, mReloadButton, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);
}

void HUDLayer::initText()
{
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    mDirection = createLabel(32, Color4B::RED);
    mDirection->setPosition(Vec2(origin.x + visibleSize.width*0.5f,
                                 origin.y + visibleSize.height - mDirection->getContentSize().height));
    
    mDistance = createLabel(18, Color4B::BLACK);
    mDistance->setPosition(Vec2(origin.x + visibleSize.width*0.5f,
                                mDirection->getPosition().y - mDirection->getContentSize().height));
    
    mTime = createLabel(18, Color4B::BLACK);
    mTime->setPosition(Vec2(origin.x + visibleSize.width*0.5f,
                            mDistance->getPosition().y - mDistance->getContentSize().height));
    
    mCountDown = createLabel(18, Color4B::BLACK);
    mCountDown->setString("Time left: 000s");
    mCountDown->setPosition(Vec2(origin.x + mCountDown->getContentSize().width*0.5f,
                            origin.y + visibleSize.height - mCountDown->getContentSize().height));
    
    mScore = createLabel(18, Color4B::BLACK);
    mScore->setString("Score: 000");
    mScore->setPosition(Vec2(origin.x + visibleSize.width - (mCountDown->getContentSize().width*0.5f),
                                 origin.y + visibleSize.height - mCountDown->getContentSize().height));
    
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
    if (mCounter > 0)
    {
        std::string distance = StringUtils::format("Distance from center: %dm",
                                                   MapLayer::Instance()->getDistanceFromCenter());
        mDistance->setString(distance.c_str());
        
        mCounter -= dt;
        std::string countdown = StringUtils::format("Time left: %ds", static_cast<int>(mCounter));
        mCountDown->setString(countdown.c_str());
        
        std::string score = StringUtils::format("Score: %d", static_cast<int>(mScoreValue));
        mScore->setString(score.c_str());
    }
    else
    {
        gameOver();
    }
}

void HUDLayer::addScore()
{
    mScoreValue += (SCORE + ShipLayer::Instance()->getBonusUpgrade());
}

void HUDLayer::gameOver()
{
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    auto gameover = createLabel(42, Color4B::BLACK);
    std::string countdown = StringUtils::format("Game Over. Your score: %d", static_cast<int>(mScoreValue));
    gameover->setString(countdown.c_str());
    gameover->setPosition(Vec2(origin.x + visibleSize.width*0.5f, origin.y + visibleSize.height*0.5f));
    
    this->unscheduleUpdate();
    
    mDistance->setVisible(false);
    mDirection->setVisible(false);
    mTime->setVisible(false);
    mCountDown->setVisible(false);
    mScore->setVisible(false);
    mReloadButton->setVisible(false);
    mSunstoneButton->setVisible(false);
}