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

    void showSunstone();
    void reloadLevel();
    void update(float dt);
    bool onTouchBegan(Touch* touch, Event* event);
    void onTouchMoved(Touch *touch, Event *event);
    void onTouchEnded(Touch *touch, Event *event);
    void onTouchCancelled(Touch *touch, Event *event);
    void setObjectivePosition(Vec2 position);
    int getDistanceFromCenter();
    int getDistanceFromObjective();
    
    virtual bool init();
    CREATE_FUNC(MapLayer);
    
private:
    void initTouchEvent();
    void initBackground();
    
    static MapLayer* mInstance;
    EventListenerTouchOneByOne* mTouchListener;
    Sprite* mIsland;
    Vec2 mStartPosition;
    Vec2 mMapPosition;
    Vec2 mObjectivePosition;
    bool mIsMoving;
    bool mMoveRight;
    bool mMoveUp;
    
    const int SPEED = 60;
};

#endif // __MAP_LAYER_H__
