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
    
    virtual bool init();
    CREATE_FUNC(ShipLayer);
    
private:
    static ShipLayer* mInstance;
    Sprite* mShip;
};

#endif // __SHIP_LAYER_H__
