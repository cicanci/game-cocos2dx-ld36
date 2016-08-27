#ifndef __SUNSTONE_LAYER_H__
#define __SUNSTONE_LAYER_H__

#include "cocos2d.h"

USING_NS_CC;

class SunstoneLayer : public Layer
{
public:
    SunstoneLayer() { mInstance = this; }
    ~SunstoneLayer() { mInstance = NULL; }
    static SunstoneLayer* Instance() { return mInstance; }
    
    void show(Vec2 sun);
    
    bool onTouchBegan(Touch* touch, Event* event);
    void onTouchMoved(Touch *touch, Event *event);
    void onTouchEnded(Touch *touch, Event *event);
    void onTouchCancelled(Touch *touch, Event *event);
    
    virtual bool init();
    CREATE_FUNC(SunstoneLayer);
    
private:
    void initTouchEvent();
    void initSprites();
    void setInitialPosition();
    void updateOpacity(Vec2 touch, Vec2 sun);
    
    static SunstoneLayer* mInstance;
    EventListenerTouchOneByOne* mTouchListener;
    Sprite* mSunstone;
    Sprite* mDotUp;
    Sprite* mDotDown;
    Vec2 mSunPosition;
};

#endif // __SUNSTONE_LAYER_H__
