#include "LevelOneScene.h"

USING_NS_CC;

Scene* LevelOne::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::createWithPhysics();
    //scene->getPhysicsWorld()->setGravity(Vec2(0, 98));
    scene->getPhysicsWorld()->setGravity(Vec2(0, 0));
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
    origin = Director::getInstance()->getVisibleOrigin();
    coso = origin.y;
    CCLOG("%s %f", "coso", coso);
    
    //************ LABEL ************
    auto label = Label::createWithTTF("Level 1", "fonts/Marker Felt.ttf", 24);
    
    // position the label on the center of the screen
    label->setPosition(Vec2(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - label->getContentSize().height));
    
    // add the label as a child to this layer
    this->addChild(label, 1);
    
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
            auto pbSprite = PhysicsBody::createBox(sprite->getContentSize(), PhysicsMaterial(0, 1.0, 0.0));
            
            pbSprite->setCollisionBitmask(5);
            pbSprite->setContactTestBitmask(true);
            
            pbSprite->setDynamic(false);
            sprite->addComponent(pbSprite);
            this->addChild(sprite);
        }
    }
    
    //************ BOLA ************
    spriteBall = Sprite::create("ball2.png");
    
    // position the sprite on the center of the screen
    spriteBall->setPosition(Vec2(0, 0));
    spriteBall->setPosition(Vec2(visibleSize.width/2 + 10, origin.y));
    spriteBall->setAnchorPoint(Vec2(0.5,0.5));
    
    // Creamos el body
    //auto pbBall = PhysicsBody::createCircle(spriteBall->getContentSize().width/2, PhysicsMaterial(0.1f, 0.0f, 0.0f));
    pbBall = PhysicsBody::createCircle(spriteBall->getContentSize().width / 2, PhysicsMaterial(1, 1, 0));
    //pbBall = PhysicsBody::createBox(spriteBall->getContentSize(), PhysicsMaterial(1, 1, 0));
    // Colisión
    pbBall->setCollisionBitmask(1);
    pbBall->setContactTestBitmask(true);
    //pbBall->setDynamic(true);

    pbBall->setLinearDamping(0);
    pbBall->setAngularDamping(0);
    
    pbBall->setGravityEnable(false);
    pbBall->setVelocity(Vec2(0, 200));
    //pbBall->setAngularVelocity(5.0f);
    //pbBall->setVelocityLimit(500);
    
    // Asociamos la física al sprite
    spriteBall->addComponent(pbBall);
    // add the sprite as a child to this layer
    this->addChild(spriteBall, 0);
    
    //************ BARRA ************
    spriteBar = Sprite::create("bar.png");
    spriteBar->setScale(0.5, 1);
    spriteBar->setPosition(Vec2(visibleSize.width/2, origin.y));
    
    // Creamos el body
    pbBar = PhysicsBody::createBox(spriteBar->getContentSize(), PhysicsMaterial(0.0f, 1.0f, 0.0f));
    
    pbBar->setCollisionBitmask(2);
    pbBar->setContactTestBitmask(true);
    
    pbBar->setDynamic(false);
    pbBar->setGravityEnable(false);
    //pbBar->applyForce(Vec2(100, 100));
    spriteBar->addComponent(pbBar);
    this->addChild(spriteBar, 0);
    
    //************ MURO ************
    auto muro = Node::create();
    muro->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
    
    
    // Edge para que solo sea los bordes
    auto pbMuro = PhysicsBody::createEdgeBox(visibleSize, PhysicsMaterial(0, 1, 0), 3);
    
    pbMuro->setCollisionBitmask(10);
    pbMuro->setContactTestBitmask(true);
    
    pbMuro->setDynamic(false);
    pbMuro->setGravityEnable(false);
    muro->addComponent(pbMuro);
    this->addChild(muro, 0);
    
    //************ FECHAS ************
    // Arrow right sprite
    auto node_right = Sprite::create("images/arrow-right.png");
    node_right->setAnchorPoint(Vec2(1,0));
    node_right->setPosition(Vec2(visibleSize.width, 30));
    node_right->setTag(10);
    this->addChild(node_right, 1);
    
    // Arrow left sprite
    auto node_left = Sprite::create("images/arrow-left.png");
    node_left->setAnchorPoint(Vec2(0,0));
    node_left->setPosition(Vec2(origin.x, 30));
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
    listenerLeftRight->onTouchMoved = [](Touch* touch, Event* event){ };
    
    // trigger when you let up
    listenerLeftRight->onTouchEnded = [=](Touch* touch, Event* event){
        // Move sprite to position 50,10 in 2 seconds.
        pressed = false;
    };
    /************/
    
    // Add listener
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listenerLeftRight, node_left);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listenerLeftRight->clone(), node_right);
    
    auto contactListener = EventListenerPhysicsContact::create();
    contactListener->onContactBegin = CC_CALLBACK_1(LevelOne::onContactBegin, this);
    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(contactListener, this);
    
    
    // Llamada para que empiece el bucle del juego
    this->scheduleUpdate();
    
    return true;
}

bool LevelOne::onContactBegin(cocos2d::PhysicsContact &contact) {
    PhysicsBody *a = contact.getShapeA()->getBody();
    PhysicsBody *b = contact.getShapeB()->getBody();
    
    if ( (1 == a->getCollisionBitmask() && 2 == b->getCollisionBitmask() ) || (2 == a->getCollisionBitmask() && 1 == b->getCollisionBitmask()) ) {
        //CCLOG("Chocaron!!! PUM!");
        //pbBar->applyForce(Vec2(100, 100));
        //pbBall->setVelocity(Vec2(pbBall->getVelocity().x, 200));
        pbBall->applyImpulse(Vec2(200,0));
        
    }
    if (1 == a->getCollisionBitmask() && 5 == b->getCollisionBitmask() ) {
        b->getNode()->removeFromParentAndCleanup(true);
    }
    else if (5 == a->getCollisionBitmask() && 1 == b->getCollisionBitmask()) {
        a->getNode()->removeFromParentAndCleanup(true);
    }
    if ( (1 == a->getCollisionBitmask() && 10 == b->getCollisionBitmask() ) || (10 == a->getCollisionBitmask() && 1 == b->getCollisionBitmask()) ) {
        
        if (spriteBall->getPosition().y < 50) {
            CCLOG("Perdiste, panoli");
            
            auto emitter = ParticleExplosion::create();
            emitter->setPosition(Vec2(pbBall->getNode()->getPosition().x, pbBall->getNode()->getPosition().y));
            emitter->setDuration(0.2f);
            addChild(emitter, 10);
            
            pbBall->getNode()->removeFromParentAndCleanup(true);
        }
    }
    
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