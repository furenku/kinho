#pragma once



#ifndef gui_video_objects_h
#define gui_video_objects_h

#include "guiObjects.h"
#include "storage.h"
#include "mediaStorage.h"
//#pragma once

//#ifndef GUIVIDEOOBJECTS_H
//#define GUIVIDEOOBJECTS_H


//----- VIDEO OBJECTS:


class kVideoThumb: virtual public DrawObject, virtual public Observable {
    public:
        kVideoThumb(){}
};


class MediaWidget: virtual public kCircleButton, public StoreObject { //, virtual public kVideoThumb {
    public:
        MediaWidget();

        ~MediaWidget();

        void setMedia( shared_ptr<MediaHolder> _media);



//    protected:
        ofImage img;

        string description;
        string filename;

        shared_ptr<MediaHolder> media;
};

class kClip: virtual public MediaWidget { //, virtual public kVideoThumb {

    public:
        kClip();

        ~kClip();




//        void createEvents(){
//            kDragObject::createEvents();
//        }


        void setClip ( shared_ptr<Clip> _clip );

        shared_ptr<Clip> getClip();

        void draw(ofEventArgs & args);

        bool inside (float px, float py);

        void mouseMoved( ofMouseEventArgs & mouse);

//    protected:

        shared_ptr<Clip> clip;

        float aspectRatio;


};


class kClipShow: virtual public kClip, virtual public kDragObject {
    public:
        kClipShow(): kClip(){}

        void createEvents();

        void mouseReleased( ofMouseEventArgs & mouse);

        void mouseDragged( ofMouseEventArgs & mouse);

};


class kClipHolder: virtual public kClip, virtual public kCircleView, virtual public kDragObject {
    public:
int output;

        kClipHolder( shared_ptr<Settings> _settings );




        void createEvents();

        void addBtnView();

        virtual void pressed();

        virtual void pressedOut();



        void removeBtnView();

        void removeSubView();



        void btnClicked(widgetEvent & _event );




        void draw(ofEventArgs & args);

        void mouseDragged(ofMouseEventArgs & mouse);


        void mouseReleased(ofMouseEventArgs & mouse);


        void deleteView();

        void addView();


        void showView(float _x, float _y);

        shared_ptr<kClipHolder> shared_from_this();

//        vector<kView*> storeViews;
        shared_ptr<kCircleButtonView> btnView;
        shared_ptr<kRectButtonView> subView;




};



class kCategory: virtual public kCircleButtonView, virtual public kDragObject {
    public:
        kCategory() { }

        void mouseDragged(ofMouseEventArgs & mouse);

};




class kClipView: virtual public kRectView, virtual public kDragSink{

    public:
    kClipView() ;

    void createEvents();

    virtual void addClip(shared_ptr<Clip> _clip);

        void clipClicked(widgetEvent & _event);


        void clipDragged(widgetEvent & _event);

    void removeClip( shared_ptr<kClipShow> _clip );

    vector< shared_ptr < kClipShow > > & getClips();

    shared_ptr<Clip> currentClip;
    vector< shared_ptr < kClipShow > > clips;

    void clearClips();

    shared_ptr<Clip> getDraggingClip();

    shared_ptr<Clip> draggingClip,clickedClip;

};






class kClipScrollView: virtual public kScrollView, virtual public kClipView {
    public:

    kClipScrollView();

    void initialize();

    void addClips(vector< shared_ptr<Clip> > _clips);

    vector< shared_ptr < kClipShow > > & getClips();

    vector< shared_ptr < kClipShow > > clips;


};



class kMediaScrollView: virtual public kCircleScrollView {
    public:
        kMediaScrollView();




        void createEvents();






        void addMedia( vector<shared_ptr<MediaHolder> > _media );


        void btnClicked(widgetEvent & _event);



        void btnDragged(widgetEvent & _event);

};




class kSample: virtual public MediaWidget { //, virtual public kVideoThumb {
    public:
        kSample();

//        void createEvents(){
//            kDragObject::createEvents();
//        }

//        shared_ptr<Sample> sample;

