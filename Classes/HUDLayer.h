#ifndef __HUD_LAYER_H__
#define __HUD_LAYER_H__

#include "cocos2d.h"

USING_NS_CC;

class HUDLayer : public Layer
{
public:
    void sunstoneCallback(Ref* pSender);

    virtual bool init();
    CREATE_FUNC(HUDLayer);
    
private:
    void initMenu();
};

#endif // __HUD_LAYER_H__
