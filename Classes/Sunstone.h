#ifndef __SUNSTONE_SCENE_H__
#define __SUNSTONE_SCENE_H__

#include "cocos2d.h"

USING_NS_CC;

class Sunstone : public cocos2d::Layer
{
public:
    Sunstone() { mInstance = this; }
    ~Sunstone() { mInstance = NULL; }
    static Sunstone* Instance() { return mInstance; }
    
    void touchEvent(Touch* touch);
    void show(Vec2 sun);
    
    virtual bool init();
    CREATE_FUNC(Sunstone);
    
private:
    void initTouchEvent();
    void initSprites();
    void setInitialPosition();
    void updateOpacity(Vec2 touch, Vec2 sun);
    
    static Sunstone* mInstance;
    EventListenerTouchOneByOne* mTouchListener;
    Sprite* mSunstone;
    Sprite* mDotUp;
    Sprite* mDotDown;
    Vec2 mSunPosition;
};

#endif // __SUNSTONE_SCENE_H__
