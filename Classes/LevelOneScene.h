#ifndef __LEVELONE_SCENE_H__
#define __LEVELONE_SCENE_H__

#include "cocos2d.h"

class LevelOne : public cocos2d::Layer
{
private:
    bool pressed = false;
    cocos2d::Sprite* spriteBar;
    cocos2d::Sprite* spriteBall;
    // Dirección derecha o izquierda (1,0 ó -1,0)
    cocos2d::Vec2 delta = cocos2d::Vec2(0,0);
    cocos2d::PhysicsBody* pbBar;
    cocos2d::PhysicsBody* pbBall;
public:
    static cocos2d::Scene* createScene();
    
    cocos2d::Sprite* matrixSprites[6][4];

    virtual bool init();
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    void update(float);
    
    bool onContactBegin(cocos2d::PhysicsContact &contact);
    
    // implement the "static create()" method manually
    CREATE_FUNC(LevelOne);
};

#endif // __LEVELONE_SCENE_H__
