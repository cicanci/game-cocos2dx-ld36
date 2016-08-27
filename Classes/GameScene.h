#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include "cocos2d.h"

#include "Sun.h"

USING_NS_CC;

class GameScene : public Layer
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    CREATE_FUNC(GameScene);
    
private:

};

#endif // __GAME_SCENE_H__
