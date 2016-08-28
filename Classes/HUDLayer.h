#ifndef __HUD_LAYER_H__
#define __HUD_LAYER_H__

#include "cocos2d.h"

USING_NS_CC;

class HUDLayer : public Layer
{
public:
    void sunstoneCallback(Ref* pSender);
    void update(float dt);

    virtual bool init();
    CREATE_FUNC(HUDLayer);
    
private:
    void initMenu();
    
    Label* mDistance;
};

#endif // __HUD_LAYER_H__
