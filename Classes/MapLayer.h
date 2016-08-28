#ifndef __MAP_LAYER_H__
#define __MAP_LAYER_H__

#include "cocos2d.h"

#include "Sun.h"

USING_NS_CC;

class MapLayer : public Layer
{
public:
    MapLayer() { mInstance = this; }
    ~MapLayer() { mInstance = NULL; }
    static MapLayer* Instance() { return mInstance; }

    void sunstoneCallback(Ref* pSender);
    void update(float dt);
    bool onTouchBegan(Touch* touch, Event* event);
    void onTouchMoved(Touch *touch, Event *event);
    void onTouchEnded(Touch *touch, Event *event);
    void onTouchCancelled(Touch *touch, Event *event);
    float getDistance();
    
    virtual bool init();
    CREATE_FUNC(MapLayer);
    
private:
    void initTouchEvent();
    void initBackground();
    
    static MapLayer* mInstance;
    EventListenerTouchOneByOne* mTouchListener;
    Sun* mSun;
    Vec2 mStartPosition;
    bool mIsMoving;
    bool mMoveRight;
    bool mMoveUp;
    
    const int SPEED = 100;
};

#endif // __MAP_LAYER_H__
