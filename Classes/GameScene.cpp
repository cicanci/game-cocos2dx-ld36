#include "GameScene.h"

#include "HUDLayer.h"
#include "MapLayer.h"
#include "ShipLayer.h"
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
    
    auto hud = HUDLayer::create();
    scene->addChild(hud);
    
    auto sunstone = SunstoneLayer::create();
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
    
    return true;
}
