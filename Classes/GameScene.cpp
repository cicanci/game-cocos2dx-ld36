#include "GameScene.h"

#include "HUDLayer.h"
#include "MapLayer.h"
#include "MessageLayer.h"
#include "ShipLayer.h"
#include "SunLayer.h"
#include "SunstoneLayer.h"

Scene* GameScene::createScene()
{
    auto scene = Scene::create();
    
    auto game = GameScene::create();
    scene->addChild(game);
    
    auto map = MapLayer::create();
    scene->addChild(map);
    
    auto ship = ShipLayer::create();
    scene->addChild(ship);
    
    auto sun = SunLayer::create();
    scene->addChild(sun);
    
    auto hud = HUDLayer::create();
    scene->addChild(hud);
    
    auto message = MessageLayer::create();
    message->setVisible(false);
    scene->addChild(message);
    
    auto sunstone = SunstoneLayer::create();
    sunstone->setVisible(false);
    scene->addChild(sunstone);

    return scene;
}

bool GameScene::init()
{
    if (!LayerColor::initWithColor(Color4B(0, 102, 255, 255)))
    {
        return false;
    }
    
    return true;
}
