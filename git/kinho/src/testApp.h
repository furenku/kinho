

#include "ofMain.h"
#include "ofxXmlSettings.h"
#include "ofxDirList.h"
#include "video.h"
#include "storage.h"
#include "videoStorage.h"



#include "mainClasses.h"
#include "baseGUIObjects.h"
#include "guiObjects.h"
#include "geometryWidgets.h"
//#include "guiVideoObjects.h"
//#include "views.h"
//#include "guiCtl.h"
//#include "guiFuncs.h"
//#include "model.h"





#include "kVideoPlayer.h"
#include "session.h"
#include "general.h"
#include "ontologies.h"
#include "library.h"
#include "archive.h"
#include "control.h"

#include "scenes.h"



#include "editor.h"
#include "outputs.h"
#include "controllers.h"
//#include "scene.h"
//#include "kinho.h"

//#include "ontologies.h"


#pragma once

#ifndef testapp_h
#define testapp_h




#include <map>
#include <tr1/memory>
#include <boost/pointer_cast.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/make_shared.hpp>
#include <boost/foreach.hpp>


using boost::shared_ptr;
using boost::enable_shared_from_this;
using boost::dynamic_pointer_cast;
using boost::make_shared;




class TSTVW: public kRectView{
    public:
        TSTVW(){

            autoArrange = false;

        }

        void init(){

            shared_ptr<kRectButtonView> bv = make_shared<kRectButtonView>( );
            bv->set(0,0,1.0f,0.1f);
            addWidget(bv);

            arrangeWidgets();

            vector<string> labels;
            for (int i=0; i<10; i++)
            {
            	labels.push_back("btn"+ofToString(i));
            }
            bv->addDragButtons(labels);

            ofAddListener(*bv->events.lookup("btnDragged"),this,&TSTVW::btnDragged);
            arrangeWidgets();

        }

        void btnDragged(widgetEvent & _event){
            dragBtn = dynamic_pointer_cast<kButtonView>(_event.sender)->getCommand();
        }

        int dragX, dragY;

        bool drawDrag;


        void mouseDragged(ofMouseEventArgs & mouse){
            if(isMouseOn) {
                if(dragBtn!="") {
                    drawDrag = true;
                    dragX = mouse.x;
                    dragY = mouse.y;
                }
                else{
                    drawDrag = false;
                }
            }
            else {
                drawDrag = false;
            }
        }

        void draw(ofEventArgs & args){
            kRectView::draw(args);

            if(drawDrag)
                ofCircle(dragX,dragY,10);

        }

        void mouseReleased(ofMouseEventArgs & mouse){
            if(dragBtn!=""){
                if( inside(mouse.x,mouse.y)){
                    shared_ptr<kRectButton> btn = make_shared<kRectButton>( );
                    btn->set( (mouse.x-x)/width,(mouse.y-y)/height,0.05f,0.05f);
                    btn->setLabel(dragBtn);
                    addWidget(btn);
                    arrangeWidgets();
                }
            }
            dragBtn = "";
            drawDrag = false;
        }

        string dragBtn;
};
class testApp : public ofBaseApp
{

public:

    void setup();
    void update();
    void draw();

    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);


    void tst(widgetEvent & event);


//		void queueDelete(shared_ptr<kWidget> _widget) {
//            deleteWidgets.push_back(_widget);
//		}

//		vector <shared_ptr<kWidget> > deleteWidgets;



    ofxXmlSettings XML;
    ofTrueTypeFont TTF;

    string xmlStructure;
    string message;

    shared_ptr<MainController> ctl;

//		ofPoint dragPts[NUM_PTS];

    int pointCount;
    int lineCount;
    int lastTagNumber;

    float red;
    float green;
    float blue;
};



#endif



















/*
class a{
    public:
        a(){ val = 0; }
        ~a(){}

        void setVal( shared_ptr<a> _a, int _i ) _a->val = _i;

        void coutVal() { cout << val << endl; }

        int val;

        shared_ptr<a> l;
};

class b: public a {
    public:
        b(){  }
        ~b(){}

};
*/
