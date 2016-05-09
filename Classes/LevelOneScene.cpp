#include "LevelOneScene.h"

USING_NS_CC;

Scene* LevelOne::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::createWithPhysics();
    scene->getPhysicsWorld()->setGravity(Vec2(0, 98));
    // Info
    scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
    
    // 'layer' is an autorelease object
    auto layer = LevelOne::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;

}

// on "init" you need to initialize your instance
bool LevelOne::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label
    
    auto label = Label::createWithTTF("Level 1", "fonts/Marker Felt.ttf", 24);
    
    // position the label on the center of the screen
    label->setPosition(Vec2(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - label->getContentSize().height));

    // add the label as a child to this layer
    this->addChild(label, 1);

    auto ball = Sprite::create("ball.jpg");
//ball->setScale(0.20);
    
    // position the sprite on the center of the screen
    ball->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
    
    // add the sprite as a child to this layer
    this->addChild(ball, 0);
    
    // Creamos el body
    auto pbSprite = PhysicsBody::createCircle(ball->getContentSize().width/2, PhysicsMaterial(0.0,1.0,0.0));
    
    // Asociamos la física al sprite
    ball->addComponent(pbSprite);
    
    // Creamos el muro
    auto muro = Node::create();
    muro->setPosition(Vec2(0,0));
    this->addChild(muro, 0);
    
    // Edge para que solo sea los bordes
    Vec2 puntos[4] = { Vec2(0,0), Vec2(0, visibleSize.height), Vec2(visibleSize.width, visibleSize.height), Vec2(visibleSize.width,0) };
    auto pbMuro = PhysicsBody::createEdgeChain(puntos, 4);
    muro->addComponent(pbMuro);
    
    
    
    return true;
}


void LevelOne::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
