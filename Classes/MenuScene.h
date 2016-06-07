#ifndef __MENUSCENE_SCENE_H__
#define __MENUSCENE_SCENE_H__

#include "cocos2d.h"

class MenuScene : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    
    // a selector callback
    void playGame(cocos2d::Ref* pSender);
    void quitGame(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(MenuScene);
};

#endif // __MENUSCENE_SCENE_H__
