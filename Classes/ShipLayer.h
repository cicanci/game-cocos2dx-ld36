#ifndef __SHIP_LAYER_H__
#define __SHIP_LAYER_H__

#include "cocos2d.h"

USING_NS_CC;

class ShipLayer : public Layer
{
public:
    ShipLayer() { mInstance = this; }
    ~ShipLayer() { mInstance = NULL; }
    static ShipLayer* Instance() { return mInstance; }

    void updateShip(Vec2 touch);
    Sprite* getShip() { return mShip; }
    void addSpeedUpgrade() { mSpeedUpgrade += 10; }
    int getSpeedUpgrade() { return mSpeedUpgrade; }
    void addBonusUpgrade() { mBonusUpgrade += 1; }
    int getBonusUpgrade() { return mBonusUpgrade; }
    
    virtual bool init();
    CREATE_FUNC(ShipLayer);
    
private:
    static ShipLayer* mInstance;
    Sprite* mShip;

    int mSpeedUpgrade;
    int mBonusUpgrade;
};

#endif // __SHIP_LAYER_H__