        void setSample ( shared_ptr<Sample> _sample ) ;

        void draw(ofEventArgs & args);

    protected:
        shared_ptr<Sample> sample;
        float sampleRate;


};


class kSampleShow: virtual public kSample, virtual public kDragObject {
    public:
        kSampleShow(): kSample(){}

        void mouseReleased( ofMouseEventArgs & mouse);

};



class kSampleView: virtual public kRectView, virtual public kDragSink{

    public:
    kSampleView() {}

    virtual void addSample(shared_ptr<Sample> _sample);

    void removeSample(shared_ptr<kSampleShow> _sample);

    vector< shared_ptr < kSampleShow > > & getSamples();

    void clearSamples();


    shared_ptr<Sample> currentSample;
    vector< shared_ptr < kSampleShow > > samples;


};



class kSampleScrollView: virtual public kScrollView,virtual public kSampleView {
    public:

    kSampleScrollView();
    void clearSamples();


/*
    void addButtons(vector<string> _labels){


            clearWidgets();

            labels=_labels;
            for (int i=0; i<labels.size(); i++)
            {
                btn = make_shared<kCircleButton>();
                btn->setSize(widgetSize);
                btn->setLabel( labels[i] );
                btn->setMode(TOGGLE_ON);
                if(i==0)    btn->toggle=true;
                else        btn->toggle=false;
                btn->value = i ;

                ofAddListener( *btn->events.lookup("press"),this,&kScrollView::btnClicked);

                addWidget( btn );

                btn.reset();

            }

        }

*/


    void addSamples(vector< shared_ptr<Sample> > _samples);

};








//--------------------------------------------------------------

