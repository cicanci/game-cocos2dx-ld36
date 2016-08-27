#ifndef __MAP_LAYER_H__
#define __MAP_LAYER_H__

#include "cocos2d.h"

#include "Sun.h"

USING_NS_CC;

class MapLayer : public Layer
{
public:
    void sunstoneCallback(Ref* pSender);
    
    virtual bool init();
    CREATE_FUNC(MapLayer);
    
private:
    void initMenu();
    
    Sun* mSun;
};

#endif // __MAP_LAYER_H__
