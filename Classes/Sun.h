#ifndef __SUN_H__
#define __SUN_H__

#include "cocos2d.h"

USING_NS_CC;

class Sun : public Node
{
public:    
    void generate();
    Vec2 getSunPosition() { return mSunPosition; }
    
    virtual bool init();
    CREATE_FUNC(Sun);
    
private:
    Vec2 mSunPosition;
    std::vector<Vec2> mPossiblePositions;
};

#endif // __SUN_H__
