#ifndef __SUN_H__
#define __SUN_H__

#include "cocos2d.h"

USING_NS_CC;

typedef enum eCardinalDirection
{
    EAST,
    WEST,
    NORTH,
    SOUTH
} CardinalDirection;

class SunLayer : public Layer
{
public:
    SunLayer() { mInstance = this; }
    ~SunLayer() { mInstance = NULL; }
    static SunLayer* Instance() { return mInstance; }
    
    void generate();
    Vec2 getSunPosition() { return mPossiblePositions[mSunIndex]; }
    std::string getSunTime() { return mPossibleTime[mTimeIndex]; }
    std::string getDirection() { return mDirectionName; }
    
    virtual bool init();
    CREATE_FUNC(SunLayer);
    
private:
    void initClouds();
    Sprite* createCloud();

    static SunLayer* mInstance;
    std::vector<Vec2> mPossiblePositions;
    std::vector<std::string> mPossibleTime;
    std::string mDirectionName;
    CardinalDirection mCardinalDirection;
    Vec2 mObjectivePosition;
    int mSunIndex;
    int mTimeIndex;
    int mEast;
    int mWest;
    int mNorth;
    int mSouth;

};

#endif // __SUN_H__
