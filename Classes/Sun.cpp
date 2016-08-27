#include "Sun.h"

bool Sun::init()
{
    if (!Node::init())
    {
        return false;
    }
    
    auto visibleSize = Director::getInstance()->getVisibleSize();
    
    std::vector<Vec2> possiblePositions(8);
    possiblePositions[0] = Vec2(0, 0);
    possiblePositions[1] = Vec2(0, visibleSize.height*0.5f);
    possiblePositions[2] = Vec2(0, visibleSize.height);
    possiblePositions[3] = Vec2(visibleSize.width*0.5f, visibleSize.height);
    possiblePositions[4] = Vec2(visibleSize.width, visibleSize.height);
    possiblePositions[5] = Vec2(visibleSize.width, visibleSize.height*0.5f);
    possiblePositions[6] = Vec2(visibleSize.width, 0);
    possiblePositions[7] = Vec2(visibleSize.width*0.5f, 0);
    mPossiblePositions = possiblePositions;
    
    generate();

    return true;
}

void Sun::generate()
{
    int dice_roll = random(0, 8);
    mSunPosition = mPossiblePositions[dice_roll];
    log("Sun is at [%d] %f, %f", dice_roll, mSunPosition.x, mSunPosition.y);
}