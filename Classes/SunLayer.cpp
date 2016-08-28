#include "SunLayer.h"

SunLayer* SunLayer::mInstance = 0;

bool SunLayer::init()
{
    if (!Layer::init())
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
    
    std::vector<std::string> possibleTime(2);
    possibleTime[0] = "Sunrise";
    possibleTime[1] = "Sunset";
    mPossibleTime = possibleTime;
    
    generate();
    initClouds();

    return true;
}

void SunLayer::generate()
{
    mTimeIndex = random(0, 1);
    mSunIndex = random(0, 7);
    mEast = (mTimeIndex == 0) ? mSunIndex : (mSunIndex + 4) % 8;
    mWest = (mTimeIndex == 0) ? (mSunIndex + 4) % 8 : mSunIndex;
    mNorth = (mTimeIndex == 0) ? (mSunIndex + 6) % 8 : (mSunIndex + 2) % 8;
    mSouth = (mTimeIndex == 0) ? (mSunIndex + 2) % 8 : (mSunIndex + 6) % 8;
    
    log("%s at (%f, %f)", mPossibleTime[mTimeIndex].c_str(),
        mPossiblePositions[mSunIndex].x, mPossiblePositions[mSunIndex].y);
    log("Sun points to EAST at (%f, %f)", mPossiblePositions[mEast].x, mPossiblePositions[mEast].y);
    log("Sun points to WEST at (%f, %f)", mPossiblePositions[mWest].x, mPossiblePositions[mWest].y);
    log("Sun points to NORTH at (%f, %f)", mPossiblePositions[mNorth].x, mPossiblePositions[mNorth].y);
    log("Sun points to SOUTH at (%f, %f)", mPossiblePositions[mSouth].x, mPossiblePositions[mSouth].y);
}

void SunLayer::initClouds()
{
    for (int i = 0; i < mPossiblePositions.size(); i++)
    {
        auto cloud1 = createCloud();
        cloud1->setPosition(mPossiblePositions[i]);
        this->addChild(cloud1);
        
        auto cloud2 = createCloud();
        cloud2->setPosition(Vec2(mPossiblePositions[i].x + 30, mPossiblePositions[i].y + 30));
        this->addChild(cloud2);
    }
}

Sprite* SunLayer::createCloud()
{
    auto cloud = Sprite::create("cloud.png");
    
    auto move = MoveBy::create(random(20, 40), Vec2(cloud->getPosition().x + 10, cloud->getPosition().y + 10));
    auto move_back = move->reverse();
    
    // create a BounceIn Ease Action
    auto move_ease_in = EaseBounceIn::create(move->clone());
    auto move_ease_in_back = EaseBounceIn::create(move_back->clone());
    
    // create a delay that is run in between sequence events
    auto delay = DelayTime::create(1);
    
    // create the sequence of actions, in the order we want to run them
    auto seq1 = Sequence::create(move_ease_in, delay, move_ease_in_back, delay->clone(), nullptr);
    
    // run the sequence and repeat forever.
    cloud->runAction(RepeatForever::create(seq1));
    
    return cloud;
}
