#include "MenuScene.h"
#include "LevelOneScene.h"

USING_NS_CC;

Scene* MenuScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = MenuScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool MenuScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    // Creo el menu
    auto menu = Menu::create();
    
    // Menu Item Font
    
    auto item = MenuItemFont::create(">> BlockSmasher <<");
    item->setPositionY(visibleSize.height/3);
    item->retain();
    auto play = MenuItemFont::create("Play", CC_CALLBACK_1(MenuScene::playGame, this));
    play->setPosition(Vec2(0,50));
    auto quit = MenuItemFont::create("Quit", CC_CALLBACK_1(MenuScene::quitGame, this));
    
    
    
    
    
    /*// Creo menu items para añadirlos a ese menu
    auto playItem = MenuItemImage::create("CloseNormal.png",
                                          "CloseSelected.png",
                                          CC_CALLBACK_1(MenuScene::playGame, this));*/
    // Añado el item al menu
    menu->addChild(item);
    menu->addChild(play);
    menu->addChild(quit);
    // Añado el menu a la escena
    menu->setPosition(visibleSize.width/2, visibleSize.height/2);
    this->addChild(menu);
    
    return true;
}

// Evento cuando pincha en play
void MenuScene::playGame(Ref* pSender)
{
    log("En el play game");
    // Transicion de escena
    auto hws = LevelOne::createScene();
    Director::getInstance()->replaceScene(hws);
    
}

void MenuScene::quitGame(Ref* pSender)
{
    Director::getInstance()->end();
    
    #if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
        exit(0);
    #endif
}
