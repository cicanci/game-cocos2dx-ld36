#ifndef __SUNSTONE_SCENE_H__
#define __SUNSTONE_SCENE_H__

#include "cocos2d.h"

USING_NS_CC;

class Sunstone : public cocos2d::Node
{
public:
    Sunstone();
    ~Sunstone();
    
    void touchEvent(Touch* touch);
    
private:
    void initTouchEvent();
    void initSprites();
    
    Sprite* mSunstone;
    Sprite* mDotUp;
    Sprite* mDotDown;
    Vec2 mSunPosition;
};

#endif // __SUNSTONE_SCENE_H__
