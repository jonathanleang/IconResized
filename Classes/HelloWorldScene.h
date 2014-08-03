#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include <Magick++.h>
#include <string>

USING_NS_CC;
using namespace std;


class HelloWorld : public cocos2d::LayerColor
{
    Point _curentImagePos;
    map<string, string> sizes;
    static HelloWorld* _instance;
public:
    static HelloWorld* getInstance(){
        return HelloWorld::_instance;
    }
    
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  
    
    void resizeAndWriteImage(Magick::Image image, string fileName, string size);
    void showPreview(Magick::Image image);
    void addImage(string file);
    
    bool onTouchBegan(Touch *touch, Event *unused_event);
    
    bool convert(string filePath);
    
    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);
};

#endif // __HELLOWORLD_SCENE_H__
