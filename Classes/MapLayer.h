#ifndef __MAP_LAYER_H__
#define __MAP_LAYER_H__

#include "cocos2d.h"

#include "SunLayer.h"

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
    std::string getDirection() { return mDirectionName; }
    int getDistanceFromCenter();
    int getDistanceFromObjective();
    
    virtual bool init();
    CREATE_FUNC(MapLayer);
    
private:
    void initTouchEvent();
    void initBackground();
    void initDirection();
    
    static MapLayer* mInstance;
    EventListenerTouchOneByOne* mTouchListener;
    Vec2 mStartPosition;
    bool mIsMoving;
    bool mMoveRight;
    bool mMoveUp;
    CardinalDirection mCardinalDirection;
    std::string mDirectionName;
    
    const int SPEED = 60;
};

#endif // __MAP_LAYER_H__
