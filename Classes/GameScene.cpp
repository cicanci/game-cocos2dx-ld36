#include "SimpleAudioEngine.h"

#include "GameScene.h"
#include "MapLayer.h"
#include "SunstoneLayer.h"

Scene* GameScene::createScene()
{
    auto scene = Scene::create();
    
    auto game = GameScene::create();
    scene->addChild(game);
    
    auto map = MapLayer::create();
    scene->addChild(map);
    
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