//class Node: virtual public kCircleButton  {
//    public:
//    Node()
//    {
//        isConnecting    =   false;
//        isActive        =   false;
//        createEvents();
//    }
//
//    void createEvents() {
//        saveEvent("attemptNodeConnection");
//    }
//
//    //--------------------------------------------------------------
//    void drawConnections(){
////        if(hasBeenCreated)  {
//        if(isConnecting)    {
//            ofSetColor(0x444444);
//            ofLine(x,y,mouseX,mouseY);
//        }
//        else
//            if(parent!=NULL){
//                ofSetColor(0xAAAAAA);
//                ofLine(x,y,parent->x,parent->y);
//            }
////        }
//    }
//
//    //--------------------------------------------------------------
//
//    //--------------------------------------------------------------
//    void mouseReleased(ofMouseEventArgs & mouse)   {
//
//        if(!isConnecting)  {
//            kCircleButton::mouseReleased(mouse);
//        }
//
//        if(isConnecting)    {
//            notify("attemptNodeConnection");
//
//            isConnecting=false;
//
//            updateConnectors();
//        }
//    }
//
//    //--------------------------------------------------------------
//    void mousePressed(ofMouseEventArgs & mouse) {
//        kCircleButton::mousePressed(mouse);
//
//        recordX=mouse.x;
//        recordY=mouse.y;
//
//        hasGotDescendants=false;
//
//    }
//
//    //--------------------------------------------------------------
//    void mouseDragged(ofMouseEventArgs & mouse) {
//
//        kCircleButton::mouseDragged(mouse);
//
//        if(isBeingDragged)  {
//
//            if(!hasGotDescendants)  {
//                getDescendants();
//                getDescendantsXY();
//            }
//
//            updateConnectors();
//
//            for(int i=0; i<children.size(); i++){
//                children[i]->updateConnectors();
//            }
//
//            for(int i=0; i<descendants.size(); i++){
//                descendants[i]->x = descendantsX[i]+(mouse.x-recordX);
//                descendants[i]->y = descendantsY[i]+(mouse.y-recordY);
//                descendants[i]->updateConnectors();
//            }
//
//        }
//
//    }
//
//    //--------------------------------------------------------------
//    void mouseMoved(ofMouseEventArgs & mouse) {
//
//        kCircleButton::mouseMoved(mouse);
//
//        if(isConnecting)
//            updateConnectors();
//    }
//
//
//    //--------------------------------------------------------------
//    void updateConnectors(){
//
//        float angle;
//
//        if(isConnecting)
//            angle = getAngle( mouseX, mouseY, x, y ) * ( TWO_PI / 360 );
//        else
//            if(parent!=NULL)
//                angle = getAngle( parent->x, parent->y, x, y ) * ( TWO_PI / 360 );
//            else
//                angle = getAngle( x, y - ( width * 0.6 ), x, y ) * ( TWO_PI / 360 );
//
//        for(int i =0; i<connectors.size(); i++)    {
//            connectors[i]->x=x + ( cos( angle ) * ( width * 0.6 ) );
//            connectors[i]->y=y + ( sin( angle ) * ( width * 0.6 ) );
//        }
//
//    }
//
//
//    //--------------------------------------------------------------
//    void btnPressed( widgetEvent & event ){
////        if(allowCalls)  {
////            Button::getCall( source, message,param);
//
//            if(event.command == "connector") isConnecting  =   true;
////        }
//    }
//
//
//    //--------------------------------------------------------------
//    void getDescendants()    {
//
//        descendants.clear();
//        getAllChildren(shared_from_this());
//        hasGotDescendants=true;
//
//    }
//
//
//    //--------------------------------------------------------------
//    void getDescendantsXY()  {
//        descendantsX.clear();
//        descendantsY.clear();
//
//        for (int i=0; i<descendants.size(); i++ )
//        {
//        	descendantsX.push_back(descendants[i]->x);
//            descendantsY.push_back(descendants[i]->y);
//        }
//
//    }
//
//
//    //--------------------------------------------------------------
//    void getAllChildren(shared_ptr<Node> parentNode)  {
//
//        // using recursion to find all nodes
//        // (based on http://stackoverflow.com/questions/177277/how-to-get-a-list-of-all-child-nodes-in-a-treeview-in-net)
//        for(int i = 0 ; i<parentNode->children.size(); i++)  {
//            descendants.push_back(parentNode->children[i]);
//            getAllChildren(parentNode->children[i]);
//        }
//    }
//
//
//    //--------------------------------------------------------------
//    int getBranch(shared_ptr<Node> descendantNode )    {
//
//        int currentBranch;
//
//            bool foundRoot = false;
//
//            for (int i=0; i<children.size(); i++ )
//            {
//                if( children[i] == descendantNode ) {
//                    currentBranch = i;
//                    foundRoot = true;
//                    break;
//                }
//            }
//
//            for (int i=0; i<children.size(); i++ )
//            {
//                children[i]->getDescendants();
//                for (int j = 0; j < children[ i ] -> descendants.size(); j++ )
//                {
//                    if( children[ i ]->descendants[ j ] == descendantNode )    {
//                        currentBranch = i;
//                        foundRoot = true;
//                        break;
//                    }
//
//                    if(foundRoot)   break;
//                }
//            }
//
//        return currentBranch;
//
//    }
//
//
//    shared_ptr<Node> shared_from_this()
//    {
//        return dynamic_pointer_cast<Node>(kWidget::shared_from_this());
//    }
//
//
//
//
//    bool hasBeenCreated;
//    bool isConnecting;
//
//
//    shared_ptr<Node>  parent;
//    vector<shared_ptr<Node> > children;
//
//    vector <shared_ptr<Node> > descendants;
//
//    vector <int> descendantsX;
//    vector <int> descendantsY;
//
//    vector< shared_ptr<kCircleButton> > connectors;
//
//    int recordX,recordY;
//
//    bool hasGotDescendants;
//
//    bool isActive;
//
//
//};











class kScene: virtual public kWidget {
    public:
        kScene(){}



};


class kTrack: virtual public kWidget {
    public:
        kTrack() {
        }

        void draw(widgetEvent & event);

};



//#endif gui_video_objects_h

#endif

