#include "SimpleAudioEngine.h"

#include "GameScene.h"
#include "Sunstone.h"

Scene* GameScene::createScene()
{
    auto scene = Scene::create();
    
    auto game = GameScene::create();
    scene->addChild(game);
    
    auto sunstone = Sunstone::create();
    sunstone->setVisible(false);
    scene->addChild(sunstone);

    return scene;
}

bool GameScene::init()
{
    if (!Layer::init())
    {
        return false;
    }
    
    initMenu();
    
    mSun = Sun::create();
    mSun->retain();
    
    return true;
}

void GameScene::initMenu()
{
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    auto closeItem = MenuItemImage::create("buttonSunstone.png",
                                           "buttonSunstone.png",
                                           CC_CALLBACK_1(GameScene::menuCloseCallback, this));
    
    closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
                                origin.y + closeItem->getContentSize().height/2));
    
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);
    
    auto label = Label::createWithTTF("Sunstone - A Cloudy Day", "fonts/Marker Felt.ttf", 24);
    label->setPosition(Vec2(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - label->getContentSize().height));
    this->addChild(label, 1);
    
    auto sprite = Sprite::create("HelloWorld.png");
    sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
    this->addChild(sprite, 0);
}

void GameScene::menuCloseCallback(Ref* pSender)
{
    Sunstone::Instance()->show(mSun->getSunPosition());
}
