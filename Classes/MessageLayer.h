#ifndef __MESSAGE_LAYER_H__
#define __MESSAGE_LAYER_H__

#include "cocos2d.h"

USING_NS_CC;

class MessageLayer : public Layer
{
public:
    MessageLayer() { mInstance = this; }
    ~MessageLayer() { mInstance = NULL; }
    static MessageLayer* Instance() { return mInstance; }
    
    void addSpeedCallback(Ref* pSender);
    void addBonusCallback(Ref* pSender);
    void closeCallback(Ref* pSender);
    void closeMessage();
    void showMessage();
    
    virtual bool init();
    CREATE_FUNC(MessageLayer);
    
private:
    void initMessage();
    Label* createLabel(int size, Color4B border, std::string text, Vec2 position);
    
    static MessageLayer* mInstance;
    Sprite* mMessageBox;
    MenuItem* mAddSpeed;
    MenuItem* mAddBonus;
    MenuItem* mCloseMessage;
    Label* mCurrentSpeed;
    Label* mCurrentBonus;

};

#endif // __MESSAGE_LAYER_H__
