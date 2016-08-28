#ifndef __HUD_LAYER_H__
#define __HUD_LAYER_H__

#include "cocos2d.h"

USING_NS_CC;

class HUDLayer : public Layer
{
public:
    void sunstoneCallback(Ref* pSender);
    void reloadCallback(Ref* pSender);
    void update(float dt);

    virtual bool init();
    CREATE_FUNC(HUDLayer);
    
private:
    void initMenu();
    void initText();
    void updateText();
    Label* createLabel(int size, Color4B border);
    
    Label* mDistance;
    Label* mDirection;
    Label* mTime;
};

#endif // __HUD_LAYER_H__
