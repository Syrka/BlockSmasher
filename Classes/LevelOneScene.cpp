#include "LevelOneScene.h"

USING_NS_CC;

Scene* LevelOne::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::createWithPhysics();
    //scene->getPhysicsWorld()->setGravity(Vec2(0, 98));
    //scene->getPhysicsWorld()->setGravity(Vec2(0, 0));
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
    
    //************ BLOQUES ************
    int i;
    int j;
    
    for (i=0; i<6; i++) {
        for (j=0; j<4; j++) {
            //matrix[i][j] = 0;
            auto sprite = Sprite::create("block.png");
            
            sprite->setScale(visibleSize.width / sprite->getContentSize().width/6,
                             visibleSize.height / sprite->getContentSize().height/15);
            sprite->setAnchorPoint(Vec2(0,0));
            sprite->setPosition(Vec2(i*80 + origin.x, visibleSize.height - (j*20 +origin.y)));
            //sprite->setScale(visibleSize.width / sprite->getContentSize().width/4, visibleSize.width / sprite->getContentSize().width/6 );
            matrixSprites[i][j] = (cocos2d::Sprite*)sprite;
            this->addChild(sprite);
            auto pbSprite = PhysicsBody::createBox(sprite->getContentSize(), PhysicsMaterial(5.0, 0.0, 0.0));
            pbSprite->setDynamic(false);
            pbSprite->setGravityEnable(false);
            sprite->addComponent(pbSprite);
        }
    }
    
    //************ LABEL ************
    auto label = Label::createWithTTF("Level 1", "fonts/Marker Felt.ttf", 24);
    
    // position the label on the center of the screen
    label->setPosition(Vec2(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - label->getContentSize().height));

    // add the label as a child to this layer
    this->addChild(label, 1);
    
    //************ BOLA ************
    spriteBall = Sprite::create("ball.png");
    spriteBall->setScale(0.05);
    
    // position the sprite on the center of the screen
    spriteBall->setPosition(Vec2(visibleSize.width/8, origin.y));
    
    // add the sprite as a child to this layer
    this->addChild(spriteBall, 0);
    // Creamos el body
    auto pbBall = PhysicsBody::createCircle(spriteBall->getContentSize().width/2, PhysicsMaterial(0.1f, 1.0f, 0.0f));
    pbBall->setGravityEnable(false);
    pbBall->setVelocity(Vec2(200, 200));
    pbBall->setVelocityLimit(500);
    
    // Asociamos la física al sprite
    spriteBall->addComponent(pbBall);
    
    //************ BARRA ************
    spriteBar = Sprite::create("bar.png");
    spriteBar->setScale(0.5);
    spriteBar->setPosition(Vec2(visibleSize.width/2,
                                origin.y));
    this->addChild(spriteBar, 0);
    // Creamos el body
    auto pbBar = PhysicsBody::createBox(spriteBar->getContentSize(), PhysicsMaterial(0.1f, 1.0f, 0.0f));
    pbBar->setDynamic(false);
    pbBar->setGravityEnable(false);
    //pbBar->applyForce(Vec2(100, 100));
    spriteBar->addComponent(pbBar);
    
    //************ MURO ************
    auto muro = Node::create();
    muro->setPosition(Vec2(0,0));
    this->addChild(muro, 0);
    
    // Edge para que solo sea los bordes
    Vec2 puntos[4] = { Vec2(0,0), Vec2(0, visibleSize.height), Vec2(visibleSize.width, visibleSize.height), Vec2(visibleSize.width,0) };
    auto pbMuro = PhysicsBody::createEdgeChain(puntos, 4, PhysicsMaterial(0.1f, 1.0f, 0.0f));
    //pbMuro->applyForce(Vec2(1000,1000));
    muro->addComponent(pbMuro);
    
    //************ PRUEBASSSS ************
    /*
    auto spritePrueba = Sprite::create("ball.png");
    spritePrueba->setScale(0.05);
    auto physicsBodyPrueba = PhysicsBody::createCircle(spritePrueba->getContentSize().width/2, PhysicsMaterial(0.1f, 1.0f, 0.0f));
    physicsBodyPrueba->setDynamic(false);
    //create a sprite
    spritePrueba->setPosition(Vec2(visibleSize.width/2, visibleSize.height/2));
    addChild(spritePrueba);
    //apply physicsBody to the sprite
    spritePrueba->addComponent(physicsBodyPrueba);
    
    //add five dynamic bodies
    for (int i = 0; i < 5; ++i)
    {
        physicsBodyPrueba = PhysicsBody::createCircle(spritePrueba->getContentSize().width/2,
                                         PhysicsMaterial(0.1f, 0.0f, 0.0f));
        //set the body isn't affected by the physics world's gravitational force
        physicsBodyPrueba->setGravityEnable(false);
        //set initial velocity of physicsBody
        //physicsBodyPrueba->setVelocity(Vec2(cocos2d::random(-500,500),
        //                                    cocos2d::random(-500,500)));
        //physicsBodyPrueba->setAngularVelocity(50.0);
        physicsBodyPrueba->setVelocity(Vec2(400, 400));
        physicsBodyPrueba->setVelocityLimit(500);
        
        // TODO: Aplicar fuerza cuando choca contra la barra (paredes tambien?)
        //physicsBodyPrueba->applyForce(Vec2(100, 300));
        
        physicsBodyPrueba->setTag(1);
        spritePrueba = Sprite::create("ball.png");
        spritePrueba->setScale(0.05);
        //spritePrueba->setPosition(Vec2(visibleSize.width/2 + cocos2d::random(-300,300),
        //                     visibleSize.height/2 + cocos2d::random(-300,300)));
        spritePrueba->setPosition(origin.x+10,
                                  origin.y+10);
        spritePrueba->addComponent(physicsBodyPrueba);
        addChild(spritePrueba);
    }*/
    // ************
    
    //************ FECHAS ************
    // Arrow right sprite
    auto node_right = Sprite::create("images/arrow-right.png");
    node_right->setAnchorPoint(Vec2(1,0));
    node_right->setPosition(Vec2(visibleSize.width, 30));
    node_right->setTag(10);
    this->addChild(node_right, 1);
    
    // Arrow left sprite
    auto node_left = Sprite::create("images/arrow-left.png");
    node_left->setAnchorPoint(Vec2(1,0));
    node_left->setPosition(Vec2(node_right->getPositionX()-100, 30));
    node_left->setTag(-10);
    this->addChild(node_left, 1);
    
    //  Create a "one by one" touch event listener
    auto listenerLeftRight = EventListenerTouchOneByOne::create();
    listenerLeftRight->setSwallowTouches(true); // Para no pasar el evento cuando hay intersección con otro objeto debajo.
    
    /* MOVING LEFT OR RIGHT */
    // trigger when you push down
    listenerLeftRight->onTouchBegan = [=](Touch* touch, Event* event){
        
        Sprite* target = (Sprite*)event->getCurrentTarget();
        if (target->getBoundingBox().containsPoint(touch->getLocation()))
        {
            pressed = true;
            delta = Vec2(target->getTag(), 0);
            return true;
        }
        
        return false; // if you are consuming it
    };
    
    // trigger when moving touch
    listenerLeftRight->onTouchMoved = [](Touch* touch, Event* event){
        // your code
    };
    
    // trigger when you let up
    listenerLeftRight->onTouchEnded = [=](Touch* touch, Event* event){
        // Move sprite to position 50,10 in 2 seconds.
        pressed = false;
    };
    /************/
    
    // Add listener
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listenerLeftRight, node_left);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listenerLeftRight->clone(), node_right);
    
    // Llamada para que empiece el bucle del juego
    this->scheduleUpdate();
    
    return true;
}

void LevelOne::update(float dd)
{
    if (pressed)
        spriteBar->setPosition(spriteBar->getPosition() + delta);
}


void LevelOne::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}