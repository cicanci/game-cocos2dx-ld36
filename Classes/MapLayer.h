#ifndef __MAP_LAYER_H__
#define __MAP_LAYER_H__

#include "cocos2d.h"

#include "Ship.h"
#include "Sun.h"

USING_NS_CC;

class MapLayer : public Layer
{
public:
    void sunstoneCallback(Ref* pSender);
    
    void update(float dt);
    bool onTouchBegan(Touch* touch, Event* event);
    void onTouchMoved(Touch *touch, Event *event);
    void onTouchEnded(Touch *touch, Event *event);
    void onTouchCancelled(Touch *touch, Event *event);
    
    virtual bool init();
    CREATE_FUNC(MapLayer);
    
private:
    void initMenu();
    void initTouchEvent();
    
    EventListenerTouchOneByOne* mTouchListener;
    Sprite* mShip;
    Sun* mSun;
};

#endif // __MAP_LAYER_H__
