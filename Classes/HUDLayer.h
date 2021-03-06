#ifndef __HUD_LAYER_H__
#define __HUD_LAYER_H__

#include "cocos2d.h"

USING_NS_CC;

class HUDLayer : public Layer
{
public:
    HUDLayer() { mInstance = this; }
    ~HUDLayer() { mInstance = NULL; }
    static HUDLayer* Instance() { return mInstance; }
    
    void sunstoneCallback(Ref* pSender);
    void reloadCallback(Ref* pSender);
    void update(float dt);
    void updateText();
    void addScore();

    virtual bool init();
    CREATE_FUNC(HUDLayer);
    
private:
    void initMenu();
    void initText();
    void gameOver();
    Label* createLabel(int size, Color4B border);
    
    static HUDLayer* mInstance;
    float mCounter;
    int mScoreValue;
    Label* mDistance;
    Label* mDirection;
    Label* mTime;
    Label* mCountDown;
    Label* mScore;
    MenuItemImage* mSunstoneButton;
    MenuItemImage* mReloadButton;
    
    const int SCORE = 10;
    const int GAME_TIME = 300;
};

#endif // __HUD_LAYER_H__
