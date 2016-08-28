#ifndef __SUN_H__
#define __SUN_H__

#include "cocos2d.h"

USING_NS_CC;

class SunLayer : public Layer
{
public:
    SunLayer() { mInstance = this; }
    ~SunLayer() { mInstance = NULL; }
    static SunLayer* Instance() { return mInstance; }
    
    void generate();
    Vec2 getSunPosition() { return mSunPosition; }
    
    virtual bool init();
    CREATE_FUNC(SunLayer);
    
private:
    void initClouds();
    Sprite* createCloud();

    static SunLayer* mInstance;
    Vec2 mSunPosition;
    std::vector<Vec2> mPossiblePositions;
};

#endif // __SUN_H__
